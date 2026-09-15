# Plan: SERV ML Benchmarks Optimization & Unification

## Architecture & Project Structure
- `serv_project/build.sh`: Main build wrapper for cross-compiling firmware.
- `serv_project/run_sim.sh`: Simulates Verilator model and runs benchmarks.
- `Codespace/SERV_codespace/`:
  - `random_forest/`: Target unified directory for Random Forest benchmark.
  - `rf_v2_lucky/`: Candidate for unification/deprecation.
  - `BNN/`: BNN benchmark.
  - `Tsetin_Machine/`: Tsetlin Machine benchmark.
  - `build_codes/startup.S`: Standard fallback startup file.
- `serv_project/fusesoc_libraries/serv_v1.5_rtl/`: SERV v1.5 RTL variant with 42-cycle popcount.

## Milestones & Work Items

### Milestone 0: Survey & Codebase Exploration
- Objectives:
  - Explore `serv_project/build.sh`, `Codespace/SERV_codespace/random_forest`, `rf_v2_lucky`, `BNN`, `Tsetin_Machine`, and `build_codes/startup.S`.
  - Check how BNN and Tsetin_Machine use `USE_CUSTOM_POPCOUNT`.
  - Verify simulation commands and options.
- Deliverables: Explorer survey report with exact file differences, flag definitions, and plan.

### Milestone 1 (R1): Build Script Extension & Startup Fallback
- Objectives:
  - Modify `serv_project/build.sh` to add `--popcount` option.
  - When `--popcount` is provided, append `-DUSE_CUSTOM_POPCOUNT` to `CFLAGS`.
  - Check if target folder contains any `.s` or `.S` files. If not, link `Codespace/SERV_codespace/build_codes/startup.S`.
  - Preserve all existing arguments (`--folder`, `--build`, `--run`, `--serv-dir`, etc.).
- Deliverables: Worker implementation, Reviewer/Challenger/Auditor verification.

### Milestone 2 (R2): Random Forest Code Unification
- Objectives:
  - Unify `random_forest` and `rf_v2_lucky`.
  - Implement `#ifdef USE_CUSTOM_POPCOUNT` in `random_forest/infer_one.c` (switching between software popcount and `.insn r 0x2B, 0, 0`).
  - Verify clean freestanding build (no `stdio.h`, no missing symbols).
  - Archive/deprecate `rf_v2_lucky`.
- Deliverables: Worker implementation, Reviewer/Challenger/Auditor verification.

### Milestone 3 (R3): Benchmark Execution & Cycle Count Comparison Report
- Objectives:
  - Execute 6 benchmark simulations on SERV v1.5 RTL (`fusesoc_libraries/serv_v1.5_rtl`):
    1. RF SW: `--folder=random_forest --build` -> `run_sim.sh`
    2. RF HW: `--folder=random_forest --popcount --build` -> `run_sim.sh`
    3. BNN SW: `--folder=BNN --build` -> `run_sim.sh`
    4. BNN HW: `--folder=BNN --popcount --build` -> `run_sim.sh`
    5. TM SW: `--folder=Tsetin_Machine --build` -> `run_sim.sh`
    6. TM HW: `--folder=Tsetin_Machine --popcount --build` -> `run_sim.sh`
  - Ensure all 6 runs terminate at normal HALT (`0x90000000`).
  - Record exact cycle counts from simulation output / logs.
  - Compute speedup percentages.
  - Produce comprehensive comparison report in markdown.
- Deliverables: Worker execution logs, Reviewer/Challenger/Auditor verification, final report.

### Milestone 4: Final Verification & Victory Claim
- Objectives:
  - Check all acceptance criteria.
  - Prepare victory summary and evidence for the parent agent.
