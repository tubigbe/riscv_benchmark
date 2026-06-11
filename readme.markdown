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
  address_capture.sh        # cycle counting
  instr_counter.sh          # instruction histogram
  bin_read.py               # trace.bin viewer
  firmware.elf              # compiled ELF (generated)
  firmware.hex              # hex for $readmemh (generated)
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
