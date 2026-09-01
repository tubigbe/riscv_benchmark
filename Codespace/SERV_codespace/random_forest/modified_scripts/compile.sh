#!/bin/bash
# Usage: ./compile.sh [TargetPlatform]
# Run from anywhere — paths resolve relative to this script's directory.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

TargetPlatform="$1"

mkdir -p outdir
mkdir -p outdir/linker

# ── Toolchain (override with e.g. RISCV_PREFIX=riscv32-unknown-elf- ./compile.sh) ──
# Defaults to the system toolchain in PATH (/usr/bin/riscv64-unknown-elf-*)
RISCV_PREFIX="${RISCV_PREFIX:-riscv64-unknown-elf-}"
CC="${CC:-${RISCV_PREFIX}gcc}"
AS="${AS:-${RISCV_PREFIX}as}"
LD="${LD:-${RISCV_PREFIX}ld}"
OBJDUMP="${OBJDUMP:-${RISCV_PREFIX}objdump}"
OBJCOPY="${OBJCOPY:-${RISCV_PREFIX}objcopy}"

# --- Generate Assembly (.s) from C files ---
"$CC" -O0 -march=rv32e -mabi=ilp32e -S main.c -o outdir/main.s
"$CC" -O0 -march=rv32e -mabi=ilp32e -S infer_one.c -o outdir/infer_one.s
"$CC" -O0 -march=rv32e -mabi=ilp32e -S RF_model.c -o outdir/RF_model.s
"$CC" -O0 -march=rv32e -mabi=ilp32e -S samples.c -o outdir/samples.s

# --- Assemble .s → .o ---
"$AS" -march=rv32e -mabi=ilp32e outdir/main.s -o outdir/main.o
"$AS" -march=rv32e -mabi=ilp32e outdir/infer_one.s -o outdir/infer_one.o
"$AS" -march=rv32e -mabi=ilp32e outdir/RF_model.s -o outdir/RF_model.o
"$AS" -march=rv32e -mabi=ilp32e outdir/samples.s -o outdir/samples.o

# --- Assemble startup ---
# Prefer platform-specific crt0 (startup/<platform>_crt0.S), else fall back to SERV's startup.S
STARTUP_SRC="startup/${TargetPlatform}_crt0.S"
if [[ ! -f "$STARTUP_SRC" ]]; then
  STARTUP_SRC="Codespace/SERV_codespace/build_codes/startup.S"
fi
[[ -f "$STARTUP_SRC" ]] || { echo "ERROR: no startup file found ($STARTUP_SRC)" >&2; exit 1; }
# Use gcc with the preprocessor so #define macros in the .S file expand
"$CC" -x assembler-with-cpp -march=rv32e -mabi=ilp32e -c "$STARTUP_SRC" -o outdir/linker/crt0.o

# --- link all .o → ELF ---
# Prefer platform-specific linker script, else fall back to SERV's link.ld
LDSCRIPT="linker/${TargetPlatform}_link.ld"
if [[ ! -f "$LDSCRIPT" ]]; then
  LDSCRIPT="serv_project/fusesoc_libraries/serv/sw/link.ld"
fi
[[ -f "$LDSCRIPT" ]] || { echo "ERROR: no linker script found ($LDSCRIPT)" >&2; exit 1; }

"$LD" \
  -T "$LDSCRIPT" \
  -m elf32lriscv \
  outdir/linker/crt0.o \
  outdir/main.o \
  outdir/infer_one.o \
  outdir/RF_model.o \
  outdir/samples.o \
  -e _start \
  -o outdir/RF.elf

# --- Disassemble and Dump ---
"$OBJDUMP" -d outdir/RF.elf > outdir/RF.dump

# bin
"$OBJCOPY" -j .text -O binary outdir/RF.elf outdir/RF_imem.bin
"$OBJCOPY" -j .data -O binary outdir/RF.elf outdir/RF_dmem.bin

# hex
hexdump -v -e '"%08x\n"' outdir/RF_imem.bin > outdir/imem.hex
hexdump -v -e '/1 "%02x\n"' outdir/RF_dmem.bin > outdir/dmem.hex

# Copy outputs to the target platform directory (optional — path from another machine)
DEST_DIR="/home/sduan/RISP/riscv_minus_minus-tapeout-3/outputdir/firmware/${TargetPlatform}"
if [[ -n "$TargetPlatform" && -d "$DEST_DIR" ]]; then
  cp -r outdir/* "$DEST_DIR/RF/."
  echo "Copied outputs to $DEST_DIR/RF/"
else
  echo "NOTE: copy target '$DEST_DIR' not found — skipping copy. Outputs are in outdir/"
fi
