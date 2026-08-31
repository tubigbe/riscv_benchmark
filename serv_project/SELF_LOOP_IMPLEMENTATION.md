# RF Self-Loop Implementation (Popcount v4)

## Date

2026-08-26

## Goal

Enable rs1 and rs2 registers to self-loop in the RF during the custom popcount instruction (Stage 1). This is the foundation for the new arbitrary-length popcount instruction: `popcount rd, rs1(start_addr), rs2(end_addr)`.

## What Was Implemented

### Core Mechanism

When `is_customized=1 & init=1` (Stage 1), the RF write ports are re-targeted:

- **Port 0 (rs1)**: writes ALU result (rs1+4) back to rs1 address
- **Port 1 (rs2)**: writes raw rs2 value back to rs2 address

This allows:
- rs1 to auto-increment by 4 each cycle (address pointer walks through memory)
- rs2 to remain constant throughout the instruction (end address for comparison)

### Files Modified

| File | Location | Changes |
|------|----------|---------|
| `serv_rf_if.v` | `fusesoc_libraries/serv/rtl/` | +2 input ports, 4 output overrides (both WITH_CSR and gen_no_csr paths) |
| `serv_top.v` | `fusesoc_libraries/serv/rtl/` | rf_if instance: +2 port connections |

### Files NOT Modified

- `serv_rf_ram_if.v` - No changes needed (time-division already handles simultaneous read/write)
- `serv_rf_ram.v` - No changes needed (read-first RAM supports simultaneous read/write)
- `serv_customized_alu.v` - No changes needed (passthrough during stage 1)

### Backup Files

- `serv_rf_if.v.bak` - Original serv_rf_if.v
- `serv_top.v.bak` - Original serv_top.v

### Documentation

- `RF_SELF_LOOP_PORTS.md` - Complete port reference for rs1/rs2 intermediate signals

## Detailed Changes

### serv_rf_if.v

**New input ports:**
```verilog
input wire i_is_customized,  // Custom instruction flag
input wire i_init,           // Stage 1=1, Stage 2=0
```

**Write data (o_wdata1):**
```verilog
// Before:
assign o_wdata1 = i_trap ? i_mepc : i_csr;
// After:
assign o_wdata1 = i_trap ? i_mepc : (i_is_customized & i_init ? i_rdata1 : i_csr);
```

**Write address (o_wreg0):**
```verilog
// Before:
assign o_wreg0 = i_trap ? {6'b100011} : {1'b0, i_rd_waddr};
// After:
assign o_wreg0 = i_trap ? {6'b100011} : (i_is_customized & i_init ? {1'b0, i_rs1_raddr} : {1'b0, i_rd_waddr});
```

**Write address (o_wreg1):**
```verilog
// Before:
assign o_wreg1 = i_trap ? {6'b100010} : {4'b1000, i_csr_addr};
// After:
assign o_wreg1 = i_trap ? {6'b100010} : (i_is_customized & i_init ? {1'b0, i_rs2_raddr} : {4'b1000, i_csr_addr});
```

**Write enable (o_wen0):**
```verilog
// Before:
assign o_wen0 = i_cnt_en & (i_trap | rd_wen);
// After:
assign o_wen0 = i_cnt_en & (i_trap | (i_is_customized & i_init ? 1'b1 : rd_wen));
```

**Write enable (o_wen1):**
```verilog
// Before:
assign o_wen1 = i_cnt_en & (i_trap | i_csr_en);
// After:
assign o_wen1 = i_cnt_en & (i_trap | (i_is_customized & i_init ? 1'b1 : i_csr_en));
```

**o_wdata0 NOT changed** - The existing `rd` mux already carries `alu_rd` when `i_rd_alu_en=1`.

### serv_top.v

**rf_if instance addition:**
```verilog
//Customized instruction self-loop
.i_is_customized (is_customized),
.i_init          (init),
```

## Data Flow Summary

### rs1 (Address Increment Loop)

```
RF RAM → i_rdata0 → o_rs1 (rs1_raw) → ALU → alu_rd (rs1+4) → o_wdata0 → RF RAM (rs1 addr)
              ↑                                                                    │
              └────────────────────────────────────────────────────────────────────┘
```

### rs2 (Constant Self-Loop)

```
RF RAM → i_rdata1 → o_rs2 (output) → [compare with rs1]
         i_rdata1 → o_wdata1 → RF RAM (rs2 addr)
              ↑                    │
              └────────────────────┘
```

## Timing

- 32 cycles per stage (bit-serial, W=1)
- Stage 1 (init=1): rs1 auto-increments, rs2 constant
- Stage 2 (init=0): self-loop disabled, normal rd write resumes
- RF RAM read-first behavior ensures simultaneous read/write is safe

## Prerequisites for Full Instruction

The following are NOT part of this change but are needed for the complete custom instruction:

1. **Decode logic** (`serv_decode.v`): Set `i_rd_alu_en=1` for custom instruction
2. **ALU configuration**: Route rs1 to ALU, set op_b=4 (immediate), sub=0 (add)
3. **State machine** (`serv_customized_state.v`): Control multi-pass loop, comparison with rs2
4. **bufreg/bufreg2**: Use rs1 address for memory read, store 32-bit data for cus_alu
