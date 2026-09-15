# AGENTS.md — SERV RISC-V Popcount Optimization

## Project Overview

**SERV** — the world's smallest RISC-V CPU. This project compiles firmware, runs it on a Verilator simulation of the SERV SoC, and produces detailed per-instruction cycle-cost reports.

**Key goal**: Reduce custom popcount instruction cycle count from **68 cycles** to **≤50 cycles**.

**Status: ACHIEVED** — the custom popcount instruction runs at **42 cycles** with an **in-window writeback**: rd comes out clean (no high-bit garbage) and the following instruction is **not slowed at all**. v2 (random_forest) measurement: Total cycles **492928** = v1 RTL (493448) − 20×(68−42), row-identical to v1 RTL except the 20 `.insn` rows. Saved as git tag **`v1.5_lucky`** (commit `271570b`).

**Next Task**: Merge two RTL designs together:
- **v1.5 RTL** (`serv_project/fusesoc_libraries/serv_v1.5_rtl/`): Popcount optimization (42-cycle in-window writeback).
- **BNE RTL** (`serv_project/fusesoc_libraries/serv_bne/`): Teammate's BNE early-exit optimization.
Combine both into a unified design to achieve joint speedups from both popcount and branch early-exit.

## ⚠️ IMPORTANT — Optimization scope (read this first)

**RTL folders for the merge task**:
```
serv_project/fusesoc_libraries/serv_v1.5_rtl/   ← v1.5 popcount design (base / target)
serv_project/fusesoc_libraries/serv_bne/        ← BNE early-exit design (merge source)
```

**Do NOT read** (not relevant for this task):
- `serv_project/fusesoc_libraries/serv_rtl_origin/` (original SERV, unoptimized)
- Subdirectories outside `serv/rtl/`: `serv/servant/`, `serv/bench/`, `serv/sw/` (shared infrastructure / testbenches — read-only, do not change)
- `Codespace/`, `serv_project/scripts/`, and other top-level directories

> Core files for the popcount writeback: `serv_state.v`, `serv_top.v`, `serv_rf_ram_if.v`, `serv_customized_alu.v`, `serv_customized_state.v` (all under `serv/rtl/`).
> One exception: `servile/servile.v` contains the `i_rf_wr_busy` wiring (the real datapath); if you change `serv_rf_ram_if`/`serv_top` ports, check it in sync.

## Current Design (v1.5_temp, commit `32f3f64`) — HISTORICAL: writeback superseded by v1.5_lucky

> ⚠️ The `custom_wr_active`/`wr_timer`/`custom_rd` out-of-band 36-cycle writeback described here is the **old mechanism**, removed in v1.5_lucky (commit `271570b`) and replaced by the "in-window writeback" (stage1 zero-fill + stage2 count write; see the **v1.5_lucky** section at the end). The stage1/stage2/`custom_stage2_done`/early-fetch structure is still valid.

The popcount instruction is a custom 2-stage instruction:

- **Stage 1** (`i_init=1`, 32 cycles): `cus_alu` accumulates set-bits of `rs1` into the 6-bit `pr_partial[5:0]`, while the PC shifts in PC+4 (`o_ctrl_pc_en = o_init ? o_cnt_en : 0`).
- **Stage 2** (`i_init=0`, **fixed 6 cycles**): `pr_partial` is shifted out LSB-first via `o_serial`; the count is written back to the RF.
- **Total**: 32 + 6 + fetch overhead ≈ **42 cycles**.

### Stage-2 control (serv_state.v)

- `custom_stage2_done = i_is_customized & !o_init & (o_cnt==3'd1) & cnt_r[1] & o_cnt_en` — fires at stage-2 count 5 (6th cycle), **data-independent** (no `is_acc_done` dependency).
- `o_cnt_done = (o_cnt[4:2]==7) & cnt_r[3] | custom_stage2_done`.
- At `custom_stage2_done`: the counter (`o_cnt` + `cnt_lsb`) is cleared (so the next instruction starts at count 0), and `ibus_cyc` is asserted to **early-fetch** the next instruction.
- `init_done` is **held** at `custom_stage2_done` and cleared on the early fetch's `i_ibus_ack` — this prevents the custom instruction from re-entering stage 1 (which would re-fire `o_rf_wreq` in a loop).
- `o_rf_wreq = ... | (i_is_customized & last_init)` — the write is triggered **once** at the stage-1→2 boundary (`last_init`).
- `o_rf_rreq` is deferred only while the **custom** writeback is draining (`custom_wr_drain`, set on `o_rf_wreq & i_is_customized`, cleared on `!i_rf_wr_busy`) so the next instruction's read does not reset `rcnt` mid-write. Ordinary writeback ops (branch/jump/lw/sw/shift) also raise `i_rf_wr_busy` but are NOT deferred (original SERV tolerated them — see bug 7).

