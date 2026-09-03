# AGENTS.md — SERV RISC-V Popcount Optimization

## Project Overview

**SERV** — the world's smallest RISC-V CPU. This project compiles firmware, runs it on a Verilator simulation of the SERV SoC, and produces detailed per-instruction cycle-cost reports.

**Key goal**: Reduce custom popcount instruction cycle count from **68 cycles** to **≤50 cycles**.

**Status: ACHIEVED** — the custom popcount instruction now runs at **42 cycles** and produces correct results (verified by memory store + UART print). Saved as git tag **`v1.5_temp`**.

## ⚠️ IMPORTANT — 优化范围（先看这个）

**下一步优化只需看一个文件夹的 RTL**：
```
serv_project/fusesoc_libraries/serv/rtl/   ← 只改这里的 .v 文件
```

**不要看**（它们不是优化目标，读了浪费时间）：
- `serv_project/fusesoc_libraries/serv_bne/`（队友的 BNE 早退版，另一个优化方向）
- `serv_project/fusesoc_libraries/serv_rtl_origin/`（原始 SERV，无优化）
- `serv/rtl/` 之外的子目录：`serv/servile/`、`serv/servant/`、`serv/bench/`、`serv/sw/`（是通用基础设施/测试台，只读不改）
- `Codespace/`、`serv_project/scripts/`、其它顶层目录

> 涉及 popcount 写回的核心文件：`serv_state.v`、`serv_top.v`、`serv_rf_ram_if.v`、`serv_customized_alu.v`、`serv_customized_state.v`（都在 `serv/rtl/` 里）。
> 一个例外：`servile/servile.v` 里有 `i_rf_wr_busy` 的接线（真实数据路径），改 `serv_rf_ram_if`/`serv_top` 端口时要同步确认它。

## Current Design (v1.5_temp, commit `32f3f64`)

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

### Writeback (serv_top.v — bypasses the main ALU)

The popcount result is **not** routed through the main ALU. Instead:

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
| `custom_wr_active` / `wr_timer` / `custom_rd` | serv_top.v | one-shot writeback window + latched rd |
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

- `serv_project/fusesoc_libraries/serv/rtl/serv_customized_alu.v` — 6-bit `pr_partial` accumulator, `o_serial` output
- `serv_project/fusesoc_libraries/serv/rtl/serv_customized_state.v` — `i_init` → `o_mode`/`o_clr` (mode gated on `i_cnt_en`)
- `serv_project/fusesoc_libraries/serv/rtl/serv_state.v` — stage-2 control, counter, write/read requests
- `serv_project/fusesoc_libraries/serv/rtl/serv_top.v` — writeback bypass mux (`o_wdata0`/`o_wen0`/`o_wreg0`)
- `serv_project/fusesoc_libraries/serv/rtl/serv_rf_ram_if.v` — `o_wr_busy`
- `serv_project/fusesoc_libraries/serv/servile/servile.v` — **real** datapath wiring of `i_rf_wr_busy`
- `serv_project/fusesoc_libraries/serv/rtl/serv_decode.v` — identifies custom instructions (opcode `01010`)

## Git State

- **serv repo** (RTL): tag **`v1.5_temp`** = commit `32f3f64`. **Working tree has an uncommitted fix on top** (`serv_state.v`: `custom_wr_drain` scoping, bug 7, 2026-09-03) — 499281 → 493488. Earlier: `29e4e38` (gating removal), `6a7f684` (initial fixed-6-cycle), `f808bc5` (v1.5 broken).
- **top repo** (firmware/scripts): main = `b0a8fd0`.
- v1 RTL snapshot kept at `serv_project/serv_rtl_v1/` (gitignored); results saved as `log/v1_results` (68 cyc/insn, 666 total) and `log/v1.5_results` (42 cyc/insn, 614 total).
- `Codespace/SERV_codespace/Codehub/popcount.c` — older software/custom comparison test (reference only).

## Verification Outputs

- `log/sim_log.txt` — PC transitions with cycle counts per instruction
- `log/trace_dump.txt` — Symbol-resolved PC trace
- `log/compare_result.txt` — Merged trace with per-instruction cycle info and summary stats
- `log/sim_wave.vcd` — full waveform (GTKWave) for RTL debugging
- `log/popcount_test.txt` — popcount test results (pass/fail per value)

## Next Optimization Direction (2026-09-03) — 写回串行化（已收窄）

