#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════
#  SERV Standalone Build Script
#  Usage: ./build.sh [--build] [--run] [--clean]
# ═══════════════════════════════════════════════════════════════
set -euo pipefail

# ── EDIT THIS: source file list ──────────────────────────────
# Add / remove entries below. Paths are relative to serv_project/.
# Supported types: .c .cc .cpp .S .s .asm
# Duplicates are automatically skipped; missing files trigger a warning.
#
# Select firmware with: BENCH=lw ./build.sh --build --run
#   default  → factorial demo (startup + factorial.c)
#   lw       → load-word cycle benchmark (startup + test_lw_cycles.s + main.c)
# ──────────────────────────────────────────────────────────────
STARTUP="../Codespace/SERV_codespace/startup.S"

if [[ "${BENCH:-}" == "lw" ]]; then
    SOURCES=(
        "$STARTUP"
        "test_lw_cycles.s"
        "main.c"
    )
else
    SOURCES=(
        "$STARTUP"
        "../Codespace/SERV_codespace/factorial.c"
    )
fi
# ──────────────────────────────────────────────────────────────

# Project root (script's own directory)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── Toolchain (prefers env.sh exports, falls back to riscv64 prefix) ──
_prefix="${RISCV64_PREFIX:-riscv64-unknown-elf-}"
CC="${CC:-${_prefix}gcc}"
CXX="${CXX:-${_prefix}g++}"
OBJCOPY="${OBJCOPY:-${_prefix}objcopy}"
SIZE="${SIZE:-${_prefix}size}"
OBJDUMP="${OBJDUMP:-${_prefix}objdump}"
FUSESOC="${FUSESOC:-fusesoc}"

# ── Compiler flags ───────────────────────────────────────────
ARCH=rv32i
ABI=ilp32
COMMON_FLAGS="-march=$ARCH -mabi=$ABI -static -nostdlib -nostartfiles -ffreestanding"
INCLUDES="-I$SCRIPT_DIR/../Codespace"
CFLAGS="-O1 $COMMON_FLAGS $INCLUDES"
LDSCRIPT="fusesoc_libraries/serv/sw/link.ld"
MAKEHEX="fusesoc_libraries/serv/sw/makehex.py"

# ── Output files ─────────────────────────────────────────────
ELF="firmware.elf"
BIN="firmware.bin"
HEX="firmware.hex"

# ── Simulation settings ──────────────────────────────────────
FUSESOC_CORE="award-winning:serv:servant:1.4.0"
BAUD=57600
SIM_TIMEOUT=${SIM_TIMEOUT:-300}
TRACE_DIR="$SCRIPT_DIR/build/award-winning_serv_servant_1.4.0/verilator_tb"

# ══════════════════════════════════════════════════════════════
#  Colored output helpers
# ══════════════════════════════════════════════════════════════
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

info()  { echo -e "${CYAN}[INFO]${NC}  $*"; }
ok()    { echo -e "${GREEN}[OK]${NC}    $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC}  $*"; }
fail()  { echo -e "${RED}[FAIL]${NC}  $*"; exit 1; }

# ══════════════════════════════════════════════════════════════
#  Classify source file type -> sets COMPILER and XFLAG
# ══════════════════════════════════════════════════════════════
classify_file() {
    local ext="${1##*.}"
    ext="$(echo "$ext" | tr '[:upper:]' '[:lower:]')"
    case "$ext" in
        c)             COMPILER="$CC";  XFLAG="-x c" ;;
        cc|cpp|cxx|c++) COMPILER="$CXX"; XFLAG="-x c++" ;;
        S|s|asm)       COMPILER="$CC";  XFLAG="-x assembler-with-cpp" ;;
        *)             COMPILER="$CC";  XFLAG=""
                       warn "Unknown extension '.$ext', using gcc default" ;;
    esac
}

