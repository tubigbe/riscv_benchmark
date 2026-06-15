# SERV RISC-V Benchmark Project

Simulation and analysis toolkit for the **SERV** — the world's smallest RISC-V CPU.
Compiles firmware, runs it on a Verilator simulation of the SERV SoC, and produces
detailed per-instruction cycle-cost reports.

---

## Project Structure

```
serv_project/
├── Codespace
│   ├── SERV_codespace
│   │   ├── factorial.c
│   │   ├── popcount.c
│   │   ├── servant_tb_template
│   │   ├── standalone_hello.S
│   │   └── startup.S
│   ├── env.sh
│   └── test_files
│       ├── firmware.c
│       ├── hello_world.c
│       ├── test.c
│       └── uart_test.S
├── README.md
├── serv_project
│   ├── build.sh
│   ├── firmware.bin
│   ├── firmware.elf
│   ├── firmware.hex
│   ├── fusesoc.conf
│   ├── fusesoc_libraries
│   │   ├── fusesoc_cores
│   │   ├── mdu
│   │   └── serv
│   ├── instr_counter.sh
│   ├── log
│   │   ├── compare_result.txt
│   │   ├── instr_count.log
│   │   ├── sim_log.txt
│   │   ├── sim_wave.vcd
│   │   └── trace_dump.txt
│   ├── run_sim.sh
│   ├── scripts
│   │   ├── compare_traces.py
│   │   ├── sim_main.cpp
│   │   └── trace_dump.py
│   ├── sim_wave.sh
│   └── tools
├── setup.sh
└── tools
    └── riscv
```

---

## Quick Start

### 1. Build firmware

```bash
./build.sh --build
```

Compiles the default factorial demo (`startup.S` + `factorial.c`) into
`firmware.elf`, `firmware.bin`, and `firmware.hex`.

### 2. Run Verilator simulation

```bash
./run_sim.sh
```

Cleans old artifacts, builds the Verilator model, runs the simulation, and
post-processes all traces. All outputs go to `log/`.

### 3. View waveform

```bash
./sim_wave.sh
```

Same as above but also opens `log/sim_wave.vcd` in GTKWave.

### 4. Count instructions

```bash
./instr_counter.sh
```

Counts every unique instruction mnemonic in `firmware.elf` and writes the
breakdown to `log/instr_count.log`.

---

## Scripts Reference

### `build.sh` — Firmware Build & Simulation

| Flag | Description |
|------|-------------|
| `--build` | Compile firmware from sources listed in the script header |
| `--run` | Launch FuseSoC-driven Verilator simulation (produces `trace.bin`) |
| `--clean` | Remove `firmware.elf`, `firmware.bin`, `firmware.hex` |

**Environment variables:**

| Variable | Description |
|----------|-------------|
| `BENCH=lw` | Use load-word benchmark sources instead of factorial demo |

**Outputs:** `firmware.elf`, `firmware.bin`, `firmware.hex`

---

### `run_sim.sh` — Verilator Simulation Pipeline

Runs the full 4-step simulation pipeline:

| Step | Action | Output |
|------|--------|--------|
| **[1/4] CLEAN** | Remove `obj_dir_custom/` | — |
| **[2/4] BUILD** | Verilator + g++ compile | `obj_dir_custom/Vservant_sim` |
| **[3/4] SIMULATE** | Run SERV simulation | `log/sim_log.txt`, `log/sim_wave.vcd` |
| **[4/4] POST-PROCESS** | `trace_dump.py` + `compare_traces.py` | `log/trace_dump.txt`, `log/compare_result.txt` |

| Flag | Description |
|------|-------------|
| *(no args)* | Clean + build + simulate (default) |
| `--clean` | Remove `obj_dir_custom/` only |
| `--build` | Build Verilator model only |
| `--run` | Run simulation only (model must exist) |
| `--firmware=FILE` | Use a different `.hex` firmware file |

**Outputs (all in `log/`):**

| File | Description |
|------|-------------|
| `sim_log.txt` | PC transitions with cycle costs per instruction |
| `sim_wave.vcd` | VCD waveform dump (viewable in GTKWave) |
| `trace_dump.txt` | Symbol-resolved PC trace from `trace.bin` |
| `compare_result.txt` | Merged trace with per-instruction cycle info and summary stats |

---

### `instr_counter.sh` — Static Instruction Counter

Counts instruction mnemonics from the ELF disassembly. Supports counting
the entire binary or a specific range between two function labels.

| Usage | Description |
|-------|-------------|
| `./instr_counter.sh` | Count all instructions in `firmware.elf` |
| `./instr_counter.sh firmware.elf` | Count in a specific ELF file |
| `./instr_counter.sh firmware.elf _start main` | Count between `<_start>` and `<main>` |

