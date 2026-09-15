# Handoff Report: Milestone 3 (R3) Simulation Infrastructure & Workload Survey

## 1. Observation

1. **`run_sim.sh` Analysis**:
   - Path: `/home/chenyoo/riscv_benchmark/serv_project/run_sim.sh`.
   - Line 69: `SERV_DIR="${SERV_DIR:-fusesoc_libraries/serv_v1.5_rtl}"`.
   - Lines 120-156: Assembles `VERILOG_SOURCES` including `serv_customized_alu.v` and `serv_customized_state.v` if present.
   - Lines 212-224: Compiles Verilator executable `Vservant_sim` into `obj_dir_custom/`.
   - Lines 250-265: Executes binary with `+firmware=firmware.hex +vcd=1 +trace_pc=1`, followed by `python3 scripts/trace_dump.py` and `python3 scripts/compare_traces.py`.
   - Output files: `log/sim_log.txt`, `log/sim_wave.vcd`, `log/trace_dump.txt`, `log/compare_result.txt`.

2. **SERV v1.5 RTL Popcount Architecture**:
   - Location: `/home/chenyoo/riscv_benchmark/serv_project/fusesoc_libraries/serv_v1.5_rtl/`.
   - `rtl/serv_state.v` Line 85:
     `wire custom_stage2_done = i_is_customized & !o_init & (o_cnt == 3'd1) & cnt_r[1] & o_cnt_en;`
   - `rtl/serv_state.v` Line 189:
     `assign o_cnt_done = ((o_cnt[4:2] == 3'b111) & cnt_r[3]) | custom_stage2_done;`
   - `rtl/serv_top.v` Lines 724-739:
     `assign o_wdata0 = is_customized ? (init ? {W{1'b0}} : cus_serial) : rf_wdata0;`
     `assign o_wen0 = custom_win ? 1'b1 : rf_wen0;`
   - Verifiable latency: 32 cycles Stage 1 + 6 cycles Stage 2 + 4 cycles early-fetch = 42 cycles total per popcount.

3. **Halt and Cycle Counting Mechanics**:
   - Wishbone Halt: `servile/servile_mux.v` line 67:
     `assign halt_en = i_wb_cpu_we & (i_wb_cpu_adr == sim_halt_adr);` (`sim_halt_adr = 32'h90000000`).
   - Line 87: `$finish;` triggers upon CPU writing to `0x90000000`.
   - In `scripts/sim_main.cpp` lines 157-176: Each PC transition records `current_cycle - start_cycle` to `log/sim_log.txt`.
   - In `scripts/compare_traces.py` lines 80-87: Summarizes total simulation cycles as `total = sum(cycle_values)`.

4. **Benchmark Workload Configurations & Results**:
   - `random_forest`:
     - SW: 9,013 instructions, **526,208 cycles** (matches historical `A_v1_origin.txt` and `D_v1_fixed15.txt`).
     - HW: 8,381 instructions, **492,928 cycles**, 20 `.insn` executions at strictly 42.0 cycles (matches historical `C_v2_popcount_v15lucky.txt`).
     - Saved: 33,280 cycles (+6.32%).
   - `BNN`:
     - SW: 1,327 instructions, **68,206 cycles**.
     - HW: 1,232 instructions, **63,876 cycles**, 3 `.insn` executions at strictly 42.0 cycles.
     - Saved: 4,330 cycles (+6.35%).
     - `helpers.c` line 37 already has `#ifdef USE_CUSTOM_POPCOUNT`.
   - `Tsetin_Machine`:
     - SW: 6,089 instructions, **331,434 cycles**.
     - HW: 5,495 instructions, **302,538 cycles**, 60 `.insn` executions at strictly 42.0 cycles.
     - Saved: 28,896 cycles (+8.72%).
     - `class_sum.c` line 21 already has `#ifdef USE_CUSTOM_POPCOUNT`.
   - All runs take < 2.0s runtime each, well below `MAX_CYCLES` (10,000,000) and `SIM_TIMEOUT` (300s).

