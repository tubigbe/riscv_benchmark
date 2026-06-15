#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════════════
#  SERV Verilator Simulation Pipeline
# ═══════════════════════════════════════════════════════════════════════
#
#  Purpose:
#    Builds a Verilator C++ model of the SERV SoC from RTL sources,
#    runs the simulation with a firmware.hex image, then post-processes
#    the results into analysis logs. This is the main simulation entry
#    point that ties together Verilator, sim_main.cpp, and the Python
#    trace-analysis scripts.
#
#  Tools used:
#    - verilator              Compile Verilog RTL → C++ simulation model
#    - make / g++             Build the C++ simulation executable
#    - Vservant_sim (built)   The compiled SERV simulation binary
#    - python3 trace_dump.py  Convert trace.bin → human-readable trace
#    - python3 compare_traces.py  Merge sim log + trace into final report
#
#  Usage:
#    ./run_sim.sh                              Clean + build + simulate
#    ./run_sim.sh --build                      Build Verilator model only
#    ./run_sim.sh --run                        Run simulation only
#    ./run_sim.sh --clear                      Clear all the log files
#    ./run_sim.sh --build --run                Build then simulate
#    ./run_sim.sh --firmware=my.hex            Use a different firmware
#
#  Pipeline steps:
#    [1/4] CLEAN        Remove obj_dir_custom/
#    [2/4] BUILD        Verilator + g++ → Vservant_sim binary
#    [3/4] SIMULATE     Run simulation, generates sim_log.txt + sim_wave.vcd
#    [4/4] POST-PROCESS trace_dump.py → trace_dump.txt
#                        compare_traces.py → compare_result.txt
#
#  Outputs (all in log/):
#    - sim_log.txt          Per-instruction cycle cost from the simulation
#    - sim_wave.vcd         VCD waveform dump (open with GTKWave)
#    - trace_dump.txt       Symbol-resolved PC trace from trace.bin
#    - compare_result.txt   Merged trace with per-instruction cycle info
#
# ═══════════════════════════════════════════════════════════════════════
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
DO_CLEAR=false

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
        --clear)    DO_CLEAR=true ;;
        --firmware=*) FIRMWARE="${arg#*=}" ;;
        -h|--help)
            echo "Usage: $0 [--clean] [--build] [--run] [--clear] [--firmware=FILE]"
            echo ""
            echo "  No args       → clean + build + run (default)"
            echo "  --clean       → remove build artifacts only"
            echo "  --build       → build without running"
            echo "  --run         → run without rebuilding"
            echo "  --clear       → remove log files and VCD"
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
#  CLEAR LOGS
# ══════════════════════════════════════════════════════════════
if $DO_CLEAR; then
    echo "════════════════════════════════════════"
    echo "  CLEAR LOGS"
    echo "════════════════════════════════════════"
    
    FILES_TO_DELETE=(
        "log/sim_log.txt"
        "log/trace_dump.txt"
        "log/compare_result.txt"
        "log/sim_wave.vcd"
    )
    
    DELETED=0
    for file in "${FILES_TO_DELETE[@]}"; do
        if [[ -f "$file" ]]; then
            rm -f "$file"
            echo "  Removed: $file"
            DELETED=$((DELETED + 1))
        fi
    done
    
    if [[ $DELETED -eq 0 ]]; then
        echo "  No log files to remove."
    else
        echo "  Removed $DELETED file(s)."
    fi
    exit 0
fi

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
