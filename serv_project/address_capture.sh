#!/bin/bash
# =================================================================
# Auto-capture disassembly PC addresses from firmware.elf
# Usage: ./address_capture.sh [firmware.elf] [function_name]
# =================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ELF_FILE="${1:-$SCRIPT_DIR/firmware.elf}"
FUNC="${2:-main}"
OBJDUMP="${OBJDUMP:-riscv64-unknown-elf-objdump}"

if [[ ! -f "$ELF_FILE" ]]; then
    echo "ERROR: ELF file not found: $ELF_FILE" >&2
    exit 1
fi

# ── Extract function start address ───────────────────────────
START_PC=$( $OBJDUMP -d "$ELF_FILE" \
    | awk "/<${FUNC}>:/ {getline; print \$1}" | tr -d ':' )

# ── Extract function end address (first ret after function) ──
STOP_PC=$( $OBJDUMP -d "$ELF_FILE" \
    | awk "/<${FUNC}>:/, /ret/ {if(\$0 ~ /ret/) print \$1}" | head -n 1 | tr -d ':' )

if [[ -z "$START_PC" ]]; then
    echo "ERROR: Could not find function <${FUNC}> in $ELF_FILE" >&2
    exit 1
fi

echo "============================================"
echo "  Function:       <${FUNC}>"
echo "  Start PC:       0x${START_PC}"
if [[ -n "$STOP_PC" ]]; then
    echo "  Stop  PC (ret): 0x${STOP_PC}"
else
    echo "  Stop  PC (ret): not found (no ret in function)"
fi
echo "============================================"
