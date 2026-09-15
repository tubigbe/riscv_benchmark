# Empirical Challenge Report — Milestone 2 (Requirement R2)

**Agent**: `teamwork_preview_challenger_m2_1`  
**Role**: Critic / Specialist (Empirical Challenger)  
**Task**: Empirically challenge and verify Requirement R2 (Random Forest Unification & Simulation)  
**Date**: 2026-09-13T00:38:40Z  
**Verdict**: **APPROVE**

---

## 1. Observation

### 1.1 Source Code Audit (`Codespace/SERV_codespace/random_forest/infer_one.c`)
In `Codespace/SERV_codespace/random_forest/infer_one.c` lines 3-18:
```c
static inline unsigned int popcnt(unsigned int val)
{
#ifdef USE_CUSTOM_POPCOUNT
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
#else
    unsigned int c = 0;
    while (val) {
        c += val & 1;
        val >>= 1;
    }
    return c;
#endif
}
```
- The `#ifdef USE_CUSTOM_POPCOUNT` macro cleanly toggles between the custom `.insn r 0x2B, 0, 0` instruction and the software bitwise shift fallback.
- Header inclusions across all files in `Codespace/SERV_codespace/random_forest/` are clean and freestanding (`stdint.h`, `RF_model.h`, `infer_one.h`, `samples.h`). Zero occurrences of host `stdio.h` were confirmed via `grep -rn "stdio" Codespace/SERV_codespace/random_forest/`.
- `Codespace/SERV_codespace/rf_v2_lucky/README.md` documents that `rf_v2_lucky` has been deprecated and unified into `random_forest/`.

---

### 1.2 Step 1: Software Mode Empirical Verification
Command executed:
```bash
cd /home/chenyoo/riscv_benchmark/serv_project
./build.sh --folder=random_forest --build
```
Build output:
```
[INFO]  Building firmware...
[INFO]  Folder: ../Codespace/SERV_codespace/random_forest
[INFO]  Sources (assembly → C):
[INFO]    ../Codespace/SERV_codespace/random_forest/startup.S
[INFO]    ../Codespace/SERV_codespace/random_forest/RF_model.c
[INFO]    ../Codespace/SERV_codespace/random_forest/infer_one.c
[INFO]    ../Codespace/SERV_codespace/random_forest/main.c
[INFO]    ../Codespace/SERV_codespace/random_forest/samples.c
[INFO]  Compiling + linking -> firmware.elf
[OK]    Linked: firmware.elf
   text    data     bss     dec     hex filename
    532    2720      40    3292     cdc firmware.elf
[INFO]  objcopy -> firmware.bin
[OK]    Binary: firmware.bin (3252 bytes)
[INFO]  makehex -> firmware.hex
[OK]    Hex: firmware.hex (814 words)
[OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
```

Disassembly inspection:
```bash
riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Verbatim Output: Empty (0 matches)
```

Simulation execution:
```bash
./obj_dir_custom/Vservant_sim +firmware=firmware.hex +vcd=1 +trace_pc=1
```
Simulation output:
```
Loading RAM from firmware.hex
9052 output q is ON
Test complete
- src/award-winning_serv_servile_1.4.0/servile/servile_mux.v:87: Verilog $finish
```
Simulation halt: Clean halt at address `0x90000000` via Wishbone write (`sw zero, 0(t0)` at `startup.S:24`, PC `0x18`).

Cycle and trace analysis (`trace.vcd` / `log/compare_result.txt`):
- Total raw transitions before halt: 11,544
- Last PC transition: `0x14 -> 0x18 : 36 cycles` (Store to `0x90000000`)
- Total simulation cycles: **526,208 cycles** (526,172 elapsed cycles + 36-cycle halt writeback = 526,208).
- Exactly matches historical references `log/A_v1_origin.txt` (526,208 cycles) and `log/D_v1_fixed15.txt` (526,208 cycles).
- Instruction count: 0 `.insn` instructions executed.
- Output correctness: Inspected `result_array` writes in RAM from `trace.vcd` at `0x00000cb4`:
  `[2, 2, 1, 2, 2, 2, 2, 0, 0, 1]` — 100% matches `predicted_class.txt`.

---

### 1.3 Step 2: Hardware Popcount Mode Empirical Verification
Command executed:
```bash
cd /home/chenyoo/riscv_benchmark/serv_project
./build.sh --folder=random_forest --popcount --build
```
Build output:
```
[INFO]  Building firmware...
[INFO]  Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)
[INFO]  Folder: ../Codespace/SERV_codespace/random_forest
[INFO]  Sources (assembly → C):
[INFO]    ../Codespace/SERV_codespace/random_forest/startup.S
[INFO]    ../Codespace/SERV_codespace/random_forest/RF_model.c
[INFO]    ../Codespace/SERV_codespace/random_forest/infer_one.c
[INFO]    ../Codespace/SERV_codespace/random_forest/main.c
[INFO]    ../Codespace/SERV_codespace/random_forest/samples.c
[INFO]  Compiling + linking -> firmware.elf
[OK]    Linked: firmware.elf
   text    data     bss     dec     hex filename
    460    2720      40    3220     c94 firmware.elf
[INFO]  objcopy -> firmware.bin
[OK]    Binary: firmware.bin (3180 bytes)
[INFO]  makehex -> firmware.hex
[OK]    Hex: firmware.hex (796 words)
[OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
```

Disassembly inspection:
```bash
riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Verbatim Output:
 138:	0007072b          	.insn	4, 0x0007072b
 144:	000787ab          	.insn	4, 0x000787ab
```
Exactly two custom instruction sites compiled corresponding to `popcnt(lo & ~hi)` and `popcnt(hi & ~lo)`.

