#!/bin/bash
# =================================================================
# Look up the PC address of any instruction and the next one
# Usage: ./bnez_counter.sh <instruction_pattern> [loop_label]
#   e.g. ./bnez_counter.sh bnez bitbang
# =================================================================
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ELF_FILE="$SCRIPT_DIR/firmware.elf"
OBJDUMP=riscv64-unknown-elf-objdump

# ── Args ─────────────────────────────────────────────────────
INST="${1:-bnez}"        # instruction mnemonic to find (default: bnez)
LABEL="${2:-bitbang}"    # label to start searching from (default: bitbang)

# ── Find the instruction PC ──────────────────────────────────
INST_PC=$( $OBJDUMP -d "$ELF_FILE" \
    | awk "/<${LABEL}>:/ {p=1} p && /${INST}/{print \$1; exit}" \
    | tr -d ':' )

# ── Find the next instruction PC ─────────────────────────────
NEXT_PC=$( $OBJDUMP -d "$ELF_FILE" \
    | awk "/<${LABEL}>:/ {p=1} p && /${INST}/{getline; print \$1; exit}" \
    | tr -d ':' )

if [[ -z "$INST_PC" || -z "$NEXT_PC" ]]; then
    echo "ERROR: Could not find '${INST}' inside <${LABEL}>"
    exit 1
fi

echo "============================================================"
echo "  Target instruction (${INST}) PC:  0x${INST_PC}"
echo "  Next instruction PC:              0x${NEXT_PC}"
echo "============================================================"