### Writeback (serv_top.v — bypasses the main ALU) — superseded by v1.5_lucky

The popcount result is **not** routed through the main ALU. Instead (old scheme):

- `cus_alu.o_serial = pr_partial[0]` feeds `o_wdata0` directly.
- `custom_wr_active` is a **36-cycle one-shot** (set at `o_rf_wreq & is_customized & !custom_wr_active`, never re-triggered) that covers the whole serial RF write window.
- During the window:
  - `o_wdata0 = cus_serial` (count bits then zeros) — immune to `bufreg`/`op_b` corruption.
  - `o_wen0 = 1` — held high because the RF write enable is gated by `i_cnt_en`, which drops after the 6-cycle stage 2 (otherwise only the low 6 bits get written and the upper 26 bits retain the old register value).
  - `o_wreg0 = custom_rd` — the custom rd is latched at the write request, because the next instruction decodes before the serial write ends (otherwise the upper words get written to the wrong register).
- After the window, `o_wdata0`/`o_wen0`/`o_wreg0` revert to the normal RF path.
- `op_b = op_b_raw`, `alu_buf = bufreg_q` (plain sources — the ALU is no longer in the writeback path).

### RF write-busy wiring (servile.v — the important gotcha)

The SoC's real datapath is `servile` instantiating `serv_rf_ram_if` + `serv_top` **directly**; `serv_rf_top` is NOT used by the simulation. So `o_wr_busy` must be wired inside `servile.v`:

```
serv_rf_ram_if.o_wr_busy → rf_wr_busy → serv_top.i_rf_wr_busy
```

`serv_rf_ram_if` asserts `o_wr_busy` for ~34 cycles after each write request (`wr_busy_cnt`).

## Bugs found & fixed during this work

1. **Counter not fully cleared** — `o_cnt` stayed nonzero, so the next instruction started at count 4 and computed PC+4 wrong (`0x50→0x500`). Fixed by clearing `o_cnt` + `cnt_lsb` at `custom_stage2_done`.
2. **Double RF write trigger** — both `last_init` and `o_cnt_done & init_done` fired, resetting `rcnt` and zeroing the result. Kept only `i_is_customized & last_init`.
3. **`wr_busy` wired to the wrong module** — it was connected in `serv_rf_top` (unused); the real path is `servile`. Fixed in `servile.v`.
4. **`o_wen0` gated by `i_cnt_en`** — after stage 2 the counter is cleared so only the low 6 bits were written; upper 26 bits kept the old value (`0x4AC8`). Fixed by forcing `o_wen0` high during `custom_wr_active`.
5. **Write register stolen by next instruction** — `o_wreg0` changed to the next instr's rd mid-write; fixed by latching `custom_rd`.
6. **Custom instruction re-entering stage 1** — `init_done` cleared at stage-2 end made `o_init` flip back to 1, re-running the counter and re-firing `o_rf_wreq` forever. Fixed by holding `init_done` until the early fetch's `i_ibus_ack`.
7. **Global +1 on every writeback op's successor (v1.5 structural regression)** — deferring `o_rf_rreq` on the raw `i_rf_wr_busy` applied to ALL instructions, but ordinary writeback ops (branch/jump/lw/sw/shift/`.insn`) also assert `o_rf_wreq` → `wr_busy` → the next instruction's read was held 1 cycle. On identical v2 firmware, **5853/8381 instructions ran +1** vs v1 RTL (70%!), everywhere in the code, independent of popcount — proof the v1.5 writeback machinery had broken the original SERV state structure. **Fix (2026-09-03)**: added `custom_wr_drain` in serv_state.v — defer the read ONLY while the custom writeback is draining. Result: total 499281 → **493488**, all 8341 ordinary instructions cycle-identical to v1 RTL.

## Key RTL Signals