5. **Toolchain Environment Nuance**:
   - `cc1` dynamically requires `libisl.so.23`, `libmpfr.so.6`, `libmpc.so.3`. In this snap environment, these libraries were missing until extracted into scratch/lib and added to `LD_LIBRARY_PATH`.

---

## 2. Logic Chain

1. **Step 1 (Simulation Infrastructure)**:
   Observation 1 establishes that `run_sim.sh` defaults to `serv_v1.5_rtl`, manages the Verilator build and run steps, outputs detailed per-instruction cycle data to `log/compare_result.txt`, and uses `trace_dump.py` and `compare_traces.py` for post-processing.

2. **Step 2 (RTL & Popcount Correctness)**:
   Observation 2 demonstrates that `serv_v1.5_rtl` implements a 42-cycle in-window writeback popcount. Observation 4 empirically validates this: in all three HW benchmark runs (`random_forest`, `BNN`, and `Tsetin_Machine`), every single invocation of `.insn` reports Avg: 42.0, Min: 42, Max: 42 with zero follower penalty.

3. **Step 3 (Halt & Total Cycle Count Integrity)**:
   Observation 3 verifies that `sw zero, 0(0x90000000)` triggers `$finish` in `servile_mux.v`. All transitions are recorded in `sim_log.txt` and summed in `compare_traces.py`. Because the CPU halts immediately upon write, the total cycles reported in `compare_result.txt` represents the exact CPU cycles from program start to halt.

4. **Step 4 (Workload Feasibility & Speedup)**:
   Observation 4 shows that all 6 configurations compile cleanly and simulate to halt within 0.2–1.5 seconds. The cycle counts confirm significant speedups from hardware popcount across all three models:
   - RF: 526,208 → 492,928 (-6.32%)
   - BNN: 68,206 → 63,876 (-6.35%)
   - TM: 331,434 → 302,538 (-8.72%)

---

## 3. Caveats

- BNN and Tsetlin Machine directories currently do not have local `startup.S` files; their successful simulation requires either the fallback to `Codespace/SERV_codespace/build_codes/startup.S` (as specified in Requirement R1) or linking `startup.S` explicitly.
- In `random_forest`, `infer_one.c` is currently split between `random_forest` (SW) and `rf_v2_lucky` (HW). Requirement R2 will unify these with `#ifdef USE_CUSTOM_POPCOUNT` exactly as BNN and TM have done.
- In this snap sandbox environment, `riscv64-unknown-elf-gcc` requires `libisl.so.23`, `libmpfr.so.6`, and `libmpc.so.3` in `LD_LIBRARY_PATH`.

---

## 4. Conclusion

1. The simulation framework (`run_sim.sh`, `sim_main.cpp`, `compare_traces.py`) and SERV v1.5 RTL are fully functional, stable, and verified.
2. The custom popcount instruction runs in exactly 42 cycles without overhead.
3. All 6 benchmark runs execute cleanly to HALT with zero timeouts, producing the definitive cycle counts:
   - Random Forest: 526,208 (SW) vs 492,928 (HW)
   - BNN: 68,206 (SW) vs 63,876 (HW)
   - Tsetlin Machine: 331,434 (SW) vs 302,538 (HW)
4. Milestone 3 (R3) can be completely satisfied as soon as R1 (`build.sh --popcount` + fallback `startup.S`) and R2 (`random_forest/infer_one.c` `#ifdef`) are in place.

---

## 5. Verification Method

1. **RTL Inspection**:
   Inspect `/home/chenyoo/riscv_benchmark/serv_project/fusesoc_libraries/serv_v1.5_rtl/rtl/serv_top.v` lines 724-742 and `serv_state.v` lines 85-88.
2. **Simulation Run**:
   In `/home/chenyoo/riscv_benchmark/serv_project`:
   ```bash
   ./run_sim.sh --run
   cat log/compare_result.txt | tail -n 25
   ```
3. **Report Verification**:
   Inspect full analysis report at:
   `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_explorer_survey_3/report.md`.
