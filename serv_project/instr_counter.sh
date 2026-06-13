#!/bin/bash
# =================================================================
# Static instruction counter for a given function in firmware.elf
# Parses objdump disassembly, counts each unique mnemonic.
# Usage: ./instr_counter.sh [function_name] [firmware.elf]
# =================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

FUNC="${1:-_start}"
ELF_FILE="${2:-$SCRIPT_DIR/firmware.elf}"
OBJDUMP="${OBJDUMP:-riscv64-unknown-elf-objdump}"

if [[ ! -f "$ELF_FILE" ]]; then
    echo "ERROR: ELF file not found: $ELF_FILE" >&2
    exit 1
fi

$OBJDUMP -d "$ELF_FILE" | awk -v func="$FUNC" '
/<'"$FUNC"'>:/ { flag = 1; next }
flag {
    # Only count lines with hex address + valid instruction
    if ($1 ~ /^[0-9a-f]+:/) {
        if ($3 != "") inst_count[$3]++
    }
    # Stop at next function label or ret
    if ($0 ~ /ret/ || (NF >= 2 && $2 ~ /^<.*>:$/)) flag = 0
}
END {
    total = 0
    for (ins in inst_count) total += inst_count[ins]
    print "[Static] <" func "> instruction breakdown (" total " total):"
    print "========================================="
    for (ins in inst_count) {
        printf "%-10s : %d\n", ins, inst_count[ins]
    }
}
'