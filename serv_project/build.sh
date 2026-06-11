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
SOURCES=(
    "../Codespace/SERV_codespace/popcount_SERV_return.c"
    "../Codespace/SERV_codespace/startup.S"
)
# ──────────────────────────────────────────────────────────────

# Project root (script's own directory)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── Toolchain ────────────────────────────────────────────────
CC=riscv64-unknown-elf-gcc
CXX=riscv64-unknown-elf-g++
OBJCOPY=riscv64-unknown-elf-objcopy
SIZE=riscv64-unknown-elf-size

# ── Compiler flags ───────────────────────────────────────────
ARCH=rv32i
ABI=ilp32
COMMON_FLAGS="-march=$ARCH -mabi=$ABI -static -nostdlib -nostartfiles -ffreestanding"
CFLAGS="-O2 $COMMON_FLAGS"
LDSCRIPT="fusesoc_libraries/serv/sw/link.ld"
MAKEHEX="fusesoc_libraries/serv/sw/makehex.py"

# ── Output files ─────────────────────────────────────────────
ELF="firmware.elf"
BIN="firmware.bin"
HEX="firmware.hex"

# ── Simulation settings ──────────────────────────────────────
FUSESOC_CORE="award-winning:serv:servant:1.4.0"
BAUD=57600
SIM_TIMEOUT=10

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
# ══════════════════════════════════════════════════════════════
do_build() {
    info "Building firmware..."
    echo ""

    [[ -f "$LDSCRIPT" ]] || fail "Linker script not found: $LDSCRIPT"
    [[ -f "$MAKEHEX" ]]  || fail "makehex.py not found: $MAKEHEX"

    # Deduplicate + validate sources
    declare -A SEEN
    local OBJ_FILES=()
    local COMPILED=0
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

        # Classify and compile
        classify_file "$src"
        local basename="${src##*/}"
        local obj="build_${basename%.*}.o"

        info "Compiling: $src -> $obj"
        $COMPILER $CFLAGS $XFLAG -c -o "$obj" "$src"
        ok "Compiled: $obj"
        OBJ_FILES+=("$obj")
        COMPILED=$((COMPILED + 1))
        echo ""
    done

    [[ $COMPILED -eq 0 ]] && fail "No source files were compiled"
    [[ $SKIPPED -gt 0 ]]  && info "Summary: $COMPILED compiled, $SKIPPED skipped"

    # Link
    info "Linking -> $ELF"
    $CC $CFLAGS -T "$LDSCRIPT" -o "$ELF" "${OBJ_FILES[@]}"
    ok "Linked: $ELF"

    echo ""
    $SIZE "$ELF"
    echo ""

    # ELF -> binary -> hex
    info "objcopy -> $BIN"
    $OBJCOPY -O binary "$ELF" "$BIN"
    ok "Binary: $BIN ($(stat -c%s "$BIN") bytes)"

    info "makehex -> $HEX"
    python3 "$MAKEHEX" "$BIN" > "$HEX"
    local hex_lines
    hex_lines=$(wc -l < "$HEX")
    ok "Hex: $HEX ($hex_lines words)"

    # Cleanup intermediates
    rm -f "${OBJ_FILES[@]}"

    echo ""
    ok "Build done! Outputs: $ELF / $BIN / $HEX"
}

# ══════════════════════════════════════════════════════════════
#  RUN: Launch Verilator simulation
# ══════════════════════════════════════════════════════════════
do_run() {
    [[ -f "$HEX" ]] || fail "Firmware not found: $HEX — run ./build.sh --build first"

    info "Starting Verilator simulation..."
    info "  Core:     $FUSESOC_CORE"
    info "  Firmware: $SCRIPT_DIR/$HEX"
    info "  Baud:     $BAUD"
    echo ""

    timeout "${SIM_TIMEOUT}s" \
        fusesoc run --target=verilator_tb "$FUSESOC_CORE" \
            --uart_baudrate="$BAUD" \
            --firmware="$SCRIPT_DIR/$HEX" \
        || {
            local exit_code=$?
            if [[ $exit_code -eq 124 ]]; then
                warn "Simulation timed out (${SIM_TIMEOUT}s) — terminated"
            else
                fail "Simulation failed (exit code: $exit_code)"
            fi
        }
}

# ══════════════════════════════════════════════════════════════
#  CLEAN: Remove build artifacts
# ══════════════════════════════════════════════════════════════
do_clean() {
    info "Cleaning build artifacts..."
    rm -f "$ELF" "$BIN" "$HEX" build_*.o
    ok "Removed: $ELF / $BIN / $HEX / build_*.o"
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
