# SERV RISC-V Benchmark Toolchain

Build, simulate, and analyze firmware for the [SERV](https://github.com/olofk/serv) RISC-V CPU using Verilator.

This repository contains everything needed to compile bare-metal RV32I firmware, run it on a simulated SERV processor, and analyze cycle-level performance from instruction traces.

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

### Step 5 — Analyze results

```bash
./cycle_counter.sh                        # cycles for main()
./address_capture.sh                      # display main() PC addresses
./instr_counter.sh main                   # instruction histogram for main()
python3 bin_read.py                       # raw trace.bin viewer
python3 trace_dump.py                     # full trace with symbol names
```

### Step 6 — Cycle cost per instruction

A four-step pipeline that tells you exactly how many cycles each instruction costs on SERV:

```bash
# Step 1 already done (build.sh --build --run produces trace.bin)

# Step 2: Run Verilator simulation → log/sim_log.txt
./run_sim.sh

# Step 3: Decode trace.bin → log/trace_dump.txt
python3 trace_dump.py

# Step 4: Merge logs → log/compare_result.txt
python3 compare_traces.py
```

Output (`log/compare_result.txt`):
```
#         PC     Next PC  Instr     Cycles
  0x00000000  0x00000004  lui           36
  0x00000004  0x00000008  lui           36
  0x0000000c  0x00000010  sb            70
  ...

# ── Summary ──────────────────────────────
# Instructions : 20987
# Total cycles : 1355310
# Avg cycles   : 64.6
# Min cycles   : 36
# Max cycles   : 99

# ── Average cycle cost per instruction ──
# Instr     Count      Avg    Min    Max
  bnez       1544     68.0     68     68
  nop        2600     36.0     36     36
  sb         1345     68.9     36     70
  srli       1424     69.0     69     69
  ...
```

**Pipeline overview:**

| Step | Script | Reads | Produces |
|------|--------|-------|----------|
| 1 | `build.sh` | C/ASM sources | `firmware.hex`, `trace.bin` |
| 2 | `run_sim.sh` | `firmware.hex` | `log/sim_log.txt` |
| 3 | `trace_dump.py` | `trace.bin` | `log/trace_dump.txt` |
| 4 | `compare_traces.py` | `log/sim_log.txt` + `log/trace_dump.txt` | `log/compare_result.txt` |

---

## Prerequisites

The project bundles local toolchains under `tools/`. After cloning and running `./setup.sh`, you should have:

| Tool | Purpose | Bundled? |
|------|---------|----------|
| `riscv64-unknown-elf-gcc` | RV32I bare-metal compiler | Yes (`tools/riscv64/`) |
| `make` | Build system | Yes (`tools/make/`) |
| `fusesoc` | FPGA/ASIC package manager | Yes (`tools/fusesoc-venv/`) |
| `verilator` | Verilog simulator | Yes (`tools/verilator/`) |
| `python3` | Scripting | System |

**System requirements:** Linux (Ubuntu 22.04+ recommended), `git`, `python3`.

---

## Project Structure

```
riscv_benchmark/
├── setup.sh                          # one-time setup (run this first!)
├── readme.markdown                   # this file
├── .gitmodules                       # submodule definitions
│
├── Codespace/
│   ├── env.sh                        # environment setup (auto-loaded)
│   └── SERV_codespace/
│       ├── startup.S                 # boot code (_start, UART, halt)
│       ├── factorial.c               # example: factorial via soft_mul
│       ├── popcount.c                # example: popcount
│       └── standalone_hello.S        # example: self-contained ASM
│
├── serv_project/
│   ├── build.sh                      # build firmware & run simulation
│   ├── run_sim.sh                    # Verilator cycle-cost simulation
│   ├── sim_main.cpp                  # custom Verilator testbench
│   ├── compare_traces.py             # merge logs → per-instruction report
│   ├── cycle_counter.sh              # cycle counting for main()
│   ├── address_capture.sh            # display function PC addresses
│   ├── instr_counter.sh              # instruction histogram
│   ├── bin_read.py                   # trace.bin hex viewer
│   ├── trace_dump.py                 # full trace with symbol resolution
│   ├── bnez_counter.sh               # instruction address lookup
│   ├── firmware.elf                  # compiled ELF (generated)
│   ├── firmware.hex                  # hex for $readmemh (generated)
│   ├── log/                          # all generated log files
│   │   ├── sim_log.txt               #   per-instruction cycle log
│   │   ├── trace_dump.txt            #   PC → instruction mapping
│   │   └── compare_result.txt        #   final merged report
│   └── fusesoc_libraries/            # git submodules
│       ├── serv/                     #   SERV CPU core
│       ├── mdu/                      #   Multiply/Divide Unit
│       └── fusesoc_cores/            #   FuseSoC standard library
│
└── tools/                            # local toolchains (git-ignored)
    ├── riscv64/                      #   RISC-V GCC cross-compiler
    ├── make/                         #   GNU Make
    ├── fusesoc-venv/                 #   FuseSoC in Python venv
    ├── verilator/                    #   Verilator simulator
    └── gcc-host/                     #   Host GCC (for Verilator C++ build)
```

---

## Tool Reference

### `build.sh` — Build & simulate

Compiles C/ASM sources into SERV firmware and runs Verilator simulation.

| Flag | Action |
|------|--------|
| `--build` | Compile SOURCES → `firmware.elf` → `.bin` → `.hex` |
| `--run` | Run simulation, generate `trace.bin` (PC trace) |
| `--build --run` | Both |
| `--clean` | Remove all build artifacts |

Edit the `SOURCES` array at the top of `build.sh` to point to your `.c` / `.S` files. Supported extensions: `.c .cc .cpp .S .s .asm`. Duplicates are auto-skipped.

**RV32I constraint:** No hardware multiply/divide. Avoid `*`, `/`, `%` in C (the compiler emits `__mulsi3`/`__udivsi3` which won't link with `-nostdlib`). Use shift-and-add instead.

### `cycle_counter.sh` — Cycle count for main()

Extracts `main()` start/stop PCs from `firmware.elf`, then counts cycles between them in `trace.bin`.

```bash
./cycle_counter.sh                              # defaults
./cycle_counter.sh path/to/firmware.elf path/to/trace.bin
```

Output:
```
Start PC (main):  0x164
Stop  PC (ret):   0x25c
main() cycle cost: 20980 cycles
```

### `address_capture.sh` — Display function PC addresses

Shows the start and stop PC of any function in the ELF.

```bash
./address_capture.sh                            # default: main
./address_capture.sh firmware.elf asm_uart_putchar
```

### `instr_counter.sh` — Instruction histogram

Prints static instruction counts for a given function.

```bash
./instr_counter.sh                              # default: _start
./instr_counter.sh main                         # target: main()
./instr_counter.sh asm_uart_putchar             # target: asm_uart_putchar
```

### `bin_read.py` — Raw trace viewer

Dumps `trace.bin` as hex + decimal for inspection.

```bash
python3 bin_read.py                             # default: first 50 words
python3 bin_read.py path/to/trace.bin 100       # custom file + word count
```

### `trace_dump.py` — Full trace with symbols

Converts `trace.bin` into a human-readable text file with symbol resolution via `objdump`. Writes to `log/trace_dump.txt`.

```bash
python3 trace_dump.py                           # auto-detect paths
python3 trace_dump.py trace.bin firmware.elf output.txt
```

### `run_sim.sh` — Cycle-cost Verilator simulation

Builds and runs the custom Verilator testbench (`sim_main.cpp`), logging every PC transition with its cycle cost to `log/sim_log.txt`.

| Flag | Action |
|------|--------|
| *(no args)* | Clean + build + run |
| `--build` | Build only |
| `--run` | Run only |
| `--clean` | Remove build artifacts |
| `--firmware=FILE` | Use a different firmware hex |

### `compare_traces.py` — Cycle cost per instruction report

Merges `log/sim_log.txt` (cycle costs) with `log/trace_dump.txt` (instruction names) and produces `log/compare_result.txt` with per-instruction cycle costs and a per-instruction-type average summary.

```bash
python3 compare_traces.py
```

### `bnez_counter.sh` — Instruction address lookup

Finds the PC address of a specific instruction inside a function.

```bash
./bnez_counter.sh bnez asm_uart_putchar         # find 'bnez' in asm_uart_putchar
./bnez_counter.sh jal main                      # find 'jal' in main
```

---

## Troubleshooting

### `command not found: riscv64-unknown-elf-gcc`

The environment isn't loaded. Run:

```bash
source ~/riscv_benchmark/Codespace/env.sh
```

Or open a **new terminal** — the environment auto-loads when inside `~/riscv_benchmark/`.

### `command not found: make` or `command not found: verilator`

The local tools aren't on your PATH. Either:

1. Open a new terminal (auto-load should pick them up), or
2. Run `source ~/riscv_benchmark/Codespace/env.sh`

### Submodule directories are empty

Run the setup script to fetch them:

```bash
cd ~/riscv_benchmark
./setup.sh
```

### `fatal error: cstdint: No such file or directory`

The C++ standard library headers are missing. This is needed for Verilator's C++ testbench compilation. Install them:

```bash
sudo apt install g++ libstdc++-15-dev
```

### `Permission denied` when running scripts

Make the scripts executable:

```bash
chmod +x *.sh *.py
```

### Simulation hangs or times out

The default timeout is 300 seconds. For longer simulations:

```bash
SIM_TIMEOUT=600 ./build.sh --run
```

### Build fails with `__mulsi3` / `__udivsi3` undefined

Your C code uses `*`, `/`, or `%`. SERV has no hardware multiply/divide. Replace with shift-and-add operations.

---

## Git Workflow

```bash
# Create a feature branch
git checkout -b my-feature

# Make changes, then commit
git add -A
git commit -m "description of changes"

# Push to your branch
git push origin my-feature

# Create a Pull Request on GitHub
```

**Important:** Always pull the latest changes before starting work:

```bash
git pull origin main
./setup.sh
```

