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
export RISCV64_TOOLS="$RISCV_BENCHMARK/tools/riscv64/usr/bin"
export FUSESOC_VENV="$RISCV_BENCHMARK/tools/fusesoc-venv/bin"
export MAKE_TOOLS="$RISCV_BENCHMARK/tools/make/usr/bin"
export GCC_HOST_TOOLS="$RISCV_BENCHMARK/tools/gcc-host/usr/bin"
export GCC_HOST_INCLUDE="$RISCV_BENCHMARK/tools/gcc-host/usr/local/include"
export VERILATOR_TOOLS="$RISCV_BENCHMARK/tools/verilator/usr/bin"

path_prepend_once "$HOME/.local/bin"
path_prepend_once "$FUSESOC_VENV"
path_prepend_once "$VERILATOR_TOOLS"
path_prepend_once "$MAKE_TOOLS"
path_prepend_once "$RISCV64_TOOLS"
path_prepend_once "$RISCV/bin"

# ----------------------------
# Host tools
# ----------------------------
export PYTHON="/usr/bin/python3"
export PIP="/usr/bin/pip3"
export VERILATOR="$(which verilator 2>/dev/null || echo $VERILATOR_TOOLS/verilator)"
if [[ -x "$FUSESOC_VENV/fusesoc" ]]; then
    export FUSESOC="$FUSESOC_VENV/fusesoc"
else
    export FUSESOC="$(which fusesoc 2>/dev/null || echo $HOME/.local/bin/fusesoc)"
fi
export CPATH="${CPATH:+:$CPATH}"
export C_INCLUDE_PATH="${C_INCLUDE_PATH:+:$C_INCLUDE_PATH}"
export CPLUS_INCLUDE_PATH="${CPLUS_INCLUDE_PATH:+:$CPLUS_INCLUDE_PATH}"

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
