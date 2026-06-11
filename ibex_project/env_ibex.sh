#!/usr/bin/env bash

source ~/riscv_benchmark/env.sh
source ~/riscv_benchmark/ibex_project/.venv/bin/activate

export IBEX_PROJECT=~/riscv_benchmark/ibex_project
export IBEX_REPO=$IBEX_PROJECT/vendor/ibex
export IBEX_SIM=$IBEX_REPO/build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system

echo "[Ibex env loaded]"
echo "IBEX_REPO = $IBEX_REPO"
echo "IBEX_SIM  = $IBEX_SIM"
echo "Python    = $(which python3)"
echo "FuseSoC   = $(which fusesoc)"
echo "Verilator = $(which verilator)"
