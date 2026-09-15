# Context: SERV RISC-V ML Benchmark Optimization & Unification

## Background
- Repository: `/home/chenyoo/riscv_benchmark`
- System: SERV RISC-V core with v1.5 custom popcount hardware support (42-cycle in-window writeback).
- Machine Learning Benchmarks to test on SERV v1.5 RTL (`fusesoc_libraries/serv_v1.5_rtl`):
  1. `random_forest`
  2. `BNN`
  3. `Tsetin_Machine`

## Requirements Overview
- **R1 (Build Script & Startup Integration)**:
  - Extend `serv_project/build.sh` to accept `--popcount` flag which adds `-DUSE_CUSTOM_POPCOUNT` to `CFLAGS`.
  - Add fallback logic: if target benchmark directory has no `.s`/`.S` assembly file, automatically link `Codespace/SERV_codespace/build_codes/startup.S`.
  - Retain backwards compatibility with `--folder=...`, `--build`, `--run`, `--serv-dir=...`.
- **R2 (C Code Macro Unification for Random Forest)**:
  - Merge `Codespace/SERV_codespace/random_forest` and `Codespace/SERV_codespace/rf_v2_lucky` into unified `random_forest`.
  - In `infer_one.c`, use `#ifdef USE_CUSTOM_POPCOUNT` to switch between custom instruction (`.insn r 0x2B, 0, 0`) and software popcount, matching BNN and Tsetin_Machine conventions.
  - Ensure freestanding build without host `stdio.h` or undefined symbols.
  - Deprecate/archive redundant `rf_v2_lucky`.
- **R3 (Benchmark Execution & Cycle Count Measurement)**:
  - Run all 3 workloads on SERV v1.5 RTL (`fusesoc_libraries/serv_v1.5_rtl`) across both modes (Software vs Custom Popcount) = 6 runs total.
  - Record total simulation cycle count for each of the 6 runs from testbench termination (normal HALT `0x90000000`).
  - Produce structured comparison report in Markdown with cycle counts and speedup percentages.
