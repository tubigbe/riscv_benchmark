# Empirical Challenge Report: Milestone 1 (R1) — Build Script & Startup Integration

**Agent**: `teamwork_preview_challenger_m1_2`  
**Working Directory**: `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_challenger_m1_2/`  
**Target File**: `/home/chenyoo/riscv_benchmark/serv_project/build.sh`  
**Verdict**: **APPROVE** (with 1 non-blocking pre-existing defect advisory)

---

## 1. Observation

Direct empirical tests were conducted on `/home/chenyoo/riscv_benchmark/serv_project/build.sh` with the project RISC-V toolchain (`riscv64-unknown-elf-gcc` 14.2.0, `GNU objdump` 2.45.50).

### Test 1: Argument Order Invariance
All 6 permutations of `--folder=BNN`, `--popcount`, and `--build` were executed:
```bash
./build.sh --popcount --folder=BNN --build
./build.sh --build --folder=BNN --popcount
./build.sh --folder=BNN --build --popcount
./build.sh --build --popcount --folder=BNN
./build.sh --popcount --build --folder=BNN
./build.sh --folder=BNN --popcount --build
```
Every permutation produced bit-identical output:
- `firmware.bin` MD5: `625d010d82443e6635f6f4beff7c6bf2` (1316 bytes)
- `firmware.hex` MD5: `3bf93ed229b8fd1cfae7fa7df0f0f582` (330 words)

The same invariance was verified for `Tsetin_Machine` across permutations:
- `firmware.bin` MD5: `e13a4b2a5617a7fd029701829b1d64ed` (1072 bytes)
- `firmware.hex` MD5: `de797679a51b0b6051f057a15d7fc2c3` (269 words)

### Test 2: Re-building after `--clear`
1. `./build.sh --clear` exited code 0:
   ```text
   [INFO]  Cleaning build artifacts...
   [OK]    Removed: firmware.elf / firmware.bin / firmware.hex / build_*.o / trace.*
   ```
   Confirmed `firmware.elf`, `firmware.bin`, and `firmware.hex` no longer exist on filesystem.
2. `./build.sh --folder=BNN --build` cleanly generated fresh artifacts:
   - `firmware.elf` (6788 bytes, modified `2026-09-13 00:19:23.922567827 +0100`)
   - `firmware.bin` (1372 bytes, MD5 `def21a02aa8dfc1b8ab1fa622cb3ccad`)
   - `firmware.hex` (3096 bytes, 344 words)
3. `./build.sh --clear` executed again, removing all artifacts.
4. `./build.sh --folder=BNN --popcount --build` re-built fresh hardware artifacts:
   - `firmware.elf` (6732 bytes, modified `2026-09-13 00:19:24.348626558 +0100`)
   - `firmware.bin` (1316 bytes, MD5 `625d010d82443e6635f6f4beff7c6bf2`)
   - `firmware.hex` (2970 bytes, 330 words)
5. Interaction test: `--clear` combined with `--build` (`./build.sh --clear --build` or `./build.sh --build --clear`) executes `do_clear` and exits with code 0 immediately, preventing partial builds.

### Test 3: Disassembly & Custom Instruction Verification
1. **`random_forest` Software Build**:
   `./build.sh --folder=random_forest --build`
   - Complete disassembly with `riscv64-unknown-elf-objdump -d firmware.elf` (133 instructions in text segment).
   - Grep for `.insn`: **0 occurrences**.
   - Grep for opcode `0x2b` (`[0-9a-f]{6}2b`): **0 occurrences**.
2. **`random_forest` Popcount Build**:
   `./build.sh --folder=random_forest --popcount --build`
   - Emits `[INFO] Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)`.
   - Compiles and links cleanly with exit code 0.
   - Text segment instructions are identical to software build because `random_forest/infer_one.c` has not yet integrated `#ifdef USE_CUSTOM_POPCOUNT` (scheduled for Milestone 2 / R2).
