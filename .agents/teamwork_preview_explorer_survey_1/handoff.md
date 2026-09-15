# Handoff Report: Build System & Startup Code Integration Survey (M1 / R1)

**Agent**: `teamwork_preview_explorer`  
**Working Directory**: `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_explorer_survey_1/`  
**Handoff Type**: Hard (Investigation complete)  
**Related Report**: `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_explorer_survey_1/report.md`  

---

## 1. Observation

1. **`serv_project/build.sh` Options & Execution Flow**:
   - `build.sh` lines 313–326 parse arguments with a `case "$arg"` loop matching `--folder=*`, `--serv-dir=*`, `--build`, `--run`, `--clear`, `--help|-h`. Unknown arguments trigger `fail "Unknown argument: $arg"`.
   - Lines 84–90 define `ARCH=rv32i`, `ABI=ilp32`, `COMMON_FLAGS="-march=$ARCH -mabi=$ABI -static -nostdlib -nostartfiles -ffreestanding"`, `INCLUDES="-I$SCRIPT_DIR/../Codespace"`, `CFLAGS="-O2 $COMMON_FLAGS $INCLUDES"`, and `LDSCRIPT="$SERV_DIR/sw/link.ld"`.
   - Lines 160–163 reassign `INCLUDES="-I$SCRIPT_DIR/../Codespace -I$FOLDER_PATH"` and `CFLAGS="-O2 $COMMON_FLAGS $INCLUDES"`. There is no separate `LDFLAGS` variable; `-T "$LDSCRIPT"` is passed directly to `$CC` alongside `$CFLAGS`.
   - Lines 150–156 locate files using `EXT_PATTERN="*.s *.S *.c *.cc *.cpp *.cxx *.c++"`.
   - Lines 167–205 partition files into `ASM_SRCS` (matching `S|s|asm`) and `C_SRCS` (all others), then concatenate `ALL_SRCS=("${ASM_SRCS[@]}" "${C_SRCS[@]}")`.
   - Line 212 invokes `$CC $BFLAG $CFLAGS -T "$LDSCRIPT" -o "$ELF" "${ALL_SRCS[@]}"`.
   - Line 220 converts ELF to binary with `$OBJCOPY -O binary "$ELF" "$BIN"`.
   - Line 224 converts binary to Verilog hex with `python3 "$MAKEHEX" "$BIN" 4096 > "$HEX"`.

2. **Benchmark Folder Inventory & Startup Presence**:
   - `Codespace/SERV_codespace/BNN/`: Contains 5 `.c` files (`helpers.c`, `layer0.c`, `layer1_uint32.c`, `main_bnn.c`, `samples_bnn.c`) and 4 `.h` files. **Zero assembly (`.s` or `.S`) files exist**.
   - `Codespace/SERV_codespace/Tsetin_Machine/`: Contains 6 `.c` files (`TA_actions_uint32.c`, `booleanization.c`, `class_sum.c`, `clause_output.c`, `main_tm.c`, `samples_tm.c`) and 2 `.h` files. **Zero assembly (`.s` or `.S`) files exist**.
   - `Codespace/SERV_codespace/random_forest/`: Contains 4 `.c` files, 3 `.h` files, and `startup.S`. `diff -u random_forest/startup.S build_codes/startup.S` yielded 0 differences (byte-for-byte identical).
   - `Codespace/SERV_codespace/rf_v2_lucky/`: Contains `startup.S` (byte-for-byte identical to `build_codes/startup.S`).
   - `BNN/compile_bnn.sh` (lines 47–51) and `Tsetin_Machine/compile_tm.sh` (lines 51–54) explicitly fall back to `Codespace/SERV_codespace/build_codes/startup.S` when no platform crt0 is found.

3. **Inspection of `Codespace/SERV_codespace/build_codes/startup.S`**:
   - Lines 1–2 define `#define GPIO_ADDR 0x40000000` and `#define HALT_ADDR 0x90000000`.
   - Lines 4–6 declare `.text`, `.globl _start`, and label `_start:`.
   - Line 11 executes `li sp, 8192` (initializes stack pointer to top of 8 KB).
   - Lines 14–16 execute `li a0, GPIO_ADDR; addi t0, zero, 1; sb t0, 0(a0)` (sets GPIO high for UART idle mark).
   - Line 19 executes `jal main` (calls C `main()` function).
   - Lines 22–25 define `halt: li t0, HALT_ADDR; sw zero, 0(t0); j halt` (signals simulation stop to Verilator testbench).
   - Lines 28–42 define `.globl asm_uart_putchar` (bit-banged UART routine).

