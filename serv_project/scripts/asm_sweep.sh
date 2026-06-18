#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════════════
#  Assembly Instruction Sweep & Diff Script
# ═══════════════════════════════════════════════════════════════════════
#
#  Purpose:
#    Systematically tests how different compiler optimization levels
#    and constant input values (B) affect the generated RISC-V assembly
#    instructions for assemb_instr_ckeck.c. After the sweep, automatically
#    diffs instruction types across B values with B=10 as the baseline.
#
#  Sweep:
#    Outer loop — optimization levels: O0, O1, O2, O3, Os
#    Inner loop — B values: 0 through 101
#    Total: 5 × 102 = 510 builds
#
#  Diff:
#    After each optimization level sweep, compares every B's instruction
#    types against B=10 (the baseline). Records:
#      - Instruction changes (+added / -removed)
#      - Build failures (marked as FAIL in sweep log)
#
#  Output:
#    log/sweep/sweep_O<level>.log  — sweep results (including FAIL lines)
#    log/diff/diff_O<level>.log    — diff against B=10 baseline
#
#  Usage:
#    ./scripts/asm_sweep.sh              # run full sweep + diff
#    ./scripts/asm_sweep.sh --clear      # clear all the log files
#    ./scripts/asm_sweep.sh --help       # show help
#
#  Safety:
#    build.sh and assemb_instr_ckeck.c are backed up at start and
#    restored on exit (even on error) via trap.
#
# ═══════════════════════════════════════════════════════════════════════
set -euo pipefail

# ── Paths ──────────────────────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_SCRIPT="$PROJECT_DIR/build.sh"
C_FILE="$PROJECT_DIR/../Codespace/SERV_codespace/Week_3/Task_2/assemb_instr_ckeck.c"
INSTR_COUNTER="$PROJECT_DIR/instr_counter.sh"
LOG_DIR="$PROJECT_DIR/log"
SWEEP_DIR="$LOG_DIR/sweep"
DIFF_DIR="$LOG_DIR/diff"
INSTR_LOG="$LOG_DIR/instr_count.log"

# ── Backup originals ───────────────────────────────────────────────────
BUILD_BAK=$(mktemp)
C_FILE_BAK=$(mktemp)
cp "$BUILD_SCRIPT" "$BUILD_BAK"
cp "$C_FILE" "$C_FILE_BAK"

cleanup() {
    cp "$BUILD_BAK" "$BUILD_SCRIPT"
    cp "$C_FILE_BAK" "$C_FILE"
    rm -f "$BUILD_BAK" "$C_FILE_BAK"
}
trap cleanup EXIT

# ── Usage ──────────────────────────────────────────────────────────────
usage() {
    echo "Usage: $0 [--clear]"
    echo ""
    echo "Sweeps optimization levels (O0, O1, O2, O3, Os) × B values (0–101)"
    echo "and records instruction types for each combination."
    echo ""
    echo "Output:"
    echo "  log/sweep/sweep_O<level>.log  — sweep results"
    echo "  log/diff/diff_O<level>.log    — diff against B=10 baseline"
    echo ""
    echo "Options:"
    echo "  --clear   Remove all sweep and diff log files"
    echo "  --help    Show this help message"
    exit 0
}

# ── Handle --clear ─────────────────────────────────────────────────────
if [[ "${1:-}" == "--clear" ]]; then
    echo "Clearing sweep and diff logs..."
    rm -rf "$LOG_DIR/sweep" "$LOG_DIR/diff"
    mkdir -p "$LOG_DIR/sweep" "$LOG_DIR/diff"
    echo "Done. Removed: $LOG_DIR/sweep/* $LOG_DIR/diff/*"
    exit 0
fi

[[ "${1:-}" == "--help" || "${1:-}" == "-h" ]] && usage

# ── Configuration ──────────────────────────────────────────────────────
OPT_LEVELS=(O0 O1 O2 O3 Os)
B_START=0
B_END=101

# ── Colored output helpers ─────────────────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

info()  { echo -e "${CYAN}[INFO]${NC}  $*"; }
ok()    { echo -e "${GREEN}[OK]${NC}    $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC}  $*"; }
fail()  { echo -e "${RED}[FAIL]${NC}  $*" >&2; }

# ── Validate paths ─────────────────────────────────────────────────────
for f in "$BUILD_SCRIPT" "$C_FILE" "$INSTR_COUNTER"; do
    [[ -f "$f" ]] || { echo "Error: required file not found: $f" >&2; exit 1; }
done

