# Popcount via Custom Instruction on SERV

## Project Goal

Add a custom RISC-V instruction (opcode `01010`, custom-0 space) to the bit-serial SERV RV32I core that implements **popcount** (population count / Hamming weight) — counting the number of 1-bits in a 32-bit register.

### Long-term Vision
- Phase 1: 32-bit register popcount (current)
- Phase 2: Arbitrary-width popcount

---

## Architecture Overview

```
Instruction Bus
      |
serv_decode.v  (modified)
  - detects opcode[6:2] == 01010
  - sets is_customized = 1
  - overrides opcode -> 01100 (OP-type)
  - ORs is_customized into two_stage_op
      |
      v
serv_state.v  (modified)
  - takes i_is_customized input
  - generates o_rf_wreq at last_init when customized
      |
      v
serv_customized_state.v  (NEW)
  - translates serv_state signals -> cus_alu control
  - no independent clock, uses serv_state timing
      |
      v
cus_alu.v  (modified)
  - intercepts rs1 line when is_customized=1
  - stage 1: accumulate rs1 bits (mode=1)
  - stage 2: shift out accumulated result (mode=0)
      |
      v
serv_top.v  (modified)
  - instantiates cus_alu + serv_customized_state
  - routes rs1_raw -> cus_alu -> rs1 (all consumers)
```

---

## Instruction Encoding

Using RISC-V **custom-0** opcode space:

```
31    27 26 25 24 20 19    15 14    12 11      7 6      2 1 0
+--------+--+--+--------+--------+--------+--------+--------+--+
| funct7 |   | rs2     | rs1    | funct3 | rd     | 01010  |11|
+--------+--+--+--------+--------+--------+--------+--------+--+
```

Decode overrides:
- `opcode` -> 5'b01100 (OP-type), so standard ALU control signals are generated
- `funct3` passes through from real instruction bits (determines which ALU path the popcount result travels through)

---

## Module Details

### `serv_decode.v`

**Modified:** Yes (by user prior to this session)

**Added output:**
```verilog
output reg o_is_customized
```

**Detection logic (PRE_REGISTER block):**
```verilog
if (i_wb_rdt[6:2] == 5'b01010) begin
    is_customized <= 1'b1;
    opcode <= 5'b01100;   // Override to OP-type
    funct3 <= i_wb_rdt[14:12];
    // ... other fields captured normally
end
```

**`co_two_stage_op` includes `is_customized`:**
```verilog
wire co_two_stage_op = ... | is_customized;
```

---

### `serv_state.v`

**Modified:** Yes (this session)

**Added input:**
```verilog
input wire i_is_customized
```

**Modified `o_rf_wreq` (one new OR term):**
```verilog
assign o_rf_wreq = (i_shift_op & ...) |
                   i_dbus_ack |
                   (MDU & i_mdu_ready) |
                   (i_branch_op & (last_init & !trap_pending)) |
                   (i_rd_alu_en & i_alu_rd_sel1 & last_init) |
                   (i_is_customized & last_init);          // NEW
```

**Key signal: `last_init = o_cnt_done & o_init`**
- Pulses for one cycle at the end of stage 1 (counter == 31 while init=1)
- Initializes `rf_ram_if` write counter for stage 2
- Without this signal, register file writes in stage 2 have incorrect timing

---

### `serv_customized_state.v` (NEW)

**Role:** Signal translation layer — translates `serv_state` timing signals into `cus_alu` control signals.

**Ports:**

| Port | Direction | Source | Description |
|------|-----------|--------|-------------|
| `i_clk` | input | system clock | Same clock as serv_state |
| `i_rst` | input | system reset | |
| `i_is_customized` | input | serv_decode | Custom instruction active |
| `i_init` | input | serv_state.o_init | Stage 1 indicator |
| `i_cnt_en` | input | serv_state.o_cnt_en | Counter running (reserved for future) |
| `i_cnt_done` | input | serv_state.o_cnt_done | Counter at max (reserved for future) |
| `i_cnt0` | input | serv_state.o_cnt0 | First bit indicator (reserved for future) |
| `o_mode` | output | -> cus_alu.i_mode | 1=accumulate, 0=shift out |
| `o_clr` | output | -> cus_alu.i_clr | Synchronous clear for accumulator |

**Translation logic:**

```verilog
// Mode: when customized, follow init
o_mode = i_is_customized ? i_init : 1'b0;

// Clear: one-cycle pulse on init rising edge
init_rising = i_init & ~init_r;
o_clr = i_is_customized & init_rising;
```

---

### `cus_alu.v` (NEW, modified this session)

**Role:** Bit-serial popcount accumulator. Counts 1-bits on the `rs1` serial line.

**Added:** `i_clr` synchronous clear input.

**State register:** `pr_partial[5:0]` (6-bit counter, up to 32)

**Modes:**

| `i_clr` | `i_mode` | Behavior |
|---------|----------|----------|
| 1 | X | `pr_partial <= 0` (synchronous clear) |
| 0 | 1 | `pr_partial <= pr_partial + o_rs1` (accumulate) |
| 0 | 0 | `pr_partial <= {1'b0, pr_partial[5:1]}` (shift right) |

**Output mux:**
```verilog
assign rs1 = i_is_customized ? pr_partial[0] : o_rs1;
```

---

### `serv_top.v` (Modified this session)

**Key integrations:**

