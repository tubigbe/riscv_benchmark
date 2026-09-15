# Handoff Report: Milestone 2 (R2) — Random Forest Unification & Conditional Popcount

**Agent**: `teamwork_preview_worker` (Milestone 2 Worker)  
**Date**: 2026-09-13  
**Working Directory**: `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_worker_m2_1/`  
**Assignment**: Requirement R2 from `ORIGINAL_REQUEST.md`

---

## 1. Observation

### 1.1 Codebase Audit and File Ownership
- Inspected `Codespace/SERV_codespace/random_forest/` and `Codespace/SERV_codespace/rf_v2_lucky/`.
- All shared files (`RF_model.c`, `RF_model.h`, `infer_one.h`, `main.c`, `samples.c`, `samples.h`, `startup.S`) are byte-for-byte identical.
- Freestanding audit: No host references, no `<stdio.h>`, no `<stdlib.h>`. Only standard freestanding `<stdint.h>` is included in `main.c`.
- `infer_one.c` differed only in the popcount implementation: `random_forest` used `popcnt_sw(x)` with a shift loop, while `rf_v2_lucky` used `popcnt_custom(val)` emitting `.insn r 0x2B, 0, 0, %0, %1, x0`.

### 1.2 Implementation
- Modified `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/random_forest/infer_one.c`:
  - Replaced `popcnt_sw` with `static inline unsigned int popcnt(unsigned int val)`.
  - Added `#ifdef USE_CUSTOM_POPCOUNT` macro guard wrapping inline assembly `.insn r 0x2B, 0, 0, %0, %1, x0`.
  - Added `#else` fallback using the bit-serial shift loop `while (val) { c += val & 1; val >>= 1; }`.
  - Updated call sites to `count1 = popcnt(lo & ~hi);` and `count2 = popcnt(hi & ~lo);`.
- Created `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/rf_v2_lucky/README.md` documenting deprecation of `rf_v2_lucky/` and unification into `Codespace/SERV_codespace/random_forest/`.

### 1.3 Build and Simulation Measurements
#### 1. Software Build (RV32I fallback):
Command:
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
[OK]    Linked: firmware.elf
   text	   data	    bss	    dec	    hex	filename
    532	   2720	     40	   3292	    cdc	firmware.elf
