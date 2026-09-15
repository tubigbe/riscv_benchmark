# Soft Handoff to Successor Orchestrator (Generation 2)

## 1. Milestone State
- **Milestone 0: Survey & Codebase Exploration** — **DONE**
  - All 3 survey reports generated and cataloged in `.agents/teamwork_preview_explorer_survey_{1,2,3}/report.md`.
- **Milestone 1: R1 Build Script Macro & Startup Integration** — **DONE (Gate Result: PASS)**
  - `serv_project/build.sh` updated to support `--popcount` (injects `-DUSE_CUSTOM_POPCOUNT` into `CFLAGS`).
  - Automatic fallback to standard SERV startup code (`Codespace/SERV_codespace/build_codes/startup.S`) when target folder lacks assembly sources (`${#ASM_SRCS[@]} == 0`).
  - `tools/lib/` created with `libisl.so.23*`, `libmpc.so.3*`, and `libmpfr.so.6*`. Zero references to `.agents/` remain in `build.sh`.
  - Full backwards compatibility with all CLI flags (`--folder`, `--serv-dir`, `--build`, `--run`, `--clear`, `--help`).
  - All verification reviews, challenges, and forensic audits passed with CLEAN status.
- **Milestone 2: R2 Random Forest C Code Macro Unification** — **DONE (Gate Result: PASS)**
  - `Codespace/SERV_codespace/random_forest/infer_one.c` unified using `#ifdef USE_CUSTOM_POPCOUNT` wrapping `.insn r 0x2B, 0, 0, %0, %1, x0` and `#else` bit-serial shift loop fallback (`popcnt(lo & ~hi)` and `popcnt(hi & ~lo)`).
  - 100% freestanding compliance verified (no `<stdio.h>`, no host symbols).
  - `Codespace/SERV_codespace/rf_v2_lucky/README.md` created to document deprecation and unification into `random_forest/`.
  - Both Software (526,208 cycles) and Hardware Popcount (492,928 cycles, 20 `.insn` at 42 cycles each) verified on SERV v1.5 RTL.
  - Reviewer 1, Reviewer 2, Challenger 1, Challenger 2, and Forensic Auditor all submitted APPROVE / CLEAN verdicts.
- **Milestone 3: R3 Benchmark Execution & Cycle Count Measurement** — **READY TO EXECUTE**
  - Run all 3 ML benchmarks (`random_forest`, `BNN`, `Tsetin_Machine`) on SERV v1.5 RTL across both modes (6 runs total).
  - Record cycle counts and produce comparison summary report.
- **Milestone 4: Acceptance Verification & Victory Claim** — **PENDING**
  - Final check of all acceptance criteria in `ORIGINAL_REQUEST.md` and victory notification to parent (`c5de3f87-845c-4a36-bd89-58327c07299a`).

## 2. Active Subagents
- None. All 17 subagents spawned in Generation 1 have completed their tasks and are retired.

## 3. Pending Decisions & Context
- Toolchain: Toolchain binaries are in `tools/riscv64/usr/bin/` and shared libraries in `tools/lib/`. `build.sh` automatically configures both `PATH` and `LD_LIBRARY_PATH`.
- RTL Target: Default RTL is `fusesoc_libraries/serv_v1.5_rtl/` (contains 42-cycle in-window writeback popcount).
- Reference cycle counts established during survey and verified in M1 & M2:
  - `random_forest`: SW = 526,208 cycles; HW = 492,928 cycles (33,280 cycles saved, +6.32% speedup)
  - `BNN`: SW = 68,206 cycles; HW = 63,876 cycles (4,330 cycles saved, +6.35% speedup)
  - `Tsetin_Machine`: SW = 331,434 cycles; HW = 302,538 cycles (28,896 cycles saved, +8.72% speedup)
  - All 6 configurations cleanly halt at `0x90000000`.

## 4. Remaining Work & Concrete Next Steps
1. Dispatch Worker M3 to:
   - Execute the 6 official benchmark runs using `serv_project/build.sh` and `serv_project/run_sim.sh --run`:
     1. RF SW: `./build.sh --folder=random_forest --build` -> `./run_sim.sh --run`
     2. RF HW: `./build.sh --folder=random_forest --popcount --build` -> `./run_sim.sh --run`
     3. BNN SW: `./build.sh --folder=BNN --build` -> `./run_sim.sh --run`
     4. BNN HW: `./build.sh --folder=BNN --popcount --build` -> `./run_sim.sh --run`
     5. TM SW: `./build.sh --folder=Tsetin_Machine --build` -> `./run_sim.sh --run`
     6. TM HW: `./build.sh --folder=Tsetin_Machine --popcount --build` -> `./run_sim.sh --run`
   - Archive each `compare_result.txt` log.
   - Record exact total simulation cycles and speedup ratios.
   - Generate the final Markdown comparison report table.
2. Dispatch Reviewer, Challenger, and Forensic Auditor for Milestone 3.
3. Gate Milestone 3: Verify all 6 runs halted at `0x90000000` with expected cycle counts and that report is complete.
4. Milestone 4: Final verification against `ORIGINAL_REQUEST.md` acceptance criteria.
5. Report victory back to caller parent `c5de3f87-845c-4a36-bd89-58327c07299a` via `send_message`.

## 5. Key Artifacts
- `/home/chenyoo/riscv_benchmark/ORIGINAL_REQUEST.md` — Authoritative requirements
- `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_orchestrator_1/plan.md` — Project plan
- `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_orchestrator_1/progress.md` — Progress tracker
- `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_orchestrator_1/BRIEFING.md` — Briefing & identity
- `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_orchestrator_1/GATE_STATUS.md` — Gating logs (M1 PASS, M2 PASS)
- `/home/chenyoo/riscv_benchmark/serv_project/build.sh` — Unified build script
- `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/random_forest/infer_one.c` — Unified popcount C source
- `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/rf_v2_lucky/README.md` — Deprecation documentation
- `/home/chenyoo/riscv_benchmark/tools/lib/` — Shared libraries for cross-toolchain
