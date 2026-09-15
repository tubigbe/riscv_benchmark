# Handoff Report: Milestone 1 (R1) - Build Script Macro & Startup Integration

## 1. Observation
- File modified: `/home/chenyoo/riscv_benchmark/serv_project/build.sh`.
- Prior to modification:
  1. `build.sh` only accepted arguments `--folder=*`, `--serv-dir=*`, `--build`, `--run`, `--clear`, and `--help|-h`. Any other argument triggered `fail "Unknown argument: $arg (use --help for usage)"`.
  2. `CFLAGS` in `do_build()` was fixed to `"-O2 $COMMON_FLAGS $INCLUDES"` without support for conditional preprocessor defines such as `-DUSE_CUSTOM_POPCOUNT`.
  3. Source discovery partitioned files into `ASM_SRCS` and `C_SRCS`. If a directory like `BNN/` or `Tsetin_Machine/` had no `.s` or `.S` files, `${#ASM_SRCS[@]}` remained 0, causing linking to fail (`undefined reference to _start` or `cannot find entry symbol _start`) or execution without `sp` initialization and halt capability.
- Changes made to `serv_project/build.sh`:
  - **Lines 83–89**: Added toolchain library search paths for container/snap environments (`$SCRIPT_DIR/../tools/lib` and fallback scratch directory) ensuring GCC dependencies (`libisl.so.23`, `libmpfr.so.6`, `libmpc.so.3`) are dynamically discoverable via `LD_LIBRARY_PATH`.
  - **Lines 171–174**: In `do_build()`, added check:
    ```bash
    if $USE_POPCOUNT; then
        CFLAGS="$CFLAGS -DUSE_CUSTOM_POPCOUNT"
        info "Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)"
    fi
    ```
  - **Lines 213–223**: In `do_build()`, added automatic fallback to standard SERV startup code if `${#ASM_SRCS[@]}` is 0:
    ```bash
    # ── Fallback startup assembly if none provided in target folder ──
    if [[ ${#ASM_SRCS[@]} -eq 0 ]]; then
        local FALLBACK_STARTUP="$SERV_CODESPACE/build_codes/startup.S"
        if [[ -f "$FALLBACK_STARTUP" ]]; then
            info "No assembly file found in $FOLDER_PATH; using fallback startup: $FALLBACK_STARTUP"
            ASM_SRCS+=("$FALLBACK_STARTUP")
            TOTAL=$((TOTAL + 1))
        else
            fail "No assembly file in $FOLDER_PATH and fallback startup not found at $FALLBACK_STARTUP"
        fi
    fi
    ```
  - **Lines 311, 318, 327–330**: Updated `usage()` documentation to include `--popcount` and benchmark build examples.
  - **Lines 342, 349**: Added `USE_POPCOUNT=false` initialization and `--popcount) USE_POPCOUNT=true ;;` argument parsing.

## 2. Logic Chain
1. **Macro Flag Requirement**: Requirement R1 requires `--popcount` to inject `-DUSE_CUSTOM_POPCOUNT` into `CFLAGS`. By initializing `USE_POPCOUNT=false`, setting it to `true` when `--popcount` is encountered, and conditionally appending `-DUSE_CUSTOM_POPCOUNT` to `CFLAGS` inside `do_build()`, the preprocessor directives in `BNN/helpers.c`, `Tsetin_Machine/class_sum.c`, and the future unified `random_forest/infer_one.c` correctly enable custom hardware popcount instructions.
2. **Startup Assembly Fallback**: In bare-metal RISC-V with `-nostdlib -nostartfiles`, `_start` must reside at reset vector `0x00000000`, set stack pointer `sp = 8192`, set UART GPIO high, call `main()`, and halt on exit via store to `0x90000000`. Folders such as `BNN` and `Tsetin_Machine` lack local assembly files. When `${#ASM_SRCS[@]} -eq 0`, injecting `Codespace/SERV_codespace/build_codes/startup.S` as the first element of `ALL_SRCS` guarantees proper freestanding initialization without requiring duplicate startup files copied across folders. Folders with local assembly (e.g. `random_forest`) have `${#ASM_SRCS[@]} > 0` and bypass fallback entirely.
3. **Backwards Compatibility**: All existing options (`--folder`, `--serv-dir`, `--build`, `--run`, `--clear`, `--help`) retain their exact original behavior. Default execution without `--folder` continues to discover and build from `build_codes/`.

## 3. Caveats
- No caveats regarding build system functionality.
- Note that `random_forest/infer_one.c` currently does not have `#ifdef USE_CUSTOM_POPCOUNT` integrated; that unification is scheduled for Milestone 2 (R2). When unified in R2, `--popcount` will automatically activate hardware popcount in `random_forest` as it already does for `BNN` and `Tsetin_Machine`.

## 4. Conclusion
Requirement R1 has been fully implemented in `serv_project/build.sh`. The script seamlessly supports `--popcount`, automatically provides standard startup assembly fallback for folders without assembly sources, retains 100% backwards compatibility with all previous options, and has been verified across all required build scenarios.

## 5. Verification Method & Results
The following 7 verification builds were executed directly and verified:

### Verification 1: `./build.sh --folder=random_forest --build`
- **Command**: `cd serv_project && ./build.sh --folder=random_forest --build`
- **Output**:
  ```text
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
     text	   data	    bss	    dec	    hex	filename
      532	   2720	     40	   3292	    cdc	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (3252 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (814 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Disassembly inspection**: Confirmed pure software bitwise instructions, no `.insn` present.

### Verification 2: `./build.sh --folder=random_forest --popcount --build`
- **Command**: `cd serv_project && ./build.sh --folder=random_forest --popcount --build`
- **Output**:
  ```text
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
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Status**: Flag acknowledged, builds cleanly.

### Verification 3: `./build.sh --folder=BNN --build`
- **Command**: `cd serv_project && ./build.sh --folder=BNN --build`
- **Output**:
  ```text
  [INFO]  Building firmware...
  [INFO]  Folder: ../Codespace/SERV_codespace/BNN
  [INFO]  No assembly file found in ../Codespace/SERV_codespace/BNN; using fallback startup: ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]  Sources (assembly → C):
  [INFO]    ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]    ../Codespace/SERV_codespace/BNN/helpers.c
  [INFO]    ../Codespace/SERV_codespace/BNN/layer0.c
  [INFO]    ../Codespace/SERV_codespace/BNN/layer1_uint32.c
  [INFO]    ../Codespace/SERV_codespace/BNN/main_bnn.c
  [INFO]    ../Codespace/SERV_codespace/BNN/samples_bnn.c
  [INFO]  Compiling + linking -> firmware.elf
  [OK]    Linked: firmware.elf
     text	   data	    bss	    dec	    hex	filename
     1088	    284	      4	   1376	    560	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (1372 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (344 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Symbol inspection**: `_start` located at `00000000 T _start`. Disassembly confirms software popcount loop, no `.insn` present.

### Verification 4: `./build.sh --folder=BNN --popcount --build`
- **Command**: `cd serv_project && ./build.sh --folder=BNN --popcount --build`
- **Output**:
  ```text
  [INFO]  Building firmware...
  [INFO]  Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)
  [INFO]  Folder: ../Codespace/SERV_codespace/BNN
  [INFO]  No assembly file found in ../Codespace/SERV_codespace/BNN; using fallback startup: ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]  Sources (assembly → C):
  [INFO]    ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]    ../Codespace/SERV_codespace/BNN/helpers.c
  [INFO]    ../Codespace/SERV_codespace/BNN/layer0.c
  [INFO]    ../Codespace/SERV_codespace/BNN/layer1_uint32.c
  [INFO]    ../Codespace/SERV_codespace/BNN/main_bnn.c
  [INFO]    ../Codespace/SERV_codespace/BNN/samples_bnn.c
  [INFO]  Compiling + linking -> firmware.elf
  [OK]    Linked: firmware.elf
     text	   data	    bss	    dec	    hex	filename
     1032	    284	      4	   1320	    528	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (1316 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (330 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Disassembly inspection**: Confirmed `.insn 4, 0x0005052b` and `.insn 4, 0x0008082b` emitted.

### Verification 5: `./build.sh --folder=Tsetin_Machine --build`
- **Command**: `cd serv_project && ./build.sh --folder=Tsetin_Machine --build`
- **Output**:
  ```text
  [INFO]  Building firmware...
  [INFO]  Folder: ../Codespace/SERV_codespace/Tsetin_Machine
  [INFO]  No assembly file found in ../Codespace/SERV_codespace/Tsetin_Machine; using fallback startup: ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]  Sources (assembly → C):
  [INFO]    ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/TA_actions_uint32.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/booleanization.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/class_sum.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/clause_output.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/main_tm.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/samples_tm.c
  [INFO]  Compiling + linking -> firmware.elf
  [OK]    Linked: firmware.elf
     text	   data	    bss	    dec	    hex	filename
      764	    312	     48	   1124	    464	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (1076 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (270 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Symbol inspection**: `_start` located at `00000000 T _start`. Pure software popcount.

### Verification 6: `./build.sh --folder=Tsetin_Machine --popcount --build`
- **Command**: `cd serv_project && ./build.sh --folder=Tsetin_Machine --popcount --build`
- **Output**:
  ```text
  [INFO]  Building firmware...
  [INFO]  Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)
  [INFO]  Folder: ../Codespace/SERV_codespace/Tsetin_Machine
  [INFO]  No assembly file found in ../Codespace/SERV_codespace/Tsetin_Machine; using fallback startup: ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]  Sources (assembly → C):
  [INFO]    ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/TA_actions_uint32.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/booleanization.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/class_sum.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/clause_output.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/main_tm.c
  [INFO]    ../Codespace/SERV_codespace/Tsetin_Machine/samples_tm.c
  [INFO]  Compiling + linking -> firmware.elf
  [OK]    Linked: firmware.elf
     text	   data	    bss	    dec	    hex	filename
      760	    312	     48	   1120	    460	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (1072 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (269 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Disassembly inspection**: Confirmed multiple `.insn` instructions emitted (e.g. `000686ab`, `0006062b`, `000787ab`).

### Verification 7: `./build.sh --build`
- **Command**: `cd serv_project && ./build.sh --build`
- **Output**:
  ```text
  [INFO]  Building firmware...
  [INFO]  Folder: ../Codespace/SERV_codespace/build_codes
  [INFO]  Sources (assembly → C):
  [INFO]    ../Codespace/SERV_codespace/build_codes/startup.S
  [INFO]    ../Codespace/SERV_codespace/build_codes/popcount_cus.c
  [INFO]  Compiling + linking -> firmware.elf
  [OK]    Linked: firmware.elf
     text	   data	    bss	    dec	    hex	filename
      259	      0	      4	    263	    107	firmware.elf
  [INFO]  objcopy -> firmware.bin
  [OK]    Binary: firmware.bin (259 bytes)
  [INFO]  makehex -> firmware.hex
  [OK]    Hex: firmware.hex (65 words)
  [OK]    Build done! Outputs: firmware.elf / firmware.bin / firmware.hex
  ```
- **Status**: Backwards compatibility confirmed.
