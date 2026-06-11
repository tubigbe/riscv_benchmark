#!/usr/bin/env bash
set -e

cd ~/riscv_benchmark
source ./ibex_project/env_ibex.sh
cd "$IBEX_REPO"

SRC="$HOME/riscv_benchmark/Codespace/Ibex_codespace/popcount_benchmark.c"
COMMON="$IBEX_REPO/examples/sw/simple_system/common"
BUILD="$HOME/riscv_benchmark/ibex_project/build/popcount_sweep"
RESULT="$BUILD/results.csv"

mkdir -p "$HOME/riscv_benchmark/Codespace/Ibex_codespace"
mkdir -p "$BUILD"
rm -f "$BUILD"/*

cat > "$SRC" <<'C_EOF'
#include <stdint.h>

#define IBEX_SIM_HALT_ADDR 0x00020008u

void popcount(uint32_t in_reg){
    uint32_t count0 = 0;
    uint32_t count1 = 0;

    for(int i = 0; i < 32; i++){
        uint32_t temp = in_reg >> i;
        temp = temp & 1;
        if(temp == 1) {
            count1 = count1 + 1;
        } else {
            count0 = count0 + 1;
        }
    }
}

#ifndef ITERATIONS
#define ITERATIONS 1000u
#endif

static void ibex_halt(void)
{
    volatile uint32_t *halt_reg = (volatile uint32_t *)IBEX_SIM_HALT_ADDR;
    *halt_reg = 1u;

    while (1) {
    }
}

int main(void)
{
    uint32_t x = 0xDEADBEEFu;

    for (uint32_t i = 0u; i < ITERATIONS; i++) {
        popcount(x);
        x = x + 0x9E3779B9u;
    }

    ibex_halt();

    return 0;
}
C_EOF

CFLAGS_BASE="-march=rv32imc_zicsr_zifencei -mabi=ilp32 -static -mcmodel=medany -Wall -g -O0 -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding -fno-builtin"

echo "iterations,cycles,instructions" > "$RESULT"

for N in 0 1 10 100 1000 10000
do
    echo "=== Build and run ITERATIONS=$N ==="

    RUN_DIR="$BUILD/N_$N"
    mkdir -p "$RUN_DIR"

    riscv32-unknown-elf-gcc $CFLAGS_BASE -DITERATIONS=$N -c \
      -I"$COMMON" \
      -o "$RUN_DIR/popcount_benchmark.o" \
      "$SRC"

    riscv32-unknown-elf-gcc $CFLAGS_BASE -c \
      -I"$COMMON" \
      -o "$RUN_DIR/simple_system_common.o" \
      "$COMMON/simple_system_common.c"

    riscv32-unknown-elf-gcc $CFLAGS_BASE -c \
      -I"$COMMON" \
      -o "$RUN_DIR/crt0.o" \
      "$COMMON/crt0.S"

    riscv32-unknown-elf-gcc $CFLAGS_BASE \
      -T "$COMMON/link.ld" \
      "$RUN_DIR/simple_system_common.o" \
      "$RUN_DIR/popcount_benchmark.o" \
      "$RUN_DIR/crt0.o" \
      -o "$RUN_DIR/popcount_N${N}.elf"

    rm -f ibex_simple_system.log ibex_simple_system_pcount.csv trace_core_00000000.log

    "$IBEX_SIM" --meminit=ram,"$RUN_DIR/popcount_N${N}.elf" \
      > "$RUN_DIR/run.log"

    cp ibex_simple_system_pcount.csv "$RUN_DIR/pcount.csv"

    CYCLES=$(awk -F',' '/Cycles/ {print $2}' "$RUN_DIR/pcount.csv")
    INSTS=$(awk -F',' '/Instructions Retired/ {print $2}' "$RUN_DIR/pcount.csv")

    echo "$N,$CYCLES,$INSTS" >> "$RESULT"

    echo "N=$N cycles=$CYCLES instructions=$INSTS"
done

echo "=== Sweep result ==="
cat "$RESULT"

echo "=== Approx cycles per iteration ==="
awk -F',' '
NR==2 {n0=$1; c0=$2}
NR>2 {
    dn=$1-n0;
    dc=$2-c0;
    if (dn > 0) {
        printf("from N=%s to N=%s: %.4f cycles/iteration\n", n0, $1, dc/dn);
    }
}
' "$RESULT"
