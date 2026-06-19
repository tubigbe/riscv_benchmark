# SERV RISC-V Benchmark Project

Simulation and analysis toolkit for the **SERV** — the world's smallest RISC-V CPU.
Compiles firmware, runs it on a Verilator simulation of the SERV SoC, and produces
detailed per-instruction cycle-cost reports.

---

## Project Structure

```
riscv_benchmark/
├── Codespace/
│   ├── env.sh                        Environment setup (toolchain PATH)
│   └── SERV_codespace/               Firmware source files
│       ├── build_codes/              ← Default build folder
│       │   ├── startup.S
│       │   └── popcount.c
│       ├── factorial.c
│       ├── popcount.c
│       ├── standalone_hello.S
│       ├── startup.S
│       └── Week_3/                   Assignment folders
│           └── Task_2/
│               └── assemb_instr_ckeck.c
├── serv_project/
│   ├── build.sh                      Firmware build script
│   ├── run_sim.sh                    Verilator simulation pipeline
│   ├── sim_wave.sh                   Waveform viewer wrapper
│   ├── instr_counter.sh              Static instruction counter
│   ├── fusesoc.conf                  FuseSoC library config
│   ├── fusesoc_libraries/            SERV RTL + peripherals
│   │   ├── serv/                     SERV CPU core + SoC
│   │   │   ├── rtl/                  CPU core (serv_top, serv_alu, …)
│   │   │   ├── servant/              SoC wrapper (RAM, UART, GPIO, timer)
│   │   │   ├── servile/              Wishbone bus arbiter
│   │   │   ├── bench/                Testbench modules
│   │   │   └── sw/
│   │   │       ├── link.ld           Linker script (4KB RAM @ 0x0000)
│   │   │       └── makehex.py        Binary → Verilog hex converter
│   │   ├── fusesoc_cores/            Generic Wishbone peripherals
│   │   └── mdu/                      Multiply/divide extension (unused)
│   ├── scripts/
│   │   ├── sim_main.cpp              Verilator C++ testbench
│   │   ├── trace_dump.py             trace.bin → symbol-resolved text
│   │   ├── compare_traces.py         Merge cycle costs + trace
│   │   ├── cycle_cost.sh             Cycle cost between two PCs
│   │   └── asm_sweep.sh              Optimization level sweep & diff
│   ├── build/                        Verilator build output
│   ├── log/                          Simulation & analysis logs
│   └── obj_dir_custom/               Compiled Verilator model
├── ibex_project/                     Ibex CPU benchmarks (separate)
├── tools/riscv/                      RISC-V toolchain binaries
├── setup.sh                          One-time environment setup
└── README.md
```

---

## Quick Start

### 1. First-time setup

```bash
cd riscv_benchmark
./setup.sh               # Fetch submodules, verify tools
source Codespace/env.sh  # Load toolchain into PATH
```

### 2. Build firmware

```bash
cd serv_project
./build.sh --build
```

Auto-discovers sources from `Codespace/SERV_codespace/build_codes/`
(`startup.S` + `popcount.c` by default). Outputs `firmware.elf`, `firmware.bin`,
`firmware.hex`.

### 3. Run simulation

```bash
./run_sim.sh
```

Cleans old artifacts, builds the Verilator model, runs the simulation, and
post-processes all traces. All outputs go to `log/`.

### 4. View waveform

```bash
./sim_wave.sh
```

Same as above but also opens `log/sim_wave.vcd` in GTKWave.

---

## Cycle Cost Toolchain

The full pipeline for measuring per-instruction cycle costs:

```
 ┌─────────────┐     ┌──────────────┐     ┌──────────────────┐
 │  build.sh   │────▶│  run_sim.sh  │────▶│  Post-processing │
 │  .c/.S → .hex│     │  Verilator   │     │  trace_dump.py   │
 └─────────────┘     │  simulation  │     │  compare_traces.py│
                     └──────────────┘     └──────────────────┘
                                                  │
                                                  ▼
                                         log/compare_result.txt
                                                  │
                                                  ▼
                                         scripts/cycle_cost.sh
                                         (cycle cost between two PCs)
```

**Step by step:**

```bash
# 1. Build firmware
./build.sh --build

# 2. Run simulation (generates trace + cycle costs)
./run_sim.sh

# 3. View merged results
cat log/compare_result.txt

# 4. Analyze cycle cost between two addresses
./scripts/cycle_cost.sh 0x48 0x6c
```

**What each stage produces:**