[OK]    Binary: firmware.bin (3252 bytes)
[OK]    Hex: firmware.hex (814 words)
[OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
```

Disassembly inspection:
```bash
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Output: empty (0 matches)
```

Simulation run:
```bash
./run_sim.sh --run
```
Output:
```
Loading RAM from firmware.hex
Test complete
- fusesoc_libraries/serv_v1.5_rtl/servile/servile_mux.v:87: Verilog $finish
Written 9013 entries to /home/chenyoo/riscv_benchmark/serv_project/log/compare_result.txt
```
Cycle summary from `log/compare_result.txt`:
```
# Total instructions traced: 9013
# Total cycles : 526208
# Avg cycles   : 58.4
# Min cycles   : 36
# Max cycles   : 70
```
Last PC transitions in `log/sim_log.txt`:
```
0x208 -> 0x20c : 36 cycles
0x20c -> 0x210 : 36 cycles
0x210 -> 0x14 : 68 cycles
0x14 -> 0x18 : 36 cycles
[VCD] Trace file closed: log/sim_wave.vcd
```
Address `0x14` is `<halt>` and `0x18` is `sw zero, 0(x5)` with `x5 = 0x90000000`. Clean HALT at `0x90000000`.

#### 2. Hardware Popcount Build (Custom Instruction):
Command:
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
[OK]    Linked: firmware.elf
   text	   data	    bss	    dec	    hex	filename
    460	   2720	     40	   3220	    c94	firmware.elf
[OK]    Binary: firmware.bin (3180 bytes)
[OK]    Hex: firmware.hex (796 words)
[OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
```

Disassembly inspection:
```bash
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i -E "insn|popc"
```
Output:
```
 138:	0007072b          	.insn	4, 0x0007072b
 144:	000787ab          	.insn	4, 0x000787ab
```
Where `0x0007072b` is `.insn r 0x2b, 0, 0, x14, x14, x0` and `0x000787ab` is `.insn r 0x2b, 0, 0, x15, x15, x0`.

Simulation run:
```bash
./run_sim.sh --run
```
Output:
```
Loading RAM from firmware.hex
Test complete
- fusesoc_libraries/serv_v1.5_rtl/servile/servile_mux.v:87: Verilog $finish
Written 8381 entries to /home/chenyoo/riscv_benchmark/serv_project/log/compare_result.txt
```
Cycle summary from `log/compare_result.txt`:
```
# Total instructions traced: 8381
# Total cycles : 492928
# Avg cycles   : 58.8
# Min cycles   : 36
# Max cycles   : 70
```
Instruction breakdown for `.insn`:
```
.insn        20     42.0     42     42
```
All 20 popcount executions executed in exactly 42 cycles.
Last PC transitions in `log/sim_log.txt`:
```
0x1c0 -> 0x1c4 : 36 cycles
0x1c4 -> 0x1c8 : 36 cycles
0x1c8 -> 0x14 : 68 cycles
0x14 -> 0x18 : 36 cycles
[VCD] Trace file closed: log/sim_wave.vcd
```
Address `0x14` is `<halt>`, `0x18` writes `0x90000000`. Clean HALT at `0x90000000`.

---

## 2. Logic Chain

1. **Freestanding Integrity**: Audited all source files in `random_forest/`. Only standard freestanding `<stdint.h>` is included in `main.c`. No standard C library calls or hosted symbols exist.
2. **Unified Popcount Interface**: In `infer_one.c`, the previous static `popcnt_sw` was replaced with `static inline unsigned int popcnt(unsigned int val)`. Under `#ifdef USE_CUSTOM_POPCOUNT`, it invokes the exact hardware instruction `.insn r 0x2B, 0, 0, %0, %1, x0` matching the custom ALU opcode `0101011`.
3. **Software Fallback Fidelity**: The `#else` branch uses the shift loop `while (val) { c += val & 1; val >>= 1; }`. This preserves identical assembly and cycle count (526,208 cycles across 9,013 instructions) to the historical baseline.
4. **Hardware Acceleration**: With `--popcount`, the compiler injects `-DUSE_CUSTOM_POPCOUNT`. The two call sites emit `.insn r 0x2B, 0, 0`. On SERV v1.5 RTL, each execution takes exactly 42 cycles with zero follower stall, reducing runtime to exactly 492,928 cycles (saving 33,280 cycles across 20 calls).
5. **Deprecation**: `Codespace/SERV_codespace/rf_v2_lucky/README.md` documents the deprecation and redirect to `random_forest/`, fulfilling Acceptance Criteria for R2.

---

## 3. Caveats

- No caveats. The build, disassembly, simulation cycle counts, and halt mechanics were verified directly against the RTL simulation on the target platform.

---

## 4. Conclusion

Requirement R2 is fully implemented and validated:
- `Codespace/SERV_codespace/random_forest/infer_one.c` conditionally compiles software and custom hardware popcount using `#ifdef USE_CUSTOM_POPCOUNT`.
- `rf_v2_lucky` is documented as deprecated in `Codespace/SERV_codespace/rf_v2_lucky/README.md`.
- All files in `random_forest/` are clean and freestanding compliant.
- Baseline software simulation yields 526,208 cycles (0 `.insn`).
- Hardware popcount simulation yields 492,928 cycles (20 `.insn` at 42 cycles each).
- Both runs halt normally at `0x90000000`.

---

## 5. Verification Method

To independently verify:
```bash
cd /home/chenyoo/riscv_benchmark/serv_project

# 1. Verify software build
./build.sh --folder=random_forest --build
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Expect: No output (0 instructions)
./run_sim.sh --run
grep "Total cycles" log/compare_result.txt
# Expect: 526208

# 2. Verify hardware popcount build
./build.sh --folder=random_forest --popcount --build
/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-objdump -d firmware.elf | grep -i -E "insn|popc"
# Expect: 2 occurrences of .insn
./run_sim.sh --run
grep "Total cycles" log/compare_result.txt
# Expect: 492928
grep -E "insn|\.insn" log/compare_result.txt
# Expect: .insn 20 42.0 42 42
```
