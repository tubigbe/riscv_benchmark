# Forensic Integrity Audit Report: Milestone 1 (Requirement R1)

**Work Product**: `/home/chenyoo/riscv_benchmark/serv_project/build.sh`  
**Profile**: General Project  
**Integrity Mode**: Development / Demo Mode  
**Verdict**: **CLEAN**  

---

## 1. Observation

### Observation 1: Git Diff Analysis of `serv_project/build.sh`
Executing `git diff serv_project/build.sh` reveals genuine, non-intrusive modifications:
- **Lines 83–89**: LD_LIBRARY_PATH auto-discovery for host toolchain dependencies (`libisl.so.23`, `libmpfr.so.6`, `libmpc.so.3`) in container/snap environments:
  ```bash
  for _libdir in "$SCRIPT_DIR/../tools/lib" "$SCRIPT_DIR/../.agents/teamwork_preview_explorer_survey_3/scratch/lib/usr/lib/x86_64-linux-gnu"; do
      if [[ -d "$_libdir" ]]; then
          export LD_LIBRARY_PATH="$_libdir${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
      fi
  done
  ```
- **Lines 171–174**: Conditional injection of `-DUSE_CUSTOM_POPCOUNT` into `CFLAGS`:
  ```bash
  if $USE_POPCOUNT; then
      CFLAGS="$CFLAGS -DUSE_CUSTOM_POPCOUNT"
      info "Hardware popcount enabled (-DUSE_CUSTOM_POPCOUNT)"
  fi
  ```
- **Lines 213–223**: Startup fallback when no local assembly file is found in the target directory:
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
- **Lines 311, 318, 327–330, 342, 349**: Added `--popcount` CLI parameter parsing (`USE_POPCOUNT=true`) and updated usage documentation.

### Observation 2: Genuine GCC Invocation and Artifact Generation
In `do_build()` (lines 234–256), actual GCC compilation and toolchain commands are executed:
```bash
$CC $BFLAG $CFLAGS -T "$LDSCRIPT" -o "$ELF" "${ALL_SRCS[@]}"
$OBJCOPY -O binary "$ELF" "$BIN"
python3 "$MAKEHEX" "$BIN" 4096 > "$HEX"
```
No hardcoded binary strings, static pre-built hex files, or dummy mock scripts exist in `serv_project/build.sh`.

### Observation 3: Macro Expansion and Disassembly Empirical Verification
We compiled `BNN` and `Tsetin_Machine` both with and without `--popcount`, capturing the resulting ELF binaries:

1. **`BNN` without `--popcount` (`bnn_sw.elf`)**:
   `riscv64-unknown-elf-objdump -d bnn_sw.elf`:
   ```assembly
   000000b8 <popcount32>:
     b8:	00050793          	mv	a5,a0
     bc:	00000513          	li	a0,0
     c0:	00078c63          	beqz	a5,d8 <popcount32+0x20>
     c4:	fff78713          	addi	a4,a5,-1
     c8:	00e7f7b3          	and	a5,a5,a4
     cc:	00150513          	addi	a0,a0,1
     d0:	fe079ae3          	bnez	a5,c4 <popcount32+0xc>
     d4:	00008067          	ret
     d8:	00008067          	ret
   ```
   Generates pure software bit-clearing loop without any custom instruction.

2. **`BNN` with `--popcount` (`bnn_popcount.elf`)**:
   `riscv64-unknown-elf-objdump -d bnn_popcount.elf`:
   ```assembly
   000000b8 <popcount32>:
     b8:	0005052b          	.insn	4, 0x0005052b
     bc:	00008067          	ret
   ```
   The `#ifdef USE_CUSTOM_POPCOUNT` macro branch is genuinely compiled into custom instruction opcode `0x2b` (`.insn r 0x2B, 0, 0`).

3. **`Tsetin_Machine` without `--popcount` (`tm_sw.elf`)**:
   Inlined `popcnt` in `compute_class_sum`:
   ```assembly
    1e8:	fff70613          	addi	a2,a4,-1
    1ec:	00c77733          	and	a4,a4,a2
    1f0:	00168693          	addi	a3,a3,1
    1f4:	fe071ae3          	bnez	a4,1e8 <compute_class_sum+0x34>
   ```
   Pure software loop.

4. **`Tsetin_Machine` with `--popcount` (`tm_popcount.elf`)**:
   Inlined `popcnt` in `compute_class_sum`:
   ```assembly
    1bc:	000686ab          	.insn	4, 0x000686ab
    1c4:	0006062b          	.insn	4, 0x0006062b
    1d8:	000787ab          	.insn	4, 0x000787ab
    1e4:	0006062b          	.insn	4, 0x0006062b
    210:	000686ab          	.insn	4, 0x000686ab
    21c:	0007072b          	.insn	4, 0x0007072b
   ```
   Hardware popcount instructions genuinely emitted.

### Observation 4: Startup Assembly Fallback Verification
Disassembly of `bnn_sw.elf` and `tm_sw.elf` entry vector:
```assembly
00000000 <_start>:
   0:	00002137          	lui	sp,0x2
   4:	40000537          	lui	a0,0x40000
   8:	00100293          	li	t0,1
   c:	00550023          	sb	t0,0(a0)
  10:	3b8000ef          	jal	3c8 <main>

00000014 <halt>:
  14:	900002b7          	lui	t0,0x90000
  18:	0002a023          	sw	zero,0(t0)
  1c:	ff9ff06f          	j	14 <halt>
```
Matches `Codespace/SERV_codespace/build_codes/startup.S` verbatim.
Furthermore, when building `random_forest` (which contains its own `startup.S`), the build log proves the fallback is bypassed and local assembly is utilized:
```text
[INFO]  Sources (assembly → C):
[INFO]    ../Codespace/SERV_codespace/random_forest/startup.S
...
```

---

## 2. Logic Chain

1. **Integrity Check 1 (Genuine Compilation)**:
   - Observation 1 & 2 confirm that `build.sh` invokes the real toolchain binary `$CC` (`riscv64-unknown-elf-gcc`) with standard compile-and-link flags.
   - Observation 3 shows that binary sizes, section text/data layouts, and instruction streams change dynamically based on target sources and preprocessor options. No static pre-built payloads or mocking exist.
   - **Deduction**: Requirement R1 contains no facade, no hardcoded results, and no circumventing of actual compilation.

2. **Integrity Check 2 (Macro Expansion of `-DUSE_CUSTOM_POPCOUNT`)**:
   - Observation 1 confirms `-DUSE_CUSTOM_POPCOUNT` is added to `CFLAGS` when `--popcount` is present.
   - Observation 3 empirically demonstrates that without `--popcount`, software loops are emitted, whereas with `--popcount`, hardware `.insn` instructions are emitted in both `BNN` and `Tsetin_Machine`.
   - **Deduction**: `-DUSE_CUSTOM_POPCOUNT` is genuinely passed to GCC and reliably alters preprocessor macro expansion as specified.

3. **Integrity Check 3 (Startup Assembly Fallback)**:
   - Observation 1 shows that if `${#ASM_SRCS[@]}` is zero, `FALLBACK_STARTUP` points directly to `$SERV_CODESPACE/build_codes/startup.S`.
   - Observation 4 confirms that `bnn_sw.elf` and `tm_sw.elf` contain the authentic SERV startup sequence (`_start` at `0x0`, stack pointer initialized to 8192, GPIO set high, jump to `main`, and exit loop writing to `0x90000000`).
   - Observation 4 confirms that directories with existing assembly files (`random_forest`) do not trigger the fallback, avoiding double startup linkage.
   - **Deduction**: The startup fallback genuinely links the real SERV startup code without dummy mocks or stubs.

4. **Integrity Check 4 (Code Quality & Cleanliness)**:
   - Git diff is minimal, adheres strictly to the existing coding style in `build.sh`, provides clean logging messages, and preserves backwards compatibility with all previous options (`--build`, `--run`, `--clear`, `--serv-dir`).
   - **Deduction**: Genuine, high-quality engineering.

---

## 3. Caveats

1. **Toolchain Shared Library Path**:
   Line 84 references `.agents/teamwork_preview_explorer_survey_3/scratch/lib/usr/lib/x86_64-linux-gnu` as a fallback directory for `libisl.so.23`. In the current environment, `tools/lib` does not exist, so GCC relies on this scratch path to load `libisl.so.23`. If the `.agents` folder is removed, GCC will fail with `libisl.so.23: cannot open shared object file`. While this is NOT an integrity violation, copying the libraries into `tools/lib` is recommended for standalone portability.
2. **`random_forest` Macro Integration Scope**:
   In `random_forest`, `infer_one.c` has not yet been unified with `#ifdef USE_CUSTOM_POPCOUNT`. Per `ORIGINAL_REQUEST.md`, this is Requirement R2 (Milestone 2), not Requirement R1. The build script correctly supplies the flag, ready for R2 unification.

---

## 4. Conclusion

The implementation of Requirement R1 in `serv_project/build.sh` is authentic, complete, and robust. All four forensic integrity checks pass with zero violations detected.

**Final Verdict**: **CLEAN**

---

## 5. Verification Method

To independently reproduce and verify this audit:

```bash
cd /home/chenyoo/riscv_benchmark

# 1. Verify build script diff
git diff serv_project/build.sh

# 2. Build BNN software mode and verify software popcount loop
export PATH="/home/chenyoo/riscv_benchmark/tools/riscv64/usr/bin:$PATH"
./serv_project/build.sh --folder=BNN --build
riscv64-unknown-elf-objdump -d serv_project/firmware.elf | sed -n "/<popcount32>:/,/^[0-9a-f]* <[a-zA-Z]/p"

# 3. Build BNN hardware mode and verify custom .insn
./serv_project/build.sh --folder=BNN --popcount --build
riscv64-unknown-elf-objdump -d serv_project/firmware.elf | sed -n "/<popcount32>:/,/^[0-9a-f]* <[a-zA-Z]/p"

# 4. Verify startup fallback entry point
riscv64-unknown-elf-objdump -d serv_project/firmware.elf | head -n 30
```
Invalidation condition: If any disassembly shows fake stub returns or if `--popcount` fails to alter the emitted machine code.