| Stage | Script | Output | Description |
|-------|--------|--------|-------------|
| Build | `build.sh` | `firmware.hex` | Compiled firmware loaded into simulation RAM |
| Simulate | `run_sim.sh` → `sim_main.cpp` | `log/sim_log.txt` | PC transitions with cycle counts |
| Simulate | `run_sim.sh` → `sim_main.cpp` | `log/sim_wave.vcd` | VCD waveform (optional) |
| Trace | `trace_dump.py` | `log/trace_dump.txt` | Symbol-resolved PC trace from `trace.bin` |
| Merge | `compare_traces.py` | `log/compare_result.txt` | Combined trace with per-instruction cycle info |
| Analyze | `cycle_cost.sh` | `log/cycle_cost_<s>_<e>.txt` | Cycle cost between two PC addresses |

**Key insight:** `sim_main.cpp` monitors the `pc_vld` and `pc_adr` signals from the
SERV CPU on every rising clock edge. When the PC changes, it records the elapsed
cycles — this is the hardware cycle cost of executing the instruction at the
previous PC. Some instructions (e.g. `sw`, `lbu`) span two RAM accesses and appear
as two entries in `sim_log.txt`; `compare_traces.py` merges these automatically.

---

## Scripts Reference

### `build.sh` — Firmware Build

Auto-discovers source files from a folder under `Codespace/SERV_codespace/` and
compiles them into a RISC-V firmware image.

| Flag | Description |
|------|-------------|
| `--build` | Compile firmware (default: from `build_codes/`) |
| `--run` | Launch FuseSoC-driven Verilator simulation |
| `--folder=NAME` | Build from `SERV_codespace/NAME/` instead of `build_codes/` |
| `--clear` | Remove `firmware.elf`, `firmware.bin`, `firmware.hex` |

**Folder mode:** Without `--folder`, sources are auto-discovered from
`Codespace/SERV_codespace/build_codes/`. With `--folder=<name>`, sources are
scanned from the named subfolder. Assembly files (`.s`/`.S`) are placed before
C/C++ files automatically so `_start` lands at address 0. The folder is also
added to `-I` for local `#include` support.

**Supported extensions:** `.s`, `.S`, `.c`, `.cc`, `.cpp`, `.cxx`, `.c++`

**Compiler flags:** `-march=rv32i -mabi=ilp32 -O2 -static -nostdlib -nostartfiles -ffreestanding`

**Outputs:** `firmware.elf`, `firmware.bin`, `firmware.hex`

```bash
# Default: build from build_codes/
./build.sh --build

# Build from a specific folder
./build.sh --folder=Week_3/Task_2 --build

# Build + simulate
./build.sh --build --run
```

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
| `--clear` | Remove log files (`sim_log.txt`, `trace_dump.txt`, etc.) |
| `--firmware=FILE` | Use a different `.hex` firmware file |

**Outputs (all in `log/`):**

| File | Description |
|------|-------------|
| `sim_log.txt` | PC transitions with cycle costs per instruction |
| `sim_wave.vcd` | VCD waveform dump (viewable in GTKWave) |
| `trace_dump.txt` | Symbol-resolved PC trace from `trace.bin` |
| `compare_result.txt` | Merged trace with per-instruction cycle info and summary stats |

---

### `sim_wave.sh` — Waveform Viewer

Convenience wrapper that calls `run_sim.sh` to build and simulate, then
opens the VCD waveform in GTKWave.

| Flag | Description |
|------|-------------|
| *(no args)* | Build + simulate + open waveform |
| `--firmware=FILE` | Use a different `.hex` firmware file |
| `--clear` | Remove log files and VCD |

**Prerequisite:** `sudo apt install gtkwave`

---

### `instr_counter.sh` — Static Instruction Counter

Counts instruction mnemonics from the ELF disassembly. Supports counting
the entire binary or a specific range between two function labels.

| Usage | Description |
|-------|-------------|
| `./instr_counter.sh` | Count all instructions in `firmware.elf` |
| `./instr_counter.sh firmware.elf` | Count in a specific ELF file |
| `./instr_counter.sh firmware.elf _start main` | Count between `<_start>` and `<main>` |
| `./instr_counter.sh --clear` | Remove the generated log file |

When both labels exist, only instructions between `start_label` (inclusive)
and `end_label` (exclusive) are counted. If labels are not found, falls back
to counting the entire ELF.

**Output:** `log/instr_count.log`

---

### `scripts/sim_main.cpp` — Verilator Testbench

The C++ testbench that drives the Verilator simulation. Compiled by `run_sim.sh`
into the `Vservant_sim` binary. Monitors PC address changes on every rising clock
edge and reports the cycle cost for each instruction transition:

```
0x4 -> 0x8 : 36 cycles
```

Also generates `log/sim_wave.vcd` when `+vcd=1` is passed.

---

### `scripts/trace_dump.py` — Trace Dumper

Reads the raw `trace.bin` (32-bit PC values) generated by the simulation and
produces a human-readable trace with symbol resolution via `riscv64-unknown-elf-objdump`:

```
  index  0x0000000c  sb
  index  0x00000010  lw
```

Also generates `firmware.dump` (full disassembly with `-M no-aliases,numeric`).

| Usage | Description |
|-------|-------------|
| `python3 scripts/trace_dump.py` | Auto-detect paths |
| `python3 scripts/trace_dump.py <trace.bin> [firmware.elf] [output.txt]` | Custom paths |
| `python3 scripts/trace_dump.py --clear` | Remove generated files |

**Output:** `log/trace_dump.txt`, `firmware.dump`

---

### `scripts/compare_traces.py` — Trace Merger

Merges `log/sim_log.txt` (cycle costs) with `log/trace_dump.txt` (instruction
names) into a combined report. Handles two-part instructions (e.g. `sw`, `lbu`
that span two RAM accesses) by merging `???` continuation entries into the
preceding instruction.

Includes summary statistics (total cycles, average, min, max) and per-instruction
averages.

**Output:** `log/compare_result.txt`

---

### `scripts/cycle_cost.sh` — Cycle Cost Calculator

Reads `log/compare_result.txt` and calculates the total cycle cost between two
user-specified PC addresses. Normalizes addresses to `0x000000XX` format.

| Usage | Description |
|-------|-------------|
| `./scripts/cycle_cost.sh <start> <end>` | Calculate cycle cost in range |
| `./scripts/cycle_cost.sh --clear` | Remove dump files |

Addresses can be passed as bare hex (`48 6c`), with `0x` prefix (`0x48 0x6c`),
or full-width (`0x00000048 0x0000006c`).

**Output:** `log/cycle_cost_<start>_<end>.txt` + terminal breakdown

---

### `scripts/asm_sweep.sh` — Optimization Level Sweep

Systematically tests how different compiler optimization levels and constant
input values affect generated RISC-V assembly. Sweeps 5 optimization levels
(O0–O3, Os) × 102 B values (0–101) = 510 builds, then diffs each B against
B=10 as the baseline.

| Usage | Description |
|-------|-------------|
| `./scripts/asm_sweep.sh` | Run full sweep + diff |
| `./scripts/asm_sweep.sh --clear` | Remove all sweep and diff log files |

**Outputs:**
- `log/sweep/sweep_O<level>.log` — sweep results per optimization level
- `log/diff/consolidated_diff.log` — consolidated diff report

---

## Toolchain Requirements

| Tool | Package | Used by |
|------|---------|---------|
| `riscv64-unknown-elf-gcc` | RISC-V GCC cross-compiler | `build.sh` |
| `riscv64-unknown-elf-objcopy` | ELF → binary conversion | `build.sh` |
| `riscv64-unknown-elf-objdump` | Disassembly + symbol resolution | `instr_counter.sh`, `trace_dump.py` |
| `verilator` (≥ 5.0) | Verilog → C++ compilation | `run_sim.sh` |
| `g++` | C++ compilation | `run_sim.sh` |
| `fusesoc` | FuseSoC package manager | `run_sim.sh` (via `build.sh --run`) |
| `python3` | Script runtime | `build.sh` (makehex.py), `trace_dump.py`, `compare_traces.py` |
| `gtkwave` | Waveform viewer (optional) | `sim_wave.sh` |

---

## New Teammate Setup Guide

### Step 1 — Clone the repository

```bash
git clone https://github.com/tubigbe/riscv_benchmark.git
cd riscv_benchmark
```

### Step 2 — Run the setup script

```bash
./setup.sh
```

This fetches all submodules (SERV CPU core, FuseSoC libraries), loads the
environment, and verifies your tools.

### Step 3 — Load the environment

The environment is auto-loaded when you open a terminal inside `~/riscv_benchmark/`.
To load manually:

```bash
source ~/riscv_benchmark/Codespace/env.sh
```

### Step 4 — Build and run your first simulation

```bash
cd ~/riscv_benchmark/serv_project
./build.sh --build --run
```

### Step 5 — Analyze cycle costs

```bash
# View the merged trace with per-instruction cycle info
cat log/compare_result.txt

# Calculate cycle cost between two addresses
./scripts/cycle_cost.sh 0x48 0x6c
```