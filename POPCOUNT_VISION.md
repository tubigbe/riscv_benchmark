# Arbitrary-Width Popcount Optimization Vision

## Current State

The current `cus_alu` only performs a single 32-bit popcount: it accumulates 1-bits from one 32-bit word over 32 cycles, then shifts out the 6-bit result over the next 32 cycles. Total: 64 cycles per 32-bit word.

**Limitation:** Cannot handle arrays larger than 32 bits.

---

## Goal

Implement **arbitrary-width popcount** via a single custom instruction that processes an entire memory array in one execution.

**Instruction format:**
```asm
popcount rd, rs1, rs2
```
- `rd` : destination register, receives final popcount result
- `rs1`: start address of input array (also used as loop counter, overwritten in-place)
- `rs2`: end address of input array (constant throughout execution)

---

## Execution Model

### Per-Word Cycle Budget

Each 32-bit word requires two stages:

| Stage | Cycles | Action |
|-------|--------|--------|
| 1 (accumulate) | 32 | `cus_alu` accumulates 1-bits from current word |
| 2 (shift out) | 32 | `cus_alu` shifts 6-bit partial result to rd path |

Total per word: **64 cycles**.

For N words: **64 x N cycles**.

### Data Path — Per Word Cycle

```
rs1 (address) ──┬──> bufreg (holds current address)
                 │         │
                 │    bufreg2 (fetches 32-bit data from memory)
                 │         │
                 │    cus_alu (popcount accumulation)
                 │         │
                 └──> serv_alu (+4 increment, compare with rs2)
                          │
                     writeback to rs1 (address += 4)
```

### Signal Flow Detail

**Stage 1 (32 cycles) — Accumulate:**
1. `rs1_raw` (from RF) = current address
2. `rs1_raw` → `bufreg` (loads address into data bus)
3. Memory read: `o_dbus_adr = bufreg_q`, data arrives via `dbus_ack`
4. `bufreg2` latches 32-bit data, serializes it to `o_op_b`
5. `cus_alu` accumulates `o_op_b` bits into `pr_partial[5:0]`
6. Simultaneously: `serv_alu` computes `rs1 + 4`, result written back to `rs1` register

**Stage 2 (32 cycles) — Shift Out:**
1. `cus_alu` shifts `pr_partial` right, outputting 6-bit result on `rs1` line
2. `rs1` → rd path → RF write
3. `rs1 + 4` and compare with `rs2` continue in parallel (address update for next word)

### Termination

The custom instruction completes when `rs1 >= rs2` (address comparison in `serv_alu`). The state machine detects this condition and signals instruction completion.

---

## Register Budget — Hard Constraint

**All additional registers introduced in the custom extension must serve only:**
- State machine control logic (FSM states, counters, flags)
- Condition judgment (comparison results, loop termination)

**Absolutely NO additional registers may be used for data storage.**

The existing `bufreg`, `bufreg2`, and `cus_alu.pr_partial[5:0]` are sufficient for all data holding. Any new registers are purely for controlling the execution flow.

---

## State Machine Design Requirements

The current `serv_customized_state.v` is minimal (just mode/clear translation). It needs to be expanded into a full FSM that coordinates:

1. **Memory access sequencing** — when to assert `dbus_cyc`, when to latch data
2. **Address increment timing** — when `rs1+4` is ready, when to write back
3. **Comparison logic** — detect `rs1 >= rs2` to terminate loop
4. **Accumulator lifecycle** — clear before each word, accumulate, shift out, repeat
5. **RF write path** — ensure `rd` receives the accumulated result correctly

### Proposed States (conceptual)

| State | Description |
|-------|-------------|
| `IDLE` | Waiting for custom instruction decode |
| `LOAD_ADDR` | Drive rs1 address to data bus, initiate memory read |
| `WAIT_MEM` | Wait for `dbus_ack`, latch data into bufreg2 |
| `ACCUMULATE` | 32 cycles: accumulate bits from bufreg2 into pr_partial |
| `INCREMENT` | Compute rs1+4, compare with rs2, writeback rs1 |
| `SHIFT_OUT` | 32 cycles: shift pr_partial result to rd |
| `CHECK_DONE` | If rs1 < rs2 → back to LOAD_ADDR; else → COMPLETE |
| `COMPLETE` | Signal instruction done, PC update |

---

## Key Design Decisions

### 1. rs1 Register Reuse
rs1 serves dual purpose:
- **Address source** for memory fetch (drives bufreg/dbus_adr)
- **Loop counter** (incremented by +4 each iteration)

This avoids allocating a separate counter register — the RF itself holds the address.

### 2. rs2 as Constant
rs2 never changes. It provides the termination boundary. The comparison `rs1 + 4 >= rs2` determines when to stop.

### 3. Memory Access Pattern
Each iteration reads exactly one 32-bit word from `[rs1]`. The address is word-aligned (4-byte granularity). No misalignment handling needed for this use case.

### 4. Result Accumulation
The 6-bit `pr_partial` accumulator is cleared before each word, accumulated during 32 cycles, then shifted out. For a full array, the final result in `rd` is the total popcount across all words.

---

## Implementation Checklist

- [ ] Redesign `serv_customized_state.v` as full FSM
- [ ] Modify `cus_alu.v` to support multi-word accumulation (clear per word)
- [ ] Add rs1+4 increment logic using existing `serv_alu`
- [ ] Add rs1 >= rs2 comparison for loop termination
- [ ] Route memory access signals through state machine
- [ ] Ensure no new data registers added (control only)
- [ ] Update `serv_top.v` for new signal routing
- [ ] Test with arrays of varying sizes (1 word, 4 words, 100+ words)

---

## Files to Modify

| File | Change |
|------|--------|
| `serv_customized_state.v` | Major rewrite: full FSM |
| `serv_customized_alu.v` | Add per-word clear, multi-word mode |
| `serv_top.v` | New signal routing for memory/comparison |
| `serv_state.v` | May need additional handshake signals |
| `serv_decode.v` | Possibly no change (already detects custom opcode) |
