#!/bin/bash
# =================================================================
# Count CPU cycles for main() from a SERV simulation trace.
# Usage: ./cycle_counter.sh [firmware.elf] [trace.bin]
# =================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ELF_FILE="${1:-$SCRIPT_DIR/firmware.elf}"
TRACE_BIN="${2:-$SCRIPT_DIR/build/award-winning_serv_servant_1.4.0/verilator_tb/trace.bin}"
OBJDUMP="${OBJDUMP:-riscv64-unknown-elf-objdump}"

if [[ ! -f "$ELF_FILE" ]]; then
    echo "ERROR: ELF file not found: $ELF_FILE" >&2
    exit 1
fi
if [[ ! -f "$TRACE_BIN" ]]; then
    echo "ERROR: Trace file not found: $TRACE_BIN" >&2
    exit 1
fi

# ── Extract main() start/stop PCs from disassembly ───────────
START_PC=$( $OBJDUMP -d "$ELF_FILE" | awk '/<main>:/ {getline; print $1}' | tr -d ':' )
STOP_PC=$( $OBJDUMP -d "$ELF_FILE" | awk '/<main>:/, /ret/ {if($0 ~ /ret/) print $1}' | head -n 1 | tr -d ':' )

if [[ -z "$START_PC" || -z "$STOP_PC" ]]; then
    echo "ERROR: Could not extract main() PCs from $ELF_FILE" >&2
    exit 1
fi

echo "============================================"
echo "  Start PC (main):  0x${START_PC}"
echo "  Stop  PC (ret):   0x${STOP_PC}"
echo "============================================"

# ── Count cycles between start and stop PCs ──────────────────
python3 -c "
import struct, sys

start = 0x${START_PC}
stop  = 0x${STOP_PC}

with open('${TRACE_BIN}', 'rb') as f:
    data = f.read()

pcs = struct.unpack(f'<{len(data)//4}I', data)

try:
    start_idx = next(i for i, pc in enumerate(pcs) if pc == start)
except StopIteration:
    print(f'ERROR: Start PC 0x{start:08x} not found in trace')
    sys.exit(1)

try:
    stop_idx = next(i for i, pc in enumerate(pcs) if i > start_idx and pc == stop)
except StopIteration:
    print(f'ERROR: Stop PC 0x{stop:08x} not found after start')
    sys.exit(1)

cycles = stop_idx - start_idx
print(f'  main() cycle cost: {cycles} cycles')
print(f'  (from trace index {start_idx} to {stop_idx})')
"
