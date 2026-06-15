#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════
#  SERV Simulation Build & Run Script
#  Usage: ./run_sim.sh [--clean] [--build] [--run] [--firmware=FILE]
#
#  Default (no args):  clean + build + run
#  --build only:       build without running
#  --run only:         run without rebuilding
#  --clean only:       remove build artifacts
#  --firmware=FILE:    specify a different .hex firmware file
# ═══════════════════════════════════════════════════════════════
set -euo pipefail

# ── Project root ─────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Ensure log directory exists
mkdir -p log

# ── Configuration ────────────────────────────────────────────
BUILD_DIR="obj_dir_custom"
BINARY="./${BUILD_DIR}/Vservant_sim"
FIRMWARE="firmware.hex"

# ── Parse arguments ──────────────────────────────────────────
DO_CLEAN=false
DO_BUILD=false
DO_RUN=false

# If no args at all → do everything
if [[ $# -eq 0 ]]; then
    DO_CLEAN=true
    DO_BUILD=true
    DO_RUN=true
fi

for arg in "$@"; do
    case "$arg" in
        --clean)    DO_CLEAN=true ;;
        --build)    DO_BUILD=true ;;
        --run)      DO_RUN=true ;;
        --firmware=*) FIRMWARE="${arg#*=}" ;;
        -h|--help)
            echo "Usage: $0 [--clean] [--build] [--run] [--firmware=FILE]"
            echo ""
            echo "  No args       → clean + build + run (default)"
            echo "  --clean       → remove build artifacts only"
            echo "  --build       → build without running"
            echo "  --run         → run without rebuilding"
            echo "  --firmware=X  → use X as firmware (default: firmware.hex)"
            exit 0
            ;;
        *)
            echo "[ERROR] Unknown option: $arg"
            echo "Run '$0 --help' for usage."
            exit 1
            ;;
    esac
done

# ── Verilog source list ──────────────────────────────────────
VERILOG_SOURCES=(
    fusesoc_libraries/serv/bench/servant_sim.v
    fusesoc_libraries/serv/servant/servant.v
    fusesoc_libraries/serv/servant/servant_mux.v
    fusesoc_libraries/serv/servant/servant_ram.v
    fusesoc_libraries/serv/servant/servant_gpio.v
    fusesoc_libraries/serv/servant/servant_timer.v
    fusesoc_libraries/serv/servile/servile.v
    fusesoc_libraries/serv/servile/servile_mux.v
    fusesoc_libraries/serv/servile/servile_arbiter.v
    fusesoc_libraries/serv/servile/servile_rf_mem_if.v
    fusesoc_libraries/serv/rtl/serv_top.v
    fusesoc_libraries/serv/rtl/serv_state.v
    fusesoc_libraries/serv/rtl/serv_decode.v
    fusesoc_libraries/serv/rtl/serv_ctrl.v
    fusesoc_libraries/serv/rtl/serv_alu.v
    fusesoc_libraries/serv/rtl/serv_immdec.v
    fusesoc_libraries/serv/rtl/serv_bufreg.v
    fusesoc_libraries/serv/rtl/serv_bufreg2.v
    fusesoc_libraries/serv/rtl/serv_csr.v
    fusesoc_libraries/serv/rtl/serv_mem_if.v
    fusesoc_libraries/serv/rtl/serv_rf_top.v
    fusesoc_libraries/serv/rtl/serv_rf_if.v
    fusesoc_libraries/serv/rtl/serv_rf_ram.v
    fusesoc_libraries/serv/rtl/serv_rf_ram_if.v
    fusesoc_libraries/serv/rtl/serv_compdec.v
    fusesoc_libraries/serv/rtl/serv_aligner.v
    fusesoc_libraries/serv/rtl/serv_debug.v
    fusesoc_libraries/serv/bench/servant_tb.v
    fusesoc_libraries/serv/bench/uart_decoder.v
)

CPP_SOURCES=(scripts/sim_main.cpp)

# ══════════════════════════════════════════════════════════════
#  CLEAN
# ══════════════════════════════════════════════════════════════
if $DO_CLEAN; then
    echo "════════════════════════════════════════"
    echo "  [1/4] CLEAN"
    echo "════════════════════════════════════════"
    rm -rf "$BUILD_DIR"
    echo "  Removed ${BUILD_DIR}/"
fi

# ══════════════════════════════════════════════════════════════
#  BUILD
# ══════════════════════════════════════════════════════════════
if $DO_BUILD; then
    echo "════════════════════════════════════════"
    echo "  [2/4] BUILD"
    echo "════════════════════════════════════════"

    # Step 1: Verilator → generate C++ model
    echo "  [Verilator] Generating C++ model..."
    verilator --Wno-fatal --cc \
        "${VERILOG_SOURCES[@]}" \
        --exe "${CPP_SOURCES[@]}" \
        --top-module servant_sim \
        --trace \
        --Mdir "$BUILD_DIR" \
        -o Vservant_sim \
        -CFLAGS "-std=c++17"

    # Step 2: Compile C++
    echo "  [Make] Compiling C++..."
    make -C "$BUILD_DIR" -f Vservant_sim.mk -j"$(nproc)"

    echo "  Build complete: ${BINARY}"
fi

# ══════════════════════════════════════════════════════════════
#  RUN
# ══════════════════════════════════════════════════════════════
if $DO_RUN; then
    if [[ ! -x "$BINARY" ]]; then
        echo "[ERROR] Binary not found: ${BINARY}"
        echo "  Run '$0 --build' first, or '$0' to clean+build+run."
        exit 1
    fi
    if [[ ! -f "$FIRMWARE" ]]; then
        echo "[ERROR] Firmware not found: ${FIRMWARE}"
        echo "  Build firmware first or specify with --firmware=FILE"
        exit 1
    fi

    echo "════════════════════════════════════════"
    echo "  [3/4] SIMULATE"
    echo "════════════════════════════════════════"
    echo "  Firmware : ${FIRMWARE}"
    echo "  Binary   : ${BINARY}"
    echo "  VCD      : log/sim_wave.vcd"
    echo "════════════════════════════════════════"
    "$BINARY" "+firmware=${FIRMWARE}" "+vcd=1"

    # ── Post-processing ──────────────────────────────────────
    echo "════════════════════════════════════════"
    echo "  [4/4] POST-PROCESS"
    echo "════════════════════════════════════════"

    echo "  [trace_dump] Processing trace.bin..."
    if ! python3 scripts/trace_dump.py; then
        echo "  [WARN] trace_dump.py failed (trace.bin may not exist)"
    fi

    echo "  [compare] Merging traces -> log/compare_result.txt"
    if ! python3 scripts/compare_traces.py; then
        echo "  [WARN] compare_traces.py failed"
    fi

    echo "════════════════════════════════════════"
    echo "  Done! Logs in log/"
    echo "════════════════════════════════════════"
fi