When both labels exist, only instructions between `start_label` (inclusive)
and `end_label` (exclusive) are counted. If labels are not found, falls back
to counting the entire ELF.

**Output:** `log/instr_count.log`

---

### `sim_wave.sh` — Waveform Viewer

Convenience wrapper that calls `run_sim.sh` to build and simulate, then
opens the VCD waveform in GTKWave.

| Flag | Description |
|------|-------------|
| *(no args)* | Build + simulate + open waveform |
| `--firmware=FILE` | Use a different `.hex` firmware file |

**Outputs:** Same as `run_sim.sh`, plus GTKWave window opens automatically.

**Prerequisite:** `sudo apt install gtkwave`

---

## Post-Processing Scripts (`scripts/`)

These are called automatically by `run_sim.sh` during the [4/4] POST-PROCESS step.

### `scripts/sim_main.cpp` — Verilator Testbench

The C++ testbench that drives the Verilator simulation. Monitors PC address
changes on every rising clock edge and reports the cycle cost for each
instruction transition:

```
0x4 -> 0x8 : 36 cycles
```

Redirects stdout to `log/sim_log.txt`. Also generates `log/sim_wave.vcd`
when `+vcd=1` is passed.

### `scripts/trace_dump.py` — Trace Dumper

Reads the raw `trace.bin` (32-bit PC values) generated by FuseSoC and
produces a human-readable trace with symbol resolution:

```
      3  0x0000000c  sb
      4  0x00000010  lw
```

**Output:** `log/trace_dump.txt`

### `scripts/compare_traces.py` — Trace Merger

Merges `log/sim_log.txt` (cycle costs) with `log/trace_dump.txt` (instruction
names) into a combined report. Includes summary statistics (total cycles,
average, min, max) and per-instruction averages.

**Output:** `log/compare_result.txt`

---

## Building Different Firmware

Edit the `SOURCES` array at the top of `build.sh`, or use environment variables:

```bash
# Default: factorial demo
./build.sh --build

# Load-word cycle benchmark
BENCH=lw ./build.sh --build
```

Supported source types: `.c`, `.S`, `.s`, `.asm`, `.cpp`, `.cc`

---

## Toolchain Requirements

| Tool | Package |
|------|---------|
| `riscv64-unknown-elf-gcc` | RISC-V GCC cross-compiler |
| `verilator` | `verilator` (≥ 5.0) |
| `fusesoc` | `fusesoc` (pip install) |
| `python3` | `python3` (for makehex.py, trace scripts) |
| `gtkwave` | `gtkwave` (optional, for waveform viewing) |

---

## New Teammate Setup Guide

Follow these steps to get a working development environment from scratch.

### Step 1 — Clone the repository

```bash
git clone https://github.com/tubigbe/riscv_benchmark.git
cd riscv_benchmark
```

### Step 2 — Run the setup script

The setup script fetches all submodules (SERV CPU core, FuseSoC libraries, etc.), loads the environment, and verifies your tools:

```bash
./setup.sh
```

You should see output like:

```
========================================
  riscv_benchmark setup
========================================

[INFO]  Initializing git submodules...
[OK]    Submodules ready
[INFO]  Verifying submodule content...
[OK]      serv_project/fusesoc_libraries/serv
[OK]      serv_project/fusesoc_libraries/mdu
[OK]      serv_project/fusesoc_libraries/fusesoc_cores
[INFO]  Loading environment...
[OK]    Environment loaded
[INFO]  Checking required tools...
[OK]      RISC-V GCC: /home/you/riscv_benchmark/tools/riscv64/usr/bin/riscv64-unknown-elf-gcc
[OK]      Python 3: ...
[OK]      FuseSoC: ...
[OK]      Verilator: ...
[OK]      Make: ...
========================================
[OK]    Setup complete! All tools ready.
========================================
```

If any tool shows "not found", see the **Troubleshooting** section below.

### Step 3 — Load the environment

The environment is **auto-loaded** when you open a terminal inside `~/riscv_benchmark/` (via `.bashrc` integration).

To load it manually in any terminal:

```bash
source ~/riscv_benchmark/Codespace/env.sh
```

This adds the RISC-V toolchain, FuseSoC, Verilator, and Make to your `PATH`.

### Step 4 — Build and run your first simulation

```bash
cd ~/riscv_benchmark/serv_project
./build.sh --build --run
```

You should see:

```
[INFO]  Building firmware...
[INFO]  Compiling + linking -> firmware.elf
[OK]    Linked: firmware.elf
[OK]    Binary: firmware.bin (642 bytes)
[OK]    Hex: firmware.hex (161 words)
[OK]    Build done!
[INFO]  Starting Verilator simulation...
Loading RAM from firmware.hex
factorial:
  1! = 1
  2! = 2
  ...
  10! = 3628800
done
Test complete
[OK]    Trace saved: .../trace.bin (20988 PC entries)
```