#!/bin/bash
# ═══════════════════════════════════════════════════════════════════════
#  SERV Static Instruction Counter
# ═══════════════════════════════════════════════════════════════════════
#
#  Purpose:
#    Parses the disassembly of a compiled RISC-V ELF file and counts
#    every unique instruction mnemonic. Can count the entire binary or
#    only the instructions between two user-specified function labels.
#
#  Tools used:
#    - riscv64-unknown-elf-objdump   Disassemble the ELF file
#    - awk                           Parse disassembly, count mnemonics
#
#  Usage:
#    ./instr_counter.sh                            Count all instructions
#    ./instr_counter.sh firmware.elf               Count specific ELF
#    ./instr_counter.sh firmware.elf _start main   Count between labels
#
#  When both labels exist in the ELF, only instructions between
#  start_label (inclusive) and end_label (exclusive) are counted.
#  If labels are not found or not provided, the full ELF is counted.
#
#  Output:
#    - log/instr_count.log   Per-mnemonic instruction breakdown
#    - Terminal               Confirmation message with log path
#
# ═══════════════════════════════════════════════════════════════════════
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_DIR="${SCRIPT_DIR}/log"

ELF_FILE="${1:-$SCRIPT_DIR/firmware.elf}"
START_LABEL="${2:-}"
END_LABEL="${3:-}"
OBJDUMP="${OBJDUMP:-riscv64-unknown-elf-objdump}"

if [[ ! -f "$ELF_FILE" ]]; then
    echo "ERROR: ELF file not found: $ELF_FILE" >&2
    exit 1
fi

mkdir -p "$LOG_DIR"
LOG_FILE="${LOG_DIR}/instr_count.log"

$OBJDUMP -d "$ELF_FILE" | awk -v elf="$ELF_FILE" \
                               -v start="$START_LABEL" \
                               -v end="$END_LABEL" '
BEGIN {
    if (start != "" && end != "") {
        mode = 'bet' 'ween'
        counting = 0
    } else {
        mode = 'a' 'll'
        counting = 1
    }
    found_start = 0
    found_end   = 0
}

# ── Match function / label headers ────────────────────────────
/<[A-Za-z0-9_$.]+>:/ {
    label = $0
    sub(/.*</, "", label)   # strip everything before <
    sub(/>.*/, "", label)   # strip everything after  >

    if (mode == 'bet' 'ween') {
        if (label == start) {
            counting    = 1
            found_start = 1
        }
        if (label == end && found_start) {
            counting  = 0
            found_end = 1
        }
    }
}

# ── Count instructions ────────────────────────────────────────
/^[[:space:]]*[0-9a-f]+:/ {
    if (counting && $3 != "") inst_count[$3]++
}

END {
    # ── Fallback: labels requested but not both found ─────────
    if (mode == 'bet' 'ween' && (!found_start || !found_end)) {
        if (!found_start)
            printf "Warning: start label \"%s\" not found\n", start > "/dev/stderr"
        if (!found_end)
            printf "Warning: end label \"%s\" not found\n", end > "/dev/stderr"
        printf "Falling back to full ELF count\n" > "/dev/stderr"
        # We skipped everything; re-run is handled by the shell below
        exit 2
    }

    # ── Print results ─────────────────────────────────────────
    total = 0
    for (ins in inst_count) total += inst_count[ins]

    print "========================================="
    print " Static instruction count"
    print " ELF: " elf
    if (mode == 'bet' 'ween')
        printf " Range: <%s> → <%s>\n", start, end
    print " Total instructions: " total
    print "========================================="
    for (ins in inst_count)
        printf "%-10s : %d\n", ins, inst_count[ins]
}
' > "$LOG_FILE" 2>&1 || {
    # awk exit 2 = labels not found, re-count entire ELF
    $OBJDUMP -d "$ELF_FILE" | awk -v elf="$ELF_FILE" '
    /^[[:space:]]*[0-9a-f]+:/ {
        if ($3 != "") inst_count[$3]++
    }
    END {
        total = 0
        for (ins in inst_count) total += inst_count[ins]
        print "========================================="
        print " Static instruction count (full ELF)"
        print " ELF: " elf
        print " Total instructions: " total
        print "========================================="
        for (ins in inst_count)
            printf "%-10s : %d\n", ins, inst_count[ins]
    }' > "$LOG_FILE"
}

echo "Log written to: $LOG_FILE"