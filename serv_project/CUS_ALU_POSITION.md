# cus_alu Position Documentation (Popcount v4)

## Date

2026-08-27

## Architecture Overview

cus_alu has been repositioned from between RF and ALU to between bufreg2 and rd.

### Previous Position (v3)

```
rs1_raw → cus_alu.o_rs1 → cus_alu.rs1 → ALU.i_rs1 → alu_rd → rf_if.o_wdata0
```

cus_alu intercepted rs1 in the RF→ALU path, accumulated popcount bits, and fed the result back through the ALU.

### Current Position (v4)

```
                    rs1_raw ──────────────────────────────→ ALU.i_rs1 (直连)
                                                            
dbus_rdt[0] → cus_alu.i_mem_bit → cus_alu.o_rd_bit → rf_if.o_wdata0
```

cus_alu now sits between the memory data bus and the RF write data port. It reads memory bits directly and outputs popcount results to rd.

---

## cus_alu Port Map

### New Interface

| Port | Direction | Width | Source/Dest | Description |
|------|-----------|-------|-------------|-------------|
| `i_clk` | input | 1 | `clk` | Clock |
| `i_rst` | input | 1 | `i_rst` | Reset |
| `i_clr` | input | 1 | `cus_state.o_clr` | Synchronous clear for accumulator |
| `i_mode` | input | 1 | `cus_state.o_mode` | 1=accumulate, 0=shift out |
| `i_is_customized` | input | 1 | `decode` | Custom instruction flag |
| `i_mem_bit` | input | 1 | `dbus_rdt[0]` | Memory data bit from bus |
| `o_rd_bit` | output | 1 | `rf_if.i_cus_alu_rd` | Popcount result current bit |
| `o_cus_alu_wen` | output | 1 | `rf_if.i_cus_alu_wen` | RF write enable (6 cycles in stage 2) |

### Removed Ports (v3)

| Port | Direction | Description |
|------|-----------|-------------|
| `o_rs1` | output | Was: raw rs1 bit from RF |
| `rs1` | input | Was: cus_alu output to ALU |

---

## Data Flow: cus_alu Input Path

```
External Memory
  → i_dbus_rdt[31:0]          (32-bit bus from memory)
  → serv_top.v wire dbus_rdt  (= i_dbus_rdt, line 140)
  → cus_alu.i_mem_bit         (= dbus_rdt[0], bit 0)
```

**Key insight**: cus_alu reads `dbus_rdt[0]` directly from the memory bus, NOT from bufreg2's registered output. This is because:
1. Memory data arrives bit-serially (1 bit per cycle)
2. cus_alu accumulates over 32 cycles during stage 1
3. bufreg2's `o_dat` is a 32-bit registered output, not bit-serial

---

## Data Flow: cus_alu Output Path

```
cus_alu.o_rd_bit
  → serv_top.v wire cus_alu_rd_bit
  → rf_if.i_cus_alu_rd
  → rf_if mux: o_wdata0 = cus_alu_wen ? i_cus_alu_rd : rd
  → RF RAM write port 0 data
```

**Write enable path**:
```
cus_alu.o_cus_alu_wen
  → serv_top.v wire cus_alu_wen
  → rf_if.i_cus_alu_wen
  → rf_if: o_wen0 = cnt_en & (trap | (is_customized & init ? 1 : cus_alu_wen ? 1 : rd_wen))
```

---

## ALU Path (Separate from cus_alu)

The ALU now receives rs1 directly from RF (bypassing cus_alu):

```
rs1_raw (from rf_if.o_rs1)
  → ALU.i_rs1
  → ALU computes rs1+4 (during stage 1)
  → ALU.o_rd (= alu_rd) → rf_if.o_wdata0 → RF write (rs1+4 back to rs1)

rs1+4 (re-read from RF or ALU internal)
  → ALU.i_rs1
rs2
  → ALU.i_op_b
  → ALU compares rs1+4 == rs2
  → ALU.o_cmp (= alu_cmp) → cus_state.i_alu_cmp
```

---

## cus_state Interface (Updated)

| Port | Direction | Description |
|------|-----------|-------------|
| `i_alu_cmp` | input (NEW) | ALU comparison result (rs1+4 == rs2) |
| `o_mode` | output | 1=accumulate (stage 1), 0=shift (stage 2) |
| `o_clr` | output | Clear accumulator at start of stage 1 |

---

## RF Write Port Usage Timeline

| Cycle | Stage | o_wen0 | o_wdata0 | Description |
|-------|-------|--------|----------|-------------|
| 0-31 | Stage 1 (init=1) | 1 (self-loop) | ALU result (rs1+4) | Write incremented rs1 back |
| 32-37 | Stage 2 (init=0) | 1 (cus_alu_wen) | cus_alu.o_rd_bit | Write popcount result (6 bits) |
| 38-63 | Stage 2 (init=0) | 0 | X | No write (cus_alu done) |

---

## Files Modified

| File | Change |
|------|--------|
| `serv_customized_alu.v` | Rewritten: new ports `i_mem_bit`, `o_rd_bit`, `o_cus_alu_wen`; removed `o_rs1`, `rs1`; added `shift_cnt` |
| `serv_top.v` | cus_alu instantiation rewritten; ALU rs1 changed from `rs1` to `rs1_raw`; cus_state gained `i_alu_cmp`; rf_if gained `i_cus_alu_rd`, `i_cus_alu_wen` |
| `serv_rf_if.v` | +2 input ports; `o_wdata0` mux for cus_alu; `o_wen0` priority for cus_alu_wen |
| `serv_customized_state.v` | +1 input port `i_alu_cmp` (reserved for future state transitions) |

## Files NOT Modified

- `serv_rf_ram_if.v` — write timing unchanged
- `serv_rf_ram.v` — RAM unchanged
- `serv_bufreg2.v` — bufreg2 unchanged
- `serv_alu.v` — ALU unchanged (only input connection changed)
