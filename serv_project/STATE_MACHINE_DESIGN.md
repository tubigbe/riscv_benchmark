# Custom Instruction State Machine Design

## Overview

The custom popcount instruction `popcount rd, rs1, rs2` processes arbitrary-length arrays.
- rs1 = start address
- rs2 = end address
- rd = accumulated popcount result

The state machine uses completion-signal-based transitions, NOT cycle-counting.

## Six States

```
IDLE -> RST -> ADDR_CALC -> DATA_LOAD -> ACCUMULATION -> --+
       ^                                                     |
       |          (address <= end address)                    |
       +-----------------------------------------------------+
                                                           |
                                                (address > end address)
                                                           v
                                                      WRITE_BACK -> IDLE
```

## State Descriptions

### 1. IDLE
Waiting for custom instruction to start.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | 0 | cus_alu inactive |
| o_clr | 0 | |
| o_dbus_cyc | 0 | No memory read |
| o_op_b_source | - | Don't care |

**Transition**: `i_is_customized & i_init` -> RST

---

### 2. RST (Reset/Clear)
Clear cus_alu accumulator before processing new word.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | 0 | |
| o_clr | **1** | Pulse to clear accumulator |
| o_dbus_cyc | 0 | |
| o_op_b_source | - | |

**Duration**: 1 cycle (clr pulse)
**Transition**: After 1 cycle -> ADDR_CALC

---

### 3. ADDR_CALC (Address Calculation + Compare)
Calculate memory address and compare with end address.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | 0 | |
| o_clr | 0 | |
| o_dbus_cyc | 0 | |
| o_op_b_source | **0 (IMM)** | ALU uses IMM for +4 calculation |

**Execution**:
- bufreg loads rs1 address (bit-serial, 32 cycles)
- ALU: rs1 + 4 (using IMM)
- Compare rs1+4 with rs2 (alu_cmp)
- rs1+4 written back to rs1 (self-loop)

**Completion signal**: `i_cnt_done` (32 cycles done)
**Transition**: cnt_done -> DATA_LOAD

---

### 4. DATA_LOAD (Memory Read)
Read memory data into bufreg2.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | 0 | |
| o_clr | 0 | |
| o_dbus_cyc | **1** | Start memory read |
| o_op_b_source | - | |

**Execution**:
- bufreg outputs address -> o_dbus_adr
- o_dbus_cyc = 1 -> wait for i_dbus_ack
- After i_dbus_ack, data loaded into bufreg2

**Completion signal**: `i_dbus_ack` (memory read done)
**Transition**: i_dbus_ack -> ACCUMULATION

---

### 5. ACCUMULATION (Popcount Accumulation)
cus_alu counts 1-bits in bufreg2 data.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | **1** | cus_alu accumulate mode |
| o_clr | 0 | |
| o_dbus_cyc | 0 | |
| o_op_b_source | - | |

**Execution**:
- cus_alu processes 32-bit data from bufreg2
- Result accumulated in cus_alu internal register
- 32 bit-serial cycles

**Completion signal**: `i_cnt_done` (32 cycles done)
**Transition**: cnt_done, then check i_alu_cmp:
- i_alu_cmp=1 (rs1+4 <= rs2) -> ADDR_CALC (next word)
- i_alu_cmp=0 (rs1+4 > rs2) -> WRITE_BACK

---

### 6. WRITE_BACK (Result Output)
Output accumulated popcount result to rd.

| Signal | Value | Note |
|--------|-------|------|
| o_mode | **0** | cus_alu shift-out mode |
| o_clr | 0 | |
| o_dbus_cyc | 0 | |
| o_op_b_source | - | |

**Execution**:
- cus_alu shifts out accumulated result
- Result flows: cus_alu -> rs1 -> ALU (op_b=0) -> alu_rd -> RF write port 0 -> rd
- 32 bit-serial cycles

**Completion signal**: `i_cnt_done` (32 cycles done)
**Transition**: cnt_done -> IDLE

---

## Key Interface Signals

### State Machine Inputs (Completion Signals)

| Signal | Source | Purpose |
|--------|--------|---------|
| i_is_customized | serv_decode | Custom instruction detected |
| i_init | serv_state | Current stage (1=stage1, 0=stage2) |
| i_cnt_done | serv_state | 32 cycles completed |
| i_alu_cmp | serv_alu | rs1+4 > rs2? |
| i_dbus_ack | external | Memory read complete |

### State Machine Outputs (Control Signals)

| Signal | Purpose |
|--------|---------|
| o_mode | cus_alu mode (1=accumulate, 0=shift-out) |
| o_clr | cus_alu accumulator clear pulse |
| o_dbus_cyc | Memory read enable |
| o_op_b_source | ALU operand B source (0=IMM, 1=RS2) |

---

## Critical Issue: init Signal Control

Current `init` is controlled by `serv_state`:
```verilog
assign o_init = i_two_stage_op & !i_new_irq & !init_done;
```

For custom instruction, the state machine needs to control init:
- ADDR_CALC / DATA_LOAD / ACCUMULATION: init=1 (stage 1)
- WRITE_BACK: init=0 (stage 2)

This requires a mux in `serv_top.v`:
```verilog
wire init_actual = is_customized ? state_machine_init : init_from_serv_state;
```

## Modules to Modify

| Module | Change | Requires Permission |
|--------|--------|-------------------|
| serv_customized_state.v | Rewrite to 6-state FSM | Yes |
| serv_top.v | Add init mux + state machine interface | Yes |
| serv_decode.v | Already completed | Done |