3. **Contrast with `BNN` and `Tsetin_Machine`**:
   - `BNN` SW: **0** `.insn` instructions.
   - `BNN` HW (`--popcount`): **2** `.insn` instructions emitted:
     ```text
     b8:  0005052b          .insn 4, 0x0005052b
     128: 0008082b          .insn 4, 0x0008082b
     ```
   - `Tsetin_Machine` SW: **0** `.insn` instructions.
   - `Tsetin_Machine` HW (`--popcount`): **6** `.insn` instructions emitted:
     ```text
     1bc: 000686ab          .insn 4, 0x000686ab
     1c4: 0006062b          .insn 4, 0x0006062b
     1d8: 000787ab          .insn 4, 0x000787ab
     1e4: 0006062b          .insn 4, 0x0006062b
     210: 000686ab          .insn 4, 0x000686ab
     21c: 0007072b          .insn 4, 0x0007072b
     ```

### Test 4: Error Handling & Boundary Cases
- Non-existent folder: `./build.sh --folder=nonexistent_foo --build` -> `[FAIL] Folder not found: ../Codespace/SERV_codespace/nonexistent_foo`, exit code 1.
- Invalid option: `./build.sh --foobar` -> `[FAIL] Unknown argument: --foobar (use --help for usage)`, exit code 1.
- Typo in flag: `./build.sh --popcnt` -> `[FAIL] Unknown argument: --popcnt (use --help for usage)`, exit code 1.
- Missing option value: `./build.sh --folder` -> `[FAIL] Unknown argument: --folder (use --help for usage)`, exit code 1.
- Empty folder: `./build.sh --folder=empty_test_dir --build` -> `[FAIL] No source files found in ../Codespace/SERV_codespace/empty_test_dir`, exit code 1.
- Missing firmware before run: `./build.sh --clear && ./build.sh --run` -> `[FAIL] Firmware not found: firmware.hex — run ./build.sh --build first`, exit code 1.
- Default invocation (no args) and `--help`: Displays usage guide and exits code 0.
- Trailing slash: `./build.sh --folder=BNN/ --build` -> Resolves folder properly and compiles cleanly, exit code 0.
- Invocation from repository root (`./serv_project/build.sh --folder=BNN --build`) -> Uses `cd "$SCRIPT_DIR"`, compiles cleanly, exit code 0.
- Entry symbol verification: Checked `_start` across all 4 suites (`build_codes`, `random_forest`, `BNN`, `Tsetin_Machine`) via `riscv64-unknown-elf-nm firmware.elf`. In all cases, `_start` is strictly at `0x00000000`.

### Adversarial Finding: `--serv-dir=DIR` Argument Latency
- Observation: In `serv_project/build.sh` lines 96–97:
  ```bash
  LDSCRIPT="$SERV_DIR/sw/link.ld"
  MAKEHEX="$SERV_DIR/sw/makehex.py"
  ```
  These variables are evaluated at top-level upon script invocation.
  In lines 344–355, command-line arguments are parsed:
  ```bash
  --serv-dir=*) SERV_DIR="${arg#*=}" ;;
  ```
  `SERV_DIR` is updated, but `LDSCRIPT` and `MAKEHEX` are never re-evaluated before `do_build()` executes.
- Empirical Proof: Running `bash -x ./build.sh --serv-dir=nonexistent_serv_dir --build` demonstrates GCC compiling with `-T fusesoc_libraries/serv_v1.5_rtl/sw/link.ld` and Python running `fusesoc_libraries/serv_v1.5_rtl/sw/makehex.py`, ignoring the command-line override.
- Root Cause: Pre-existing logic flaw dating from commit `8adc925` (2026-09-02), not introduced by Worker M1.
- Impact: Non-blocking for Milestone 1 because the active target SERV core is `fusesoc_libraries/serv_v1.5_rtl` (the default) and `link.ld` / `makehex.py` are bit-identical between variants. Recommended mitigation: move assignments into `do_build()`.

---

## 2. Logic Chain

