#!/usr/bin/env bash

# ============================================================
# riscv_benchmark unified environment
# Generic RISC-V simulation environment
# SERV + Ibex + Verilator
# ============================================================

# ----------------------------
# Helper: prepend PATH only once
# ----------------------------
path_prepend_once() {
    case ":$PATH:" in
        *":$1:"*) ;;
        *) export PATH="$1:$PATH" ;;
    esac
}

# ----------------------------
# Project paths
# ----------------------------
export RISCV_BENCHMARK="$HOME/riscv_benchmark"
export CODESPACE_DIR="$RISCV_BENCHMARK/Codespace"
export SERV_PROJECT="$RISCV_BENCHMARK/serv_project"
export IBEX_PROJECT="$RISCV_BENCHMARK/ibex_project"
export IBEX_REPO="$IBEX_PROJECT/vendor/ibex"

# ----------------------------
# Project-local tool wrappers
# ----------------------------
export RISCV="$RISCV_BENCHMARK/tools/riscv"
path_prepend_once "$HOME/.local/bin"
path_prepend_once "$RISCV/bin"

# ----------------------------
# Host tools
# ----------------------------
export PYTHON="/usr/bin/python3"
export PIP="/usr/bin/pip3"
export VERILATOR="/usr/bin/verilator"
export FUSESOC="$HOME/.local/bin/fusesoc"

# ----------------------------
# RISC-V bare-metal toolchain
# ----------------------------
export RISCV64_PREFIX="riscv64-unknown-elf-"
export RISCV32_PREFIX="riscv32-unknown-elf-"

export RISCV_GCC="/usr/bin/riscv64-unknown-elf-gcc"
export RISCV_OBJCOPY="/usr/bin/riscv64-unknown-elf-objcopy"
export RISCV_OBJDUMP="/usr/bin/riscv64-unknown-elf-objdump"
export RISCV_READELF="/usr/bin/riscv64-unknown-elf-readelf"

# Default RV32 target.
# Keep zicsr/zifencei because modern RISC-V GCC requires them explicitly
# when compiling CSR/fence.i instructions.
export RISCV_ARCH="rv32imc_zicsr_zifencei"
export RISCV_ABI="ilp32"

# ----------------------------
# Helpful aliases
# ----------------------------
alias rb='cd "$RISCV_BENCHMARK"'
alias codes='cd "$CODESPACE_DIR"'
alias servp='cd "$SERV_PROJECT"'
alias ibexp='cd "$IBEX_PROJECT"'
alias ibexr='cd "$IBEX_REPO"'

# ----------------------------
# Environment report
# This prints every time the script is sourced.
# If ~/.bashrc sources this file, it prints whenever a new Ubuntu terminal starts.
# ----------------------------
echo "[riscv_benchmark env loaded]"
echo "RISCV_BENCHMARK = $RISCV_BENCHMARK"
echo "CODESPACE_DIR   = $CODESPACE_DIR"
echo "SERV_PROJECT    = $SERV_PROJECT"
echo "IBEX_PROJECT    = $IBEX_PROJECT"
echo "IBEX_REPO       = $IBEX_REPO"
echo "RISCV           = $RISCV"
echo "PATH prepend    = $RISCV/bin:$HOME/.local/bin"
echo "PYTHON          = $PYTHON"
echo "PIP             = $PIP"
echo "VERILATOR       = $VERILATOR"
echo "FUSESOC         = $(which fusesoc 2>/dev/null || echo not-found)"
echo "RISCV_ARCH      = $RISCV_ARCH"
echo "RISCV_ABI       = $RISCV_ABI"
echo "RV32 GCC        = $(which riscv32-unknown-elf-gcc 2>/dev/null || echo not-found)"
echo "RV64 GCC        = $(which riscv64-unknown-elf-gcc 2>/dev/null || echo not-found)"
echo "RISCV_GCC       = $RISCV_GCC"
echo "RISCV_OBJCOPY   = $RISCV_OBJCOPY"
echo "RISCV_OBJDUMP   = $RISCV_OBJDUMP"
echo "RISCV_READELF   = $RISCV_READELF"