### 问题（2026-09-02 原版 → 2026-09-03 已修复全局 +1，见 bug 7）

`.insn`（popcount）自身 42 cycles ✓，但**紧随其后的那一条指令被写回拖慢 ~28 拍**：

- 证据：`log/C_v2_popcount_v15fixed.txt`（修复后的 v1.5）里，紧跟 `.insn`（0x138）的 `not`（0x13c）是 **64 cycles**，而前面是普通 `and` 的 `not`（0x130）是 **36 cycles**。**只有紧跟 `.insn` 的那一条**受影响（20 条，全是 `not`/`add`），其余 8341 条普通指令与 v1 RTL 逐拍一致。
- A/B 测量（原始/BNE，无 popcount）里 `not` 全是 36。
- 原因：popcount 写回窗口 `custom_wr_active`（36 拍）在指令自身结束后仍在 drain（带外写回），下一条指令的 RF 读被 `rf_rreq_pending`（现在只在 `custom_wr_drain` 期间挂起）延迟到写回清掉才开始 → 36 + ~28 写回等待 = 64。

### 目标

让 popcount 写回和后续指令执行**真正重叠**，收回那 ~28 拍。`.insn` 有效成本目前 ≈ 42 + 28 = ~70，重叠后应回到 ~42 附近。当前修复版总周期 493488 ≈ v1 RTL 的 493448（差 40 = 20×(.insn 省 26 - 跟随者多付 28)），popcount 本身快但写回串行化把它抵消了。

### 难点（之前踩过的坑）

- 之前尝试"不延迟 RF 读"（去掉串行化）→ 写回被后续指令的读重置 `rcnt`，**结果写错**（0x4AC8 之类）。
- 所以不能简单删 `rf_rreq_pending`；需要更精细的 RF 读写协调。

### 候选思路（未验证）

1. **RF 读写解耦**：给 `serv_rf_ram_if` 的读/写用独立的计数器/时序，让读可以在写回进行中发起而不重置写回的 `rcnt` 对齐。改动在 `serv/rtl/serv_rf_ram_if.v`。
2. **写回数据与 `o_rd` 解耦**：已实现（`o_wdata0 = custom_wr_active ? cus_serial : rf_wdata0`）。若读写能解耦，后续指令的 ALU 在 `o_rd` 上活动就不会污染写回。
3. **缩短写回窗口**：`custom_wr_active` 现在 36 拍（覆盖整个 32-bit 串行 RF 写）。能否只在 count 移出那 6 拍写低字、高位强制清零，缩短窗口？需要改 `serv_top.v` 的 `o_wen0`/`o_wreg0`/`o_wdata0` 逻辑 + `serv_rf_ram_if.v`。

### 验证方法

- 复现：`./serv_project/run_sim.sh --serv-dir=fusesoc_libraries/serv`（popcount 版）跑 v2 固件，看 `log/compare_result.txt` 里 `.insn` 后一条指令是否仍 ~63。
- 目标：改完后下一条指令回到 ~36-40，且 popcount 结果仍正确（`C` 测量 total cycles 应明显下降）。

### 相关测量存档

- `log/A_v1_origin.txt` — v1 on 原始 SERV，Total cycles 526208
- `log/D_v1_fixed15.txt` — v1 on v1.5_fixed，Total cycles 526208（9013 条与 A 逐行 **0 差** → 纯 RV32I 路径与原版完全一致，作为修复正确性的回归证据）
- `log/B_v1_bne.txt` — v1 on BNE，Total cycles 493157
- `log/C_v2_popcount_v1rtl.txt` — **C 官方测量**：v2 on v1 RTL（`serv_rtl_v1`，68-cycle .insn），Total cycles 493448 ← 用这个
- `log/C_v2_popcount_v15fixed.txt` — v2 on 修复后的 v1.5（`custom_wr_drain` fix），.insn 42，Total cycles 493488（全局 +1 已除，仅 20 条跟随者付写回串行化）
- `log/C_v2_popcount.txt` — **作废**（v1.5 writeback bug 污染测量），v2 on v1.5，499281，仅供对照

> 注意：v1 RTL 虽然 `.insn` 是 68 cycles（v1.5 是 42），但总周期反而略低（493448 < 493488），因为 v1 **没有** v1.5 的写回串行化（后续指令不被拖慢 ~28 拍）。v1.5 的写回串行化代价真实存在，是下一步优化要解决的目标。