| Signal | Location | Meaning |
|---|---|---|
| `custom_stage2_done` | serv_state.v | stage-2 count 5 (6-cycle end) |
| `o_serial` / `cus_serial` | serv_customized_alu.v / serv_top.v | raw serial count bits (`pr_partial[0]`) |
| `custom_win` | serv_top.v | in-window writeback window (stage1+stage2) |
| `custom_wr_drain` | serv_state.v | custom writeback still draining (defer next read only then) |
| `o_wr_busy` / `i_rf_wr_busy` | serv_rf_ram_if.v / servile.v / serv_state.v | RF writeback in progress |
| `rf_rreq_pending` | serv_state.v | deferred read while custom writeback draining |

## Key Files & Commands

### Build & Simulation Pipeline

```bash
cd riscv_benchmark
./setup.sh                          # Fetch submodules, verify tools
source Codespace/env.sh             # Load toolchain into PATH

cd serv_project
./build.sh --build                  # Compile firmware into firmware.hex
./run_sim.sh                        # Clean + build Verilator model + simulate
cat log/compare_result.txt          # Merged trace with per-instruction cycle info
```

### Popcount Test

```bash
./serv_project/run_popcount_test.sh           # Default max_val=10000, timeout=60s
./serv_project/reproduce_range_popcount.sh
```

### Current Test Firmware

`Codespace/SERV_codespace/build_codes/popcount_cus.c` — computes `popcount_sink = popcnt_custom(19149)` and prints it via UART:

```
popcount_sink = 0x00000008
```

UART output appears on the GPIO/`q` line (bit-banged by `asm_uart_putchar` in `startup.S`). The testbench does NOT capture UART; inspect `q` in `log/sim_wave.vcd` or add capture if needed.

### RTL Files of Interest

- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_customized_alu.v` — 6-bit `pr_partial` accumulator, `o_serial` output
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_customized_state.v` — `i_init` → `o_mode`/`o_clr` (mode gated on `i_cnt_en`)
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_state.v` — stage-2 control, counter, write/read requests
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_top.v` — in-window writeback (`o_wdata0`/`o_wen0`/`o_wreg0`, `custom_win`)
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_rf_ram_if.v` — `o_wr_busy`, `wr_busy_cnt`
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/servile/servile.v` — **real** datapath wiring of `i_rf_wr_busy`
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_decode.v` — identifies custom instructions (opcode `01010`)

## Git State

- **serv repo** (RTL): tag **`v1.5_lucky`** = commit `271570b` (in-window writeback; see section at end). Chain: `fe99b81` (bug-7 custom_wr_drain scope fix, 499281→493488) → `5e5ee9a` (force-stop writeback probe: follower 98→70 but rd high bits garbage) → `271570b` (in-window writeback: stage1 zero-fill + stage2 count write; rd clean and follower has no stall). Earlier: `32f3f64`=v1.5_temp, `29e4e38`, `6a7f684`, `f808bc5`.
- **top repo** (firmware/scripts): main = `b0a8fd0`.
- v1 RTL snapshot kept at `serv_project/serv_rtl_v1/` (gitignored); results saved as `log/v1_results` (68 cyc/insn, 666 total) and `log/v1.5_results` (42 cyc/insn, 614 total).
- `Codespace/SERV_codespace/Codehub/popcount.c` — older software/custom comparison test (reference only).

## Verification Outputs

- `log/sim_log.txt` — PC transitions with cycle counts per instruction
- `log/trace_dump.txt` — Symbol-resolved PC trace
- `log/compare_result.txt` — Merged trace with per-instruction cycle info and summary stats
- `log/sim_wave.vcd` — full waveform (GTKWave) for RTL debugging
- `log/popcount_test.txt` — popcount test results (pass/fail per value)

## Historical direction (2026-09-03) — writeback serialization — ✅ RESOLVED by v1.5_lucky (see section at end)

### Problem (2026-09-02 original → 2026-09-03 global +1 fixed, see bug 7)

`.insn` (popcount) itself is 42 cycles ✓, but **the single instruction right after it is slowed by ~28 cycles**:

- Evidence: in `log/C_v2_popcount_v15fixed.txt` (fixed v1.5), the `not` (0x13c) right after `.insn` (0x138) is **64 cycles**, while a `not` after an ordinary `and` (0x130) is **36 cycles**. **Only the instruction immediately after `.insn`** is affected (20 total, all `not`/`add`); the other 8341 ordinary instructions are cycle-identical to v1 RTL.
- In the A/B measurements (original/BNE, no popcount) every `not` is 36.
- Cause: the popcount writeback window `custom_wr_active` (36 cycles) kept draining after the instruction itself ended (out-of-band writeback); the next instruction's RF read was deferred by `rf_rreq_pending` (now only during `custom_wr_drain`) until the writeback cleared → 36 + ~28 writeback wait = 64.

### Goal

Make the popcount writeback **truly overlap** the execution of the following instruction and recover the ~28 cycles. `.insn` effective cost is currently ≈ 42 + 28 = ~70; after overlap it should return to ~42. The fixed version's total is 493488 ≈ v1 RTL's 493448 (difference 40 = 20×(.insn saves 26 − follower pays 28)); popcount is fast but the writeback serialization cancels it out.

### Difficulties (pitfalls hit before)

- Earlier attempt "don't defer the RF read" (remove serialization) → the writeback was reset mid-write by the next instruction's read (`rcnt` reset), **corrupting the result** (e.g. `0x4AC8`).
- So `rf_rreq_pending` cannot simply be deleted; finer read/write coordination of the RF is needed.

### Candidate ideas (unverified at the time)

1. **Decouple RF read/write**: give `serv_rf_ram_if` independent counters/timing for read and write so a read can start during a writeback without resetting the writeback's `rcnt` alignment. Change in `serv/rtl/serv_rf_ram_if.v`.
2. **Decouple writeback data from `o_rd`**: already done (`o_wdata0 = custom_wr_active ? cus_serial : rf_wdata0`). If read/write can be decoupled, the next instruction's ALU activity on `o_rd` no longer pollutes the writeback.
3. **Shorten the writeback window**: `custom_wr_active` is currently 36 cycles (covering the whole 32-bit serial RF write). Could we write only the low words in the 6 count bits and force the high bits to zero, shortening the window? Requires changes to `serv_top.v`'s `o_wen0`/`o_wreg0`/`o_wdata0` logic + `serv_rf_ram_if.v`.

### Verification method

- Reproduce: `./serv_project/run_sim.sh --serv-dir=fusesoc_libraries/serv_v1.5_rtl` (popcount version) with v2 firmware; check in `log/compare_result.txt` whether the instruction after `.insn` is still ~63.
- Goal: after the fix the next instruction returns to ~36-40 and the popcount result stays correct (the `C` measurement's total cycles should drop noticeably).

### Related measurement archives

- `log/A_v1_origin.txt` — v1 on original SERV, Total cycles 526208
- `log/D_v1_fixed15.txt` — v1 on v1.5_fixed, Total cycles 526208 (9013 lines with **0 diff** vs A row-by-row → the pure RV32I path is exactly identical to the original; regression evidence for the fix's correctness)
- `log/B_v1_bne.txt` — v1 on BNE, Total cycles 493157
- `log/C_v2_popcount_v1rtl.txt` — **official C measurement**: v2 on v1 RTL (`serv_rtl_v1`, 68-cycle .insn), Total cycles 493448 ← use this one
- `log/C_v2_popcount_v15fixed.txt` — v2 on fixed v1.5 (`custom_wr_drain` fix), .insn 42, Total cycles 493488 (global +1 removed; only the 20 followers pay the writeback serialization)
- `log/C_v2_popcount.txt` — **void** (measurement polluted by the v1.5 writeback bug), v2 on v1.5, 499281, for reference only

> Note: v1 RTL has `.insn` at 68 cycles (v1.5 at 42) but a slightly LOWER total (493448 < 493488), because v1 has **no** v1.5 writeback serialization (followers are not slowed by ~28 cycles). The v1.5 writeback serialization cost is real and was the target of the next optimization — now resolved by v1.5_lucky.

## v1.5_lucky — In-window writeback (2026-09-03, ✅ done, tag `v1.5_lucky`)

### What was achieved (on top of v1.5_fixed `fe99b81`)
- **Goal 1 (follower stall) and Goal 2 (rd garbage) solved together**: `.insn` stays at 42 cycles, rd is clean across all 32 bits, and the following instruction has zero stall.
- Core design: moved the popcount writeback from the "out-of-band 36-cycle window after the instruction" to "completed inside the instruction's own window" (only `serv/rtl/serv_top.v` changed; net −2 flip-flops):
  1. **stage1 (init=1, 32 cycles)**: `o_wdata0` is driven to 0 and `o_wen0` forced to 1; zeros are streamed into all of rd through the normal serial write port. LSB-first; each word is first read into `rdata0` (~rcnt 2j+1) before its zero-write commits (~rcnt 4+2j) → **rd==rs1 safe** (same mechanism as ordinary ALU rd==rs1).
  2. At the stage1→2 boundary the retained `o_rf_wreq` resets rcnt → **stage2 (init=0, 6 cycles)** re-aligns and writes the 6-bit count (`cus_serial`) into word0..2.
  3. `custom_win` (1 flop): set on `is_customized & cnt_en & init`, cleared on `is_customized & !init & cnt_done`; while set `o_wen0=1`, `o_wreg0=rf_wreg0` (immdec holds rd for the whole instruction, so the `custom_rd` latch is deleted); the RF write port is released right after stage 2's last beat.
  4. Deleted `custom_wr_active`/`wr_timer`/`custom_rd`. `serv_state.v`/`serv_rf_ram_if.v` untouched (`wr_busy_cnt=6` + `custom_wr_drain` kept; wreq is used only for the rcnt re-align and no longer blocks anything now that there is no out-of-band write).

### Verification
- build_codes (single `.insn`@0x6c, `popcnt x15,x15` of 0x0fffffff → 28): `.insn`=42; follower `sw`=70 (was 98); VCD reconstruction of x15=**0x0000001C** (all 16 words written, upper 26 bits zero); instruction count 1647 exactly matching v1 RTL; total 91094 = v1(91120) − 26.
- **v2 (random_forest, 10 samples, 20 `.insn` executions)**: Total cycles **492928** = v1 RTL `C_v2_popcount_v1rtl.txt` (493448) − 20×26; row-by-row comparison over 8381 rows shows **0 differences** except the 20 `.insn` rows (68→42), including all followers back at 36.
- Archives: `log/C_v2_popcount_v15lucky.txt` (compare_result), `log/C_v2_simlog_v15lucky.txt`, `log/C_v2_tracedump_v15lucky.txt`.
- v2 firmware build dir: `Codespace/SERV_codespace/rf_v2_lucky/` (C/H sources from random_forest/modified_scripts + startup.S/main.c from base random_forest; note the modified main.c has a leftover `stdio.h` include and cannot be compiled as-is).

## Next Task — Merge RTL Designs: v1.5 (Popcount) + BNE (Early-Exit)

### Objective
Merge the two distinct RTL optimization branches into a single unified SERV core:
1. **v1.5 Popcount optimization** (`serv_project/fusesoc_libraries/serv_v1.5_rtl/`):
   - Custom 2-stage popcount instruction (`.insn`, 42 cycles).
   - In-window writeback (stage 1 zero-fill + stage 2 count write, zero follower stall, clean `rd`).
   - Core files: `serv_customized_alu.v`, `serv_customized_state.v`, `serv_top.v`, `serv_state.v`, `servile/servile.v`.
2. **BNE Early-Exit branch optimization** (`serv_project/fusesoc_libraries/serv_bne/`):
   - Early-exit evaluation when inequality is determined early, reducing cycle latency on branch instructions.
   - Core files: `serv_bne_early.v`, along with modifications to `serv_state.v`, `serv_ctrl.v`, etc.

### Merge Goals & Verification
- Combine both datapaths into a unified RTL codebase without conflicting state-machine signals (`custom_stage2_done`, early fetch, and BNE branch early-exit control).
- Ensure correctness: Verify that popcount retains its 42-cycle clean in-window execution and that BNE continues to early-terminate as expected.
- Validate on the `random_forest` benchmark and dedicated popcount test suite (`run_popcount_test.sh`).

## Appendix — scripts, environment & toolchain reference (moved out of README)

> `README.md` is the short public-facing doc for readers (e.g. the teacher). This
> appendix keeps the detailed per-script reference that was removed from it.

### Environment & first-time setup
- `source Codespace/env.sh` adds the in-repo RISC-V toolchain to PATH
  (`tools/riscv64/usr/bin`, prefix `riscv64-unknown-elf-`).
- `./setup.sh` (repo root): `git submodule update --init --recursive`, then verifies
  that the working RTL dirs under `serv_project/fusesoc_libraries/` are non-empty.
  Note: that whole directory is git-ignored **except** the four SERV variants, which
  are committed directly (`serv_v1.5_rtl`, `serv_bne`, `serv_rtl_origin`,
  `serv_rtl_v1`). The upstream clones `fusesoc_cores/ mdu/ picorv32/` stay ignored.
- Toolchain requirements:
  | Tool | Used by |
  |---|---|
  | `riscv64-unknown-elf-gcc/objcopy/objdump` | build.sh (compile/link/hex), trace_dump.py (symbols) |
  | `verilator` (>=5) | run_sim.sh Verilator compile |
  | `g++` | run_sim.sh testbench compile |
  | `fusesoc` | build.sh `--run` path only (optional; primary sim is run_sim.sh) |
  | `python3` | makehex.py, trace_dump.py, compare_traces.py |
  | `gtkwave` (optional) | viewing log/sim_wave.vcd |

### Pipeline
```
build.sh  (.c/.S, -march=rv32i, freestanding)  ->  firmware.hex
run_sim.sh (clean -> verilator+g++ -> Vservant_sim)  ->  sim_log.txt + sim_wave.vcd + trace.bin
trace_dump.py + compare_traces.py  ->  log/trace_dump.txt + log/compare_result.txt
```
RTL variant is selected with `--serv-dir=<dir>` on both build.sh and run_sim.sh
(default `fusesoc_libraries/serv_v1.5_rtl`). `run_sim.sh` compiles the variant's
own file list and adds conditional sources: `serv_customized_{alu,state}.v`
(v1/v1.5 popcount) or `serv_bne_early.v` (bne).

### scripts reference
- `scripts/sim_main.cpp` — self-written Verilator testbench. Toggles wb_clk, applies
  active-high reset, monitors `pc_vld`/`pc_adr` each rising edge and logs
  `last_pc -> current_pc : N cycles` to `log/sim_log.txt`. Enabled with
  `+vcd=1` (writes log/sim_wave.vcd) and `+trace_pc=1` (writes
  build/…/verilator_tb/trace.bin). Simulation ends on the SoC halt (program writes
  `0x90000000`) or after 10M cycles. Does NOT capture UART.
- `scripts/trace_dump.py` — trace.bin (32-bit PCs) -> symbol-resolved
  `log/trace_dump.txt`; also regenerates `firmware.dump` (objdump `-M no-aliases,numeric`).
- `scripts/compare_traces.py` — merges sim_log.txt (cycle costs) with trace_dump.txt
  (mnemonics) into `log/compare_result.txt`; merges two-part instructions (sw/lbu …)
  and prints summary stats + per-instruction averages.
- `scripts/cycle_cost.sh <start> <end>` — cycle cost between two PCs from
  compare_result.txt (bare hex, `0x…`, or full-width accepted); writes
  `log/cycle_cost_<s>_<e>.txt`.
- `scripts/asm_sweep.sh` — O0–O3/Os sweep over input values, diffs vs a baseline.
- `scripts/instr_counter.sh` — counts instruction mnemonics in firmware.elf
  (whole or between two labels); output `log/instr_count.log`.
- `serv_project/sim_wave.sh` — build+simulate then open the VCD in GTKWave.
- `scripts/run_popcount_test.sh` / `scripts/reproduce_range_popcount.sh` — popcount
  correctness helpers (default SERV_DIR `fusesoc_libraries/serv_v1.5_rtl`).

### Program layout & termination conventions (teacher-facing)
- Program folders live under `Codespace/SERV_codespace/`; each needs a `startup.S`
  (template: `Codespace/SERV_codespace/build_codes/startup.S`), which sets
  `sp = 8192`, raises the GPIO, calls `main()`, then on return writes `0x90000000`
  (HALT) and loops — the SoC stops the simulation on that write.
- Firmware flags: `-march=rv32i -mabi=ilp32 -O2 -static -nostdlib -nostartfiles
  -ffreestanding`. Assembly files are linked before C so `_start` is at 0.
- Custom popcount (v1 / v1.5 RTL only) is invoked from C via:
  ```c
  volatile static unsigned int popcnt_custom(unsigned int val) {
      unsigned int rd;
      asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                   : "=r"(rd) : "r"(val));
      return rd;
  }
  ```