1. **Argument Parsing Order**: Because argument parsing in `build.sh` (lines 344–355) stores incoming flags into state variables (`FOLDER`, `SERV_DIR`, `USE_POPCOUNT`, `DO_BUILD`, `DO_RUN`) and only executes actions (`do_build`, `do_run`) after the loop terminates, the ordering of flags is mathematically commutative. The empirical output hashes across all permutations for both BNN and TM confirmed exact identity.
2. **Re-build Integrity**: When `--clear` is executed, all downstream compiler outputs are removed. Subsequent invocations rebuild all targets (`.elf`, `.bin`, `.hex`) with new file modification timestamps. Furthermore, transitioning from SW to HW (`--popcount`) alters code generation, changing the binary size and hash, confirming that build outputs are never stale.
3. **Instruction Isolation**: In `random_forest`, the C source currently lacks `#ifdef USE_CUSTOM_POPCOUNT`. GCC RV32I compilation emits only base integer instructions, with 0 custom opcodes. When `--popcount` is provided, `build.sh` properly injects `-DUSE_CUSTOM_POPCOUNT` into `CFLAGS`, satisfying R1 acceptance criteria and preparing the build system for R2 code unification. In contrast, BNN and TM demonstrate that `-DUSE_CUSTOM_POPCOUNT` cleanly activates 2 and 6 custom popcount instructions respectively.
4. **Error Handling Integrity**: Testing malformed options, missing directories, and missing source files confirms that `set -euo pipefail` along with explicit directory checks (`[[ -d "$FOLDER_PATH" ]]`) and source count assertions (`[[ ${#SOURCES[@]} -eq 0 ]]`) intercept errors prior to invocation of the toolchain, returning standardized exit code 1 with actionable error messages.
5. **Precedence of Startup Assembly**: In bare-metal linking, the entry point must be at offset 0. By verifying that `${#ASM_SRCS[@]} -eq 0` triggers injection of `Codespace/SERV_codespace/build_codes/startup.S` as the first item of `ALL_SRCS`, symbol resolution places `_start` at `0x00000000` across all benchmarks.

---

## 3. Caveats

1. **Concurrency**: `build.sh` produces outputs in the fixed directory `serv_project/` (`firmware.elf`, `firmware.bin`, `firmware.hex`). If multiple agents or subtasks run `build.sh` simultaneously in parallel without separate output staging, intermediate file overwrites may occur.
2. **Simulation Phase (R3)**: This review tested the firmware build pipeline, flags, and static binary outputs. Full Verilator hardware execution and cycle count logging on SERV v1.5 are part of Milestone 3.

---

## 4. Conclusion

**Verdict: APPROVE**

The implementation of Requirement R1 in `serv_project/build.sh` is robust, backward-compatible, and fully complies with all specifications in `ORIGINAL_REQUEST.md`:
- Flag `--popcount` is accepted in any argument position and successfully defines `-DUSE_CUSTOM_POPCOUNT`.
- Automatic fallback to standard SERV `startup.S` functions seamlessly for assembly-less benchmarks (`BNN`, `Tsetin_Machine`), guaranteeing `_start` alignment at `0x00000000`.
- `--folder=random_forest --build` generates zero custom instructions; `--folder=random_forest --popcount --build` accepts the flag cleanly.
- Error handling on invalid arguments and non-existent paths is strict and fails with non-zero exit codes.
- The identified `--serv-dir` delayed evaluation defect is pre-existing and does not compromise Milestone 1 deliverables.

---

## 5. Verification Method

To independently verify all findings:

```bash
# Set up toolchain PATH
export PATH="/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin:/home/chenyoo/riscv_benchmark/tools/verilator/usr/bin:$PATH"
cd /home/chenyoo/riscv_benchmark/serv_project

# 1. Verify argument order invariance
./build.sh --popcount --folder=BNN --build
h1=$(md5sum firmware.hex | awk '{print $1}')
./build.sh --build --folder=BNN --popcount
h2=$(md5sum firmware.hex | awk '{print $1}')
[[ "$h1" == "$h2" ]] && echo "Order Invariant: PASS"

# 2. Verify clean and rebuild
./build.sh --clear
[[ ! -f firmware.hex ]] && echo "Clear: PASS"
./build.sh --folder=BNN --build
[[ -f firmware.hex ]] && echo "Rebuild: PASS"

# 3. Verify zero custom instructions in random_forest
./build.sh --folder=random_forest --build
riscv64-unknown-elf-objdump -d firmware.elf | grep -i "insn" || echo "RF SW 0 insn: PASS"

# 4. Verify popcount flag accepted
./build.sh --folder=random_forest --popcount --build

# 5. Verify error handling
./build.sh --folder=nonexistent_xyz --build || echo "Nonexistent folder error: PASS"
./build.sh --invalid_flag || echo "Invalid flag error: PASS"
```