mkdir -p "$LOG_DIR"
mkdir -p "$SWEEP_DIR"
mkdir -p "$DIFF_DIR"

# ── Parse instr_count.log → comma-separated instruction types ──────────
extract_types() {
    # instr_count.log lines look like:  "addi       : 45"
    # Extract the mnemonic (field before the colon), skip header/footer lines.
    awk '/:/{ gsub(/[[:space:]]*:[[:space:]]*/, ":"); split($0, a, ":"); if (a[1] ~ /^[a-z]+/) print a[1] }' "$1" \
        | sort -u \
        | paste -sd ',' -
}

# ── Diff function: compare sweep log against B=10 baseline ────────────
# Reads a sweep log, compares every B entry against the B=10 baseline.
# Failed builds (lines containing "FAIL") are flagged in the diff output.
diff_sweep_log() {
    local sweep_file="$1"
    local level="$2"
    local diff_file="$DIFF_DIR/diff_${level}.log"

    info "Diffing: $sweep_file → $diff_file"

    awk -v diff_file="$diff_file" -v baseline_b=10 '
    BEGIN {
        baseline_set = 0
        baseline_sorted = ""
        baseline_b = baseline_b + 0
        n_diffs = 0
        n_total = 0
        n_fails = 0
    }

    /^#/ { next }
    /^[[:space:]]*$/ { next }

    {
        n_total++

        split($0, parts, " : ")
        b_part = parts[1]
        sub(/^B=/, "", b_part)
        b_val = b_part + 0

        types = parts[2]
        gsub(/[[:space:]]/, "", types)

        # Detect failed builds
        if (types == "FAIL" || types ~ /FAIL/) {
            n_fails++
            if (baseline_set) {
                printf "B=%-4d          BUILD FAILED (baseline B=%d has: %s)\n", b_val, baseline_b, baseline_sorted > diff_file
            } else {
                printf "B=%-4d          BUILD FAILED (no baseline yet)\n", b_val > diff_file
            }
            next
        }

        # Sort instruction types for comparison
        n = split(types, tarr, ",")
        for (i = 2; i <= n; i++) {
            key = tarr[i]
            j = i - 1
            while (j >= 1 && tarr[j] > key) {
                tarr[j+1] = tarr[j]
                j--
            }
            tarr[j+1] = key
        }
        sorted = ""
        for (i = 1; i <= n; i++) {
            if (i > 1) sorted = sorted ","
            sorted = sorted tarr[i]
        }

        # Set baseline at B=10
        if (b_val == baseline_b && !baseline_set) {
            baseline_sorted = sorted
            baseline_set = 1
            printf "# Diff log: %s\n", diff_file > diff_file
            printf "# Baseline: B=%d uses: %s\n\n", b_val, sorted > diff_file
            next
        }

        # Compare against baseline (only once baseline is set)
        if (!baseline_set) next

        if (sorted != baseline_sorted) {
            n_diffs++

            nb = split(baseline_sorted, ba, ",")
            nc = split(sorted, ca, ",")

            added = ""
            removed = ""

            for (c = 1; c <= nc; c++) {
                found = 0
                for (p = 1; p <= nb; p++) {
                    if (ca[c] == ba[p]) { found = 1; break }
                }
                if (!found) {
                    if (added != "") added = added ","
                    added = added ca[c]
                }
            }

            for (p = 1; p <= nb; p++) {
                found = 0
                for (c = 1; c <= nc; c++) {
                    if (ba[p] == ca[c]) { found = 1; break }
                }
                if (!found) {
                    if (removed != "") removed = removed ","
                    removed = removed ba[p]
                }
            }

            printf "B=%-4d vs B=%-4d", b_val, baseline_b > diff_file
            if (added != "")   printf "  +%s", added > diff_file
            if (removed != "") printf "  -%s", removed > diff_file
            printf "\n" > diff_file
        }
    }

    END {
        if (!baseline_set) {
            printf "# Diff log: %s\n", diff_file > diff_file
            printf "# WARNING: Baseline B=%d not found or failed — no comparison possible\n", baseline_b > diff_file
        }
        printf "\n─────────────────────────────────────────────\n" > diff_file
        printf "Total B values checked: %d\n", n_total > diff_file
        printf "Build failures:         %d\n", n_fails > diff_file
        printf "Instruction diffs:      %d  (vs B=%d baseline)\n", n_diffs, baseline_b > diff_file
        printf "─────────────────────────────────────────────\n" > diff_file
    }
    ' "$sweep_file"

    local diff_count
    diff_count=$(grep -c '^B=' "$diff_file" 2>/dev/null || echo "0")
    ok "Diff done: $diff_count entries → $diff_file"
}

