#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════
#  SERV Standalone Build Script
#  Usage: ./build.sh [--build] [--run] [--clean]
# ═══════════════════════════════════════════════════════════════
set -euo pipefail

# ── EDIT THIS: specify your source files ─────────────────────
# Paths are relative to the serv_project/ directory
C_SOURCE="../Codespace/SERV_codespace/popcount_SERV_return.c"
ASM_SOURCE="../Codespace/SERV_codespace/startup.S"
# ──────────────────────────────────────────────────────────────

# Project root (script's own directory)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── Toolchain ────────────────────────────────────────────────
CC=riscv64-unknown-elf-gcc
OBJCOPY=riscv64-unknown-elf-objcopy
OBJDUMP=riscv64-unknown-elf-objdump
SIZE=riscv64-unknown-elf-size

# ── Compiler flags ───────────────────────────────────────────
ARCH=rv32i
ABI=ilp32
CFLAGS="-O2 -march=$ARCH -mabi=$ABI -static -nostdlib -nostartfiles -ffreestanding"
LDSCRIPT="fusesoc_libraries/serv/sw/link.ld"
MAKEHEX="fusesoc_libraries/serv/sw/makehex.py"
RAM_WORDS=4096

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
NC='\033[0m' # No Color

info()  { echo -e "${CYAN}[INFO]${NC}  $*"; }
ok()    { echo -e "${GREEN}[OK]${NC}    $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC}  $*"; }
fail()  { echo -e "${RED}[FAIL]${NC}  $*"; exit 1; }

# ══════════════════════════════════════════════════════════════
#  BUILD: Compile firmware
# ══════════════════════════════════════════════════════════════
do_build() {
    info "Building firmware..."
    info "  C source:   $C_SOURCE"
    info "  ASM source: $ASM_SOURCE"

    # Check that source files exist
    [[ -f "$C_SOURCE" ]]   || fail "C source not found: $C_SOURCE"
    [[ -f "$ASM_SOURCE" ]] || fail "ASM source not found: $ASM_SOURCE"
    [[ -f "$LDSCRIPT" ]]   || fail "Linker script not found: $LDSCRIPT"
    [[ -f "$MAKEHEX" ]]    || fail "makehex.py not found: $MAKEHEX"

    # Step 1: Compile + link
    info "Step 1/3: gcc compile -> $ELF"
    $CC $CFLAGS \
        -T "$LDSCRIPT" \
        -o "$ELF" \
        "$ASM_SOURCE" \
        "$C_SOURCE"
    ok "Compiled: $ELF"

    # Print firmware size
    echo ""
    $SIZE "$ELF"
    echo ""

    # Step 2: ELF -> raw binary
    info "Step 2/3: objcopy -> $BIN"
    $OBJCOPY -O binary "$ELF" "$BIN"
    ok "Binary: $BIN ($(stat -c%s "$BIN") bytes)"

    # Step 3: Binary -> hex (one 32-bit word per line, for $readmemh)
    info "Step 3/3: makehex -> $HEX"
    python3 "$MAKEHEX" "$BIN" > "$HEX"
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

    info "Starting Verilator simulation..."
    info "  Core:    $FUSESOC_CORE"
    info "  Firmware: $SCRIPT_DIR/$HEX"
    info "  Baud:    $BAUD"
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
    rm -f "$ELF" "$BIN" "$HEX"
    ok "Removed: $ELF / $BIN / $HEX"
}

# ══════════════════════════════════════════════════════════════
#  Main: parse command-line arguments
# ══════════════════════════════════════════════════════════════
usage() {
    echo "Usage: $0 [--build] [--run] [--clean]"
    echo ""
    echo "  --build   Compile firmware (.c + .S -> .elf -> .bin -> .hex)"
    echo "  --run     Launch Verilator simulation"
    echo "  --clean   Remove all build artifacts"
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
