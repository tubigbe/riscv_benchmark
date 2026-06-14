# SERV RISC-V Benchmark Toolchain

Build, simulate, and analyze firmware for the [SERV](https://github.com/olofk/serv) RISC-V CPU on Verilator.

## Quick Start

```bash
cd ~/riscv_benchmark/serv_project

# 1. Edit SOURCES in build.sh, then:
./build.sh --build --run

# 2. Analyze:
./address_capture.sh    # cycle count for main()
./instr_counter.sh      # static instruction breakdown
./bin_read.py           # raw trace.bin viewer
```

## Cycle Cost Per Instruction Workflow

A four-step pipeline that tells you exactly how many cycles each instruction costs on SERV.

```bash
cd ~/riscv_benchmark/serv_project

# Step 1: Build firmware and run Verilator simulation
#         Produces: firmware.hex, firmware.elf, trace.bin
./build.sh --build --run

# Step 2: Run SERV simulation and log per-instruction cycle cost
#         Produces: sim_log.txt   (one line per PC transition + cycle count)
./run_sim.sh

# Step 3: Decode the PC trace into instruction mnemonics
#         Produces: trace_dump.txt  (address → instruction name)
./trace_dump.py

# Step 4: Merge the two logs into a final report
#         Produces: compare_result.txt  (per-instruction cost + summary)
python3 compare_traces.py
```

**Output (`compare_result.txt`):**

```
#         PC     Next PC  Instr     Cycles
  0x00000000  0x00000004  lui           36
  0x00000004  0x00000008  lui           36
  0x0000000c  0x00000010  sb            70
  ...

# ── Summary ──────────────────────────────
# Instructions : 113
# Total cycles : 6146
# Avg cycles   : 54.4
# Min cycles   : 36
# Max cycles   : 70

# ── Average cycle cost per instruction ──
# Instr     Count      Avg    Min    Max
  bnez         20     68.0     68     68
  nop          40     36.0     36     36
  sb           21     70.0     70     70
  srli         20     69.0     69     69
  ...
```

### Pipeline overview

| Step | Script | Reads | Produces | Purpose |
|------|--------|-------|----------|---------|
| 1 | `build.sh` | C/ASM sources | `firmware.hex`, `trace.bin` | Compile & simulate |
| 2 | `run_sim.sh` | `firmware.hex` | `sim_log.txt` | Per-instruction cycle count |
| 3 | `trace_dump.py` | `trace.bin` | `trace_dump.txt` | PC → instruction mnemonic |
| 4 | `compare_traces.py` | `sim_log.txt` + `trace_dump.txt` | `compare_result.txt` | Final merged report |

## Files

### `build.sh` — Build & simulate

Compiles C/ASM sources into SERV firmware and runs Verilator simulation.

| Flag | Action |
|------|--------|
| `--build` | Compile SOURCES array → `firmware.elf` → `.bin` → `.hex` |
| `--run` | Run simulation, generate `trace.bin` (PC trace) |
| `--build --run` | Both |
| `--clean` | Remove all build artifacts |

Edit the `SOURCES` array at the top to point to your `.c` / `.S` files. Supported: `.c .cc .cpp .S .s .asm`. Duplicates are auto-skipped.

**RV32I constraint:** No hardware multiply/divide. Avoid `*`, `/`, `%` in C (compiler emits `__mulsi3`/`__udivsi3` which won't link with `-nostdlib`). Use shift-and-add instead.

### `run_sim.sh` — Cycle-cost simulation

Builds and runs the Verilator simulation, logging every PC transition with its cycle cost to `sim_log.txt`.

| Flag | Action |
|------|--------|
| *(no args)* | Clean + build + run |
| `--build` | Build only |
| `--run` | Run only |
| `--clean` | Remove build artifacts |
| `--firmware=FILE` | Use a different firmware hex |

### `trace_dump.py` — PC trace decoder

Reads `trace.bin` and decodes each PC address into its RISC-V instruction mnemonic. Writes `trace_dump.txt`.

```bash
./trace_dump.py
```

### `compare_traces.py` — Final report generator

Merges `sim_log.txt` (cycle costs) with `trace_dump.txt` (instruction names) and produces `compare_result.txt` with per-instruction cycle costs and a per-instruction-type average summary.

```bash
python3 compare_traces.py
```

### `address_capture.sh` — Cycle counter

Extracts `main()` start/stop PCs from `firmware.elf`, then counts cycles between them in `trace.bin`.

```
Start PC (main):  0x48
Stop  PC (ret):   0x6c
main() cycle cost: 178 cycles
```

### `instr_counter.sh` — Instruction histogram

Prints static instruction counts from the `popcount` function in `firmware.elf`. Edit the awk pattern to target a different function name.

```
andi       : 1
srl        : 1
li         : 3
...
```

### `bin_read.py` — Binary trace viewer

Dumps `trace.bin` as hex + decimal for inspection. Usage:

```bash
python3 bin_read.py                          # default: first 50 words
python3 bin_read.py                          # or ./bin_read.py (executable)
```

## File Layout

```
serv_project/
  build.sh                  # build & simulate
  run_sim.sh                # Verilator cycle-cost simulation
  trace_dump.py             # PC trace → instruction decoder
  compare_traces.py         # merge sim_log + trace_dump → final report
  address_capture.sh        # cycle counting for main()
  instr_counter.sh          # instruction histogram
  bin_read.py               # trace.bin viewer
  firmware.elf              # compiled ELF (generated)
  firmware.hex              # hex for $readmemh (generated)
  sim_log.txt               # per-instruction cycle log (generated)
  trace_dump.txt            # PC → instruction mapping (generated)
  compare_result.txt        # final merged report (generated)
  ../Codespace/SERV_codespace/
    popcount.c              # example firmware source
    startup.S               # boot code (_start, UART, halt)
    factorial.c             # example: factorial via soft_mul
    standalone_hello.S      # example: self-contained ASM
```

## Dependencies

- `riscv64-unknown-elf-gcc` (or `riscv32-unknown-elf-gcc`)
- Python 3
- FuseSoC + Verilator (for simulation)
