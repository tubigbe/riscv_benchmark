#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════
#  SERV Simulation + VCD Waveform Viewer
#  Usage: ./sim_wave.sh [--firmware=FILE]
#
#  Steps:
#    1. Clean old build artifacts
#    2. Build Verilator model with --trace (VCD support)
#    3. Run simulation to generate log/sim_wave.vcd
#    4. Open waveform with GTKWave
# ═══════════════════════════════════════════════════════════════
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── Parse optional firmware argument ─────────────────────────
FIRMWARE_ARG=""
for arg in "$@"; do
    case "$arg" in
        --firmware=*) FIRMWARE_ARG="--firmware=${arg#*=}" ;;
        -h|--help)
            echo "Usage: $0 [--firmware=FILE]"
            echo ""
            echo "  --firmware=FILE   Specify a .hex firmware file (default: firmware.hex)"
            echo ""
            echo "This script builds Verilator with VCD tracing, runs the simulation,"
            echo "and opens the waveform in GTKWave."
            exit 0
            ;;
        *)
            echo "[ERROR] Unknown argument: $arg"
            exit 1
            ;;
    esac
done

VCD_FILE="log/sim_wave.vcd"

# ── Step 1/2: Clean + Build ──────────────────────────────────
echo "╔══════════════════════════════════════════════╗"
echo "║  Step 1-2: Clean & Build (with --trace)      ║"
echo "╚══════════════════════════════════════════════╝"
./run_sim.sh --clean --build

# ── Step 3: Run simulation ───────────────────────────────────
echo ""
echo "╔══════════════════════════════════════════════╗"
echo "║  Step 3: Running simulation → generating VCD ║"
echo "╚══════════════════════════════════════════════╝"
./run_sim.sh --run $FIRMWARE_ARG

# ── Step 4: Verify and open waveform ─────────────────────────
echo ""
if [[ -f "$VCD_FILE" ]]; then
    local_size=$(stat -c%s "$VCD_FILE" 2>/dev/null || echo "0")
    echo "╔══════════════════════════════════════════════╗"
    echo "║  Step 4: Opening waveform in GTKWave         ║"
    echo "╚══════════════════════════════════════════════╝"
    echo "  VCD file : $VCD_FILE (${local_size} bytes)"
    echo ""

    if command -v gtkwave &>/dev/null; then
        gtkwave "$VCD_FILE" &
        echo "[OK] GTKWave launched (PID: $!)"
    else
        echo "[WARN] gtkwave not found in PATH."
        echo "  Install with: sudo apt install gtkwave"
        echo "  Or manually open: $VCD_FILE"
    fi
else
    echo "[ERROR] VCD file not generated: $VCD_FILE"
    echo "  Check simulation output above for errors."
    exit 1
fi

echo ""
echo "Done!"