Simulation execution:
```bash
./obj_dir_custom/Vservant_sim +firmware=firmware.hex +vcd=1 +trace_pc=1
```
Simulation output:
```
Loading RAM from firmware.hex
9052 output q is ON
Test complete
- src/award-winning_serv_servile_1.4.0/servile/servile_mux.v:87: Verilog $finish
```

Cycle and trace analysis (`trace.vcd` / `log/compare_result.txt`):
- Total raw transitions before halt: 10,912
- Last PC transition: `0x14 -> 0x18 : 36 cycles` (Store to `0x90000000`)
- Total simulation cycles: **492,928 cycles** (492,892 elapsed cycles + 36-cycle halt writeback = 492,928).
- Exactly matches historical reference `log/C_v2_popcount_v15lucky.txt` (492,928 cycles).
- Popcount instruction statistics in `compare_result.txt`:
  ```
  # Instr     Count      Avg    Min    Max
  # --------  -----  -------  -----  -----
    .insn        20     42.0     42     42
  ```
- Every single one of the 20 `.insn` executions ran in **strictly 42.0 cycles** (Min: 42, Max: 42, StdDev: 0.0).
- Follower stall audit: Verified instruction immediately following `.insn` at `0x13c` (`not`) and `0x148` (`add`):
  ```
    0x00000138  0x0000013c  .insn         42
    0x0000013c  0x00000140  not           36
    0x00000140  0x00000144  and           36
    0x00000144  0x00000148  .insn         42
    0x00000148  0x0000014c  add           36
  ```
  Follower instructions execute at exactly 36 cycles. The in-window writeback incurs **zero follower stall penalty**.
- Output correctness: Inspected `result_array` writes in RAM from `trace.vcd` at `0x00000c6c`:
  `[2, 2, 1, 2, 2, 2, 2, 0, 0, 1]` — 100% matches `predicted_class.txt`.

---

### 1.4 Step 3: Speedup and Cycle Difference Validation
- **Software Cycles**: 526,208
- **Hardware Cycles**: 492,928
- **Difference**: $526,208 - 492,928 = \mathbf{33,280\text{ cycles saved}}$
- **Speedup Ratio**: $526,208 / 492,928 = \mathbf{1.0675\times}$ (+6.3245% speedup)

---

## 2. Logic Chain

1. **Unification Integrity**: Observation 1.1 establishes that `random_forest/infer_one.c` implements `#ifdef USE_CUSTOM_POPCOUNT`, standardizing popcount selection across Random Forest, BNN, and Tsetlin Machine. Header inclusions are freestanding and clean.
2. **Software Mode Compliance**: Observation 1.2 proves that without `--popcount`, GCC compiles purely standard RV32I instructions (0 `.insn` instructions). Execution halts cleanly on Wishbone write to `0x90000000` at exactly 526,208 cycles, reproducing the baseline `A_v1_origin.txt` and `D_v1_fixed15.txt`.
3. **Hardware Mode Compliance**: Observation 1.3 proves that with `--popcount`, `-DUSE_CUSTOM_POPCOUNT` is injected, compiling exactly 2 `.insn` call sites in `infer_one.c`. During 10 samples of inference, `.insn` executes exactly 20 times. Each execution takes exactly 42 cycles with in-window writeback and 0 follower stall penalty, completing at 492,928 cycles, reproducing `C_v2_popcount_v15lucky.txt`.
4. **Algorithmic Correctness**: Observations 1.2 and 1.3 confirm that the stored prediction vectors in RAM are identical (`[2, 2, 1, 2, 2, 2, 2, 0, 0, 1]`) and match `predicted_class.txt`.
5. **Metric Verification**: Observation 1.4 confirms the cycle difference of 33,280 cycles and a +6.32% speedup, fulfilling all acceptance criteria of Requirement R2.

---

## 3. Caveats

1. **Host Compilation Dependencies**: In Ubuntu Snap/container execution environments where host development headers (`libstdc++-dev`) are unmounted, rebuilding the Verilator C++ testbench from scratch via `run_sim.sh --build` requires an isolated build environment or container toolchain mounting. However, `run_sim.sh --run` executes the precompiled SERV Verilator model (`Vservant_sim`) without host C++ dependency issues.
2. **Workloads Covered**: This review challenged Requirement R2 (Random Forest). Full multi-workload execution of BNN and Tsetlin Machine across both modes is governed by Milestone 3 (Requirement R3).

---

## 4. Conclusion

**Verdict: APPROVE**

Requirement R2 is fully satisfied:
- `random_forest` is unified with clean `#ifdef USE_CUSTOM_POPCOUNT` support and zero host header dependencies.
- Redundant `rf_v2_lucky` has been cleanly documented and deprecated.
- Software mode halts at `0x90000000` with 0 `.insn` instructions and exactly 526,208 cycles.
- Hardware mode halts at `0x90000000` with 20 `.insn` executions at exactly 42 cycles each and exactly 492,928 cycles.
- Exactly 33,280 cycles are saved (+6.32% speedup).
- Algorithmic output accuracy is 100% verified against ground truth.

---

## 5. Verification Method

To independently reproduce and verify all empirical findings:

```bash
# 1. Setup environment
export PATH="/home/chenyoo/riscv_benchmark/tools/bin:/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin:$PATH"
cd /home/chenyoo/riscv_benchmark/serv_project

# 2. Software Mode Verification
./build.sh --folder=random_forest --build
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# (Must return 0 lines)
./run_sim.sh --run
# Verify HALT at 0x90000000 and total cycles = 526,208

# 3. Hardware Popcount Mode Verification
./build.sh --folder=random_forest --popcount --build
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# (Must return 2 lines: 0x0007072b and 0x000787ab)
./run_sim.sh --run
# Verify HALT at 0x90000000, 20 .insn executions at 42 cycles, and total cycles = 492,928
```