4. **Popcount Macro Usage in Existing Source Files**:
   - `BNN/helpers.c` lines 37–51:
     ```c
     #ifdef USE_CUSTOM_POPCOUNT
         int rd;
         asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0" : "=r"(rd) : "r"(x));
         return rd;
     #else
         /* Software fallback */
     ...
     ```
   - `Tsetin_Machine/class_sum.c` lines 21–33:
     ```c
     #ifdef USE_CUSTOM_POPCOUNT
         unsigned int rd;
         asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0" : "=r"(rd) : "r"(val));
         return rd;
     #else
     ...
     ```

---

## 2. Logic Chain

1. **Premise 1 (Order & Entry Point)**: SERV hardware resets to PC `0x00000000`. `link.ld` specifies `ENTRY(_start)` and sets `.text` at `0x00000000`. By placing assembly sources first in `ALL_SRCS`, GCC places `_start` at `0x00000000`.
2. **Premise 2 (Absence of Assembly in BNN and TM)**: Because neither `BNN/` nor `Tsetin_Machine/` contains any assembly files, `ASM_SRCS` is empty when building these folders. GCC fails to find `_start` with `-nostartfiles`.
3. **Inference 1 (Fallback Requirement)**: Automatically adding `Codespace/SERV_codespace/build_codes/startup.S` to `ASM_SRCS` when `${#ASM_SRCS[@]} -eq 0` allows `BNN` and `Tsetin_Machine` to link seamlessly without modifying benchmark folders or copying redundant files.
4. **Premise 3 (Popcount Macro Propagation)**: `BNN/helpers.c` and `Tsetin_Machine/class_sum.c` already check `#ifdef USE_CUSTOM_POPCOUNT`.
5. **Inference 2 (Flag Design)**: Adding `--popcount` to `build.sh` and appending `-DUSE_CUSTOM_POPCOUNT` to `CFLAGS` in `do_build()` cleanly enables hardware popcount across all benchmarks when the flag is passed, while leaving pure software execution as the default when the flag is omitted.

---

## 3. Caveats

- **No Caveats Regarding Build Survey**: The build script, linker script, startup assembly, and source tree files are fully explored and documented.
- **Out-of-Scope Milestones**: Modifying `random_forest/infer_one.c` (Milestone 2) and running simulation cycle count measurements (Milestone 3) are subsequent milestones and were not modified during this read-only survey.

---

## 4. Conclusion

1. The exact modifications required for `serv_project/build.sh` are fully identified across four sections:
   - Line 315: Add `USE_POPCOUNT=false`.
   - Line 320: Add `--popcount) USE_POPCOUNT=true ;;`.
   - Line 164: Append `-DUSE_CUSTOM_POPCOUNT` to `CFLAGS` if `$USE_POPCOUNT`.
   - Line 200: If `${#ASM_SRCS[@]} -eq 0`, inject `FALLBACK_STARTUP="$SERV_CODESPACE/build_codes/startup.S"`.
   - Line 286: Update `usage()` with `--popcount` documentation and examples.
2. Full backwards compatibility is guaranteed. All existing options (`--folder`, `--build`, `--run`, `--clear`, `--serv-dir`) continue functioning without alteration.
3. Complete implementation details and before/after diffs are documented in `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_explorer_survey_1/report.md`.

---

## 5. Verification Method

To independently verify the survey findings and subsequent implementation:

1. **Verify Startup Fallback on BNN**:
   ```bash
   cd /home/chenyoo/riscv_benchmark/serv_project
   ./build.sh --folder=BNN --build
   ```
   *Expected Result*: Output logs `[INFO] No assembly file found in ../Codespace/SERV_codespace/BNN; using fallback startup: ...` and produces `firmware.hex`.
2. **Verify Software vs Hardware Popcount Build**:
   ```bash
   ./build.sh --folder=Tsetin_Machine --build
   riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn" # Should be empty
   ./build.sh --folder=Tsetin_Machine --popcount --build
   riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn" # Should find popcount instruction
   ```
3. **Verify Backwards Compatibility**:
   ```bash
   ./build.sh --build
   ```
   *Expected Result*: Successfully builds `build_codes/` exactly as before.