# ── Counters ───────────────────────────────────────────────────────────
TOTAL=0
SUCCESSES=0
FAILURES=0

TOTAL_BUILDS=$(( ${#OPT_LEVELS[@]} * (B_END - B_START + 1) ))
info "Sweep: ${#OPT_LEVELS[@]} opt levels × $((B_END - B_START + 1)) B values = ${TOTAL_BUILDS} builds"
info "Output: $SWEEP_DIR/sweep_O<level>.log"
echo ""

# ── OUTER LOOP: optimization levels ────────────────────────────────────
for opt in "${OPT_LEVELS[@]}"; do
    SWEEP_LOG="$SWEEP_DIR/sweep_${opt}.log"
    OPT_OK=0
    OPT_FAIL=0

    echo -e "${BOLD}=== $opt ===${NC}"

    # Rewrite build.sh: set optimization level
    sed -i "s|CFLAGS=\"-O[0-9s]* |CFLAGS=\"-${opt} |" "$BUILD_SCRIPT"

    # Rewrite build.sh: point SOURCES to assemb_instr_ckeck.c
    sed -i 's|"../Codespace/SERV_codespace/factorial\.c"|"../Codespace/SERV_codespace/Week_3/Task_2/assemb_instr_ckeck.c"|' "$BUILD_SCRIPT"

    # Start fresh log for this optimization level
    echo "# Optimization level: $opt" > "$SWEEP_LOG"
    echo "# Format: B=<value> : <instruction_types>" >> "$SWEEP_LOG"

    # ── INNER LOOP: B values ───────────────────────────────────────
    for (( b = B_START; b <= B_END; b++ )); do
        TOTAL=$((TOTAL + 1))

        # Rewrite B value in assemb_instr_ckeck.c
        sed -i "s|const int B = [0-9]*;|const int B = $b;|" "$C_FILE"

        # Build (capture stderr for error reporting)
        BUILD_LOG=$(mktemp)
        if ! "$BUILD_SCRIPT" --build > "$BUILD_LOG" 2>&1; then
            fail "O${opt} B=${b}: build failed — skipping"
            tail -5 "$BUILD_LOG" >&2
            rm -f "$BUILD_LOG"
            echo "B=${b} : FAIL" >> "$SWEEP_LOG"
            OPT_FAIL=$((OPT_FAIL + 1))
            FAILURES=$((FAILURES + 1))
            continue
        fi
        rm -f "$BUILD_LOG"

        # Count instructions
        INST_LOG=$(mktemp)
        if ! "$INSTR_COUNTER" > "$INST_LOG" 2>&1; then
            fail "O${opt} B=${b}: instr_counter failed — skipping"
            tail -3 "$INST_LOG" >&2
            rm -f "$INST_LOG"
            echo "B=${b} : FAIL" >> "$SWEEP_LOG"
            OPT_FAIL=$((OPT_FAIL + 1))
            FAILURES=$((FAILURES + 1))
            continue
        fi
        rm -f "$INST_LOG"

        # Extract instruction types and log
        TYPES=$(extract_types "$INSTR_LOG")
        echo "B=${b} : ${TYPES}" >> "$SWEEP_LOG"

        SUCCESSES=$((SUCCESSES + 1))
        OPT_OK=$((OPT_OK + 1))
        printf "  B=%-4d %s\n" "$b" "$TYPES"
    done

    ok "$opt: ${OPT_OK}/$((B_END - B_START + 1)) succeeded, ${OPT_FAIL} failed"

    # Run diff against B=10 baseline for this optimization level
    diff_sweep_log "$SWEEP_LOG" "$opt"
    echo ""
done

# ── Grand summary ──────────────────────────────────────────────────────
echo -e "${BOLD}════════════════════════════════════════════════════${NC}"
echo -e "${BOLD}  Sweep complete: ${TOTAL} total builds${NC}"
echo -e "  ${GREEN}Successes: ${SUCCESSES}${NC}"
[[ $FAILURES -gt 0 ]] && echo -e "  ${RED}Failures:  ${FAILURES}${NC}"
echo -e "  Sweep logs: ${SWEEP_DIR}/sweep_O*.log"
echo -e "  Diff logs:  ${DIFF_DIR}/diff_O*.log  (baseline: B=10)"
echo -e "${BOLD}════════════════════════════════════════════════════${NC}"
