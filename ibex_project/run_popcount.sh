#!/usr/bin/env bash
set -e

cd ~/riscv_benchmark
source ./ibex_project/env_ibex.sh
cd "$IBEX_REPO"

SRC="$HOME/riscv_benchmark/Codespace/Ibex_codespace/popcount.c"
COMMON="$IBEX_REPO/examples/sw/simple_system/common"
BUILD="$HOME/riscv_benchmark/ibex_project/build/codespace_popcount"
ELF="$BUILD/popcount.elf"

mkdir -p "$BUILD"
rm -f "$BUILD"/*

CFLAGS="-march=rv32imc_zicsr_zifencei -mabi=ilp32 -static -mcmodel=medany -Wall -g -Os -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding -fno-builtin"

echo "=== Check files ==="
ls -lh "$SRC"
ls -lh "$COMMON/simple_system_common.c"
ls -lh "$COMMON/crt0.S"
ls -lh "$COMMON/link.ld"

echo "=== Compile popcount.c ==="
riscv32-unknown-elf-gcc $CFLAGS -c \
  -I"$COMMON" \
  -o "$BUILD/popcount.o" \
  "$SRC"

echo "=== Compile simple_system_common.c ==="
riscv32-unknown-elf-gcc $CFLAGS -c \
  -I"$COMMON" \
  -o "$BUILD/simple_system_common.o" \
  "$COMMON/simple_system_common.c"

echo "=== Compile crt0.S ==="
riscv32-unknown-elf-gcc $CFLAGS -c \
  -I"$COMMON" \
  -o "$BUILD/crt0.o" \
  "$COMMON/crt0.S"

echo "=== Link popcount.elf ==="
riscv32-unknown-elf-gcc $CFLAGS \
  -T "$COMMON/link.ld" \
  "$BUILD/simple_system_common.o" \
  "$BUILD/popcount.o" \
  "$BUILD/crt0.o" \
  -o "$ELF"

echo "=== Check ELF ==="
ls -lh "$ELF"
riscv64-unknown-elf-readelf -h "$ELF" | grep -E "Class|Machine|Entry|Flags"

echo "=== Clean old simulation logs ==="
rm -f ibex_simple_system.log ibex_simple_system_pcount.csv trace_core_00000000.log

echo "=== Run popcount on Ibex ==="
"$IBEX_SIM" --meminit=ram,"$ELF" | tee "$BUILD/popcount_run.log"

echo "=== Program output ==="
cat ibex_simple_system.log

echo "=== Performance counters ==="
cat ibex_simple_system_pcount.csv