1. Added wires: `is_customized`, `rs1_raw`, `cus_mode`, `cus_clr`
2. `rf_if.o_rs1` now drives `rs1_raw` instead of `rs1` directly
3. `cus_alu` inserted between `rs1_raw` and `rs1`
4. `serv_customized_state` instantiated, connected to `init`/`cnt_en`/`cnt_done`/`cnt0`

**Data path flow:**
```
serv_rf_if.o_rs1  -->  rs1_raw  -->  cus_alu.o_rs1
                                     cus_alu.rs1  -->  rs1  -->  serv_alu.i_rs1
                                                                  serv_bufreg.i_rs1
                                                                  serv_csr.i_rs1
```

---

## Instruction Execution Timeline

### Stage 1: Accumulate (32 cycles)

```
Cycle         Event                              cus_alu state
-----         -----                              ------------
Decode        is_customized = 1                  idle
              two_stage_op = 1
              opcode -> 01100 (OP-type)
              init -> 1 (combo)

init↑ clk     init_rising pulses                  o_clr = 1 (one pulse)
              RF read request sent                pr_partial = 0

rf_ready      counter starts
cnt0          cnt_en=1, cnt0=1                    mode=1: pr_partial += rs1[0]
cnt1          ...                                 mode=1: pr_partial += rs1[1]
...
cnt31         cnt_done=1                          mode=1: pr_partial += rs1[31]
              last_init = cnt_done & init = 1
              o_rf_wreq pulses (custom term)
              init_done set, init drops
```

### Stage 2: Shift Out + Write RD (32 cycles)

```
Cycle         Event                              cus_alu state
-----         -----                              ------------
cnt0          init=0                              mode=0: rs1 = pr_partial[0]
              rd_en = rd_op & !init = 1
              wen0 = cnt_en & rd_wen              RF writes bit 0
cnt1          ...                                 mode=0: rs1 = pr_partial[1]
cnt2          ...                                 mode=0: rs1 = pr_partial[2]
cnt3                                              mode=0: rs1 = pr_partial[3]
cnt4                                              mode=0: rs1 = pr_partial[4]
cnt5                                              mode=0: rs1 = pr_partial[5]
cnt6..31      ...                                 6-bit result exhausted
                                                  rs1 = 0 (high bits zero-filled)
```

### Instruction Complete

```
cnt_done (stage 2)
  init_done cleared
  o_ctrl_pc_en = cnt_en & !init = 1  -> PC update
  ibus_cyc asserted                   -> next instruction fetch
```

---

## Key Timing Guarantees

### `o_clr` before first accumulation
- `init` goes high immediately after decode (combo logic from `two_stage_op`)
- Counter starts only after `i_rf_ready` (RF read complete)
- `o_clr` pulses on the clock edge when `init` rises
- Between `init↑` and `cnt0`, there are at least 1+ cycles for the RF read handshake
- Guarantee: `pr_partial` is cleared before any bits are accumulated

### `o_rf_wreq` for write path
- `rf_ram_if.i_wreq` initializes the write counter
- The counter cycles through sub-words of the RF RAM, collecting bits into wide words
- Without proper `wreq` timing, writes don't start or collect wrong bits
- `last_init = cnt_done & init` on cycle 31 of stage 1 is the exact right time

---

## Known Incompleteness / Issues (All Resolved)

### Issue 1: `op_b != 0` during stage 2 (FIXED)
- **Root cause:** `op_b` driven by `serv_bufreg2.o_op_b` = rs2 during stage 2, corrupting ALU result
- **Fix:** Added mux in `serv_top.v` that forces `op_b = 0` when `is_customized & ~init`

### Issue 2: `o_rf_wreq` condition for funct3 without `rd_sel[1]` (FIXED)
- **Root cause:** Original term `i_rd_alu_en & i_alu_rd_sel1 & last_init` misses some funct3 values
- **Fix:** Custom term `i_is_customized & last_init` added in `serv_state.v` bypasses this

### Issue 3: `alu_rd_sel` must pass `rs1` through (RESOLVED)
- Resolved by Issue 1 fix — with `op_b = 0`, both ADD and XOR paths compute `rs1` correctly

---

## File Inventory

| File | Status | Path |
|------|--------|------|
| `serv_top.v` | **Modified** | `D:\Vivado\SERV\rtl\` |
| `serv_state.v` | **Modified** | `D:\Vivado\SERV\rtl\` |
| `serv_decode.v` | **Pre-modified** | `D:\Vivado\SERV\rtl\` |
| `serv_customized_alu.v` | **Modified** | `D:\Vivado\SERV\rtl\` |
| `serv_customized_state.v` | **NEW** | `D:\Vivado\SERV\rtl\` |
| `serv_alu.v` | Unchanged | `D:\Vivado\SERV\rtl\` |
| `serv_rf_if.v` | Unchanged | `D:\Vivado\SERV\rtl\` |
| `serv_rf_ram_if.v` | Unchanged | `D:\Vivado\SERV\rtl\` |
| `serv_bufreg2.v` | Unchanged | `D:\Vivado\SERV\rtl\` |
| `serv_bufreg.v` | Unchanged | `D:\Vivado\SERV\rtl\` |

---

## Vivado Project

- **Project:** `D:\serv_viewer\serv_viewer.xpr`
- **Files added to project:** `serv_customized_state.v`
- **Top module (current):** `tb_cust_alu` (standalone ALU testbench)
- **Top module (for full system test):** `serv_rf_top`

To run full system simulation: add a system-level testbench as a simulation source and set it as top.