# ══════════════════════════════════════════════════════════════
#  BUILD: Compile firmware from SOURCES array
#  Strategy: single GCC invocation (compile + link).
#  .S files are always placed BEFORE .c/.cpp files so the
#  linker puts _start at the correct address.
# ══════════════════════════════════════════════════════════════
do_build() {
    info "Building firmware..."
    echo ""

    [[ -f "$LDSCRIPT" ]] || fail "Linker script not found: $LDSCRIPT"
    [[ -f "$MAKEHEX" ]]  || fail "makehex.py not found: $MAKEHEX"

    # ── Partition sources: assembly first, then C/C++ ──────
    local ASM_SRCS=()
    local C_SRCS=()
    declare -A SEEN
    local TOTAL=0
    local SKIPPED=0

    for src in "${SOURCES[@]}"; do
        local abs
        abs="$(realpath "$src" 2>/dev/null || echo "$SCRIPT_DIR/$src")"

        # Skip duplicates
        if [[ -n "${SEEN[$abs]+_}" ]]; then
            warn "Duplicate skipped: $src"
            SKIPPED=$((SKIPPED + 1))
            continue
        fi
        SEEN["$abs"]=1

        # Skip missing files
        if [[ ! -f "$src" ]]; then
            warn "File not found, skipping: $src"
            SKIPPED=$((SKIPPED + 1))
            continue
        fi

        local ext="${src##*.}"
        ext="$(echo "$ext" | tr '[:upper:]' '[:lower:]')"
        case "$ext" in
            S|s|asm) ASM_SRCS+=("$src") ;;
            *)       C_SRCS+=("$src") ;;
        esac
        TOTAL=$((TOTAL + 1))
    done

    [[ $TOTAL -eq 0 ]] && fail "No source files to compile"

    # Concatenate: assembly first, then C/C++
    local ALL_SRCS=("${ASM_SRCS[@]}" "${C_SRCS[@]}")

    info "Sources (assembly → C):"
    for f in "${ALL_SRCS[@]}"; do info "  $f"; done
    echo ""

    # ── Single GCC command: compile + link ─────────────────
    info "Compiling + linking -> $ELF"
    $CC $CFLAGS -T "$LDSCRIPT" -o "$ELF" "${ALL_SRCS[@]}"
    ok "Linked: $ELF"

    echo ""
    $SIZE "$ELF"
    echo ""

    # ── ELF -> binary -> hex ───────────────────────────────
    info "objcopy -> $BIN"
    $OBJCOPY -O binary "$ELF" "$BIN"
    ok "Binary: $BIN ($(stat -c%s "$BIN") bytes)"

    info "makehex -> $HEX"
    python3 "$MAKEHEX" "$BIN" 4096 > "$HEX"
    local hex_lines
    hex_lines=$(wc -l < "$HEX")
    ok "Hex: $HEX ($hex_lines words)"

    echo ""
    ok "Build done! Outputs: $ELF / $BIN / $HEX"
}

# ══════════════════════════════════════════════════════════════
#  RUN: Launch Verilator simulation
# ══════════════════════════════════════════════════════════════
do_run() {
    [[ -f "$HEX" ]] || fail "Firmware not found: $HEX — run ./build.sh --build first"

    # Clean up old trace files before simulation
    rm -f "$TRACE_DIR/trace.bin" "$TRACE_DIR/trace.vcd"

    info "Starting Verilator simulation..."
    info "  Core:     $FUSESOC_CORE"
    info "  Firmware: $SCRIPT_DIR/$HEX"
    info "  Baud:     $BAUD"
    info "  Trace:    $TRACE_DIR/trace.bin"
    echo ""

    timeout "${SIM_TIMEOUT}s" \
        "$FUSESOC" run --target=verilator_tb "$FUSESOC_CORE" \
            --uart_baudrate="$BAUD" \
            --firmware="$SCRIPT_DIR/$HEX" \
            --trace_pc \
        || {
            local exit_code=$?
            if [[ $exit_code -eq 124 ]]; then
                warn "Simulation timed out (${SIM_TIMEOUT}s) — terminated"
            else
                fail "Simulation failed (exit code: $exit_code)"
            fi
        }

    # Verify trace.bin was generated
    if [[ -f "$TRACE_DIR/trace.bin" ]]; then
        local trace_size
        trace_size=$(stat -c%s "$TRACE_DIR/trace.bin")
        ok "Trace saved: $TRACE_DIR/trace.bin ($((trace_size / 4)) PC entries)"
    else
        warn "trace.bin not found at $TRACE_DIR/trace.bin"
    fi
}

# ══════════════════════════════════════════════════════════════
#  CLEAN: Remove build artifacts
# ══════════════════════════════════════════════════════════════
do_clean() {
    info "Cleaning build artifacts..."
    rm -f "$ELF" "$BIN" "$HEX" build_*.o "$TRACE_DIR/trace.bin" "$TRACE_DIR/trace.vcd"
    ok "Removed: $ELF / $BIN / $HEX / build_*.o / trace.*"
}

# ══════════════════════════════════════════════════════════════
#  Main: parse command-line arguments
# ══════════════════════════════════════════════════════════════
usage() {
    echo "Usage: $0 [--build] [--run] [--clean]"
    echo ""
    echo "  --build   Compile firmware (deduplicates sources automatically)"
    echo "  --run     Launch Verilator simulation"
    echo "  --clean   Remove all build artifacts"
    echo ""
    echo "Edit the SOURCES array at the top of this script to add/remove files."
    echo ""
    echo "Examples:"
    echo "  $0 --build          # compile only"
    echo "  $0 --build --run    # compile + simulate"
    echo "  $0 --clean          # clean artifacts"
}

if [[ $# -eq 0 ]]; then
    usage
    exit 0
fi

DO_BUILD=false
DO_RUN=false

for arg in "$@"; do
    case "$arg" in
        --build)  DO_BUILD=true ;;
        --run)    DO_RUN=true ;;
        --clean)  do_clean; exit 0 ;;
        --help|-h) usage; exit 0 ;;
        *) fail "Unknown argument: $arg (use --help for usage)" ;;
    esac
done

$DO_BUILD && do_build
$DO_RUN   && do_run
