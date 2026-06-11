# Standalone SERV firmware build — no Zephyr, no FuseSoC
# Usage:
#   make                          # builds popcount_SERV_return.hex
#   make run                      # builds + runs on Verilator
#   make FIRMWARE=other.c run     # build a different .c file

# ── Toolchain (matches your workspace) ──────────────────────
CROSS     ?= /home/chenyoo/riscv_benchmark/tools/riscv/bin/riscv32-unknown-elf
CC         = $(CROSS)-gcc
OBJCOPY    = $(CROSS)-objcopy
OBJDUMP    = $(CROSS)-objdump
SIZE       = $(CROSS)-size

# ── SERV is pure RV32I (no M, no C) ────────────────────────
ARCH       = rv32i
ABI        = ilp32
CFLAGS     = -march=$(ARCH) -mabi=$(ABI) -Os -Wall \
             -static -mcmodel=medany -fvisibility=hidden \
             -nostdlib -nostartfiles -ffreestanding

# ── Sources ─────────────────────────────────────────────────
STARTUP    = startup.S
FIRMWARE  ?= ../../Codespace/SERV_codespace/popcount_SERV_return.c
LDSCRIPT   = serv.ld

# ── Output names ────────────────────────────────────────────
BASENAME   = popcount_SERV_return
ELF        = $(BASENAME).elf
BIN        = $(BASENAME).bin
HEX        = $(BASENAME).hex

# ── Verilator simulation binary (already built by FuseSoC) ─
VSIM       = ../build/award-winning_serv_servant_1.4.0/verilator_tb/Vservant_sim
BAUD       = 57600

# ═══════════════════════════════════════════════════════════
.PHONY: all clean run disasm

all: $(HEX)

# 1. Compile startup.S — put _start in .text.start so it lands at address 0
startup.o: $(STARTUP)
	$(CC) $(CFLAGS) -c -o $@ $<

# 2. Compile C firmware
firmware.o: $(FIRMWARE)
	$(CC) $(CFLAGS) -c -o $@ $<

# 3. Link
$(ELF): startup.o firmware.o $(LDSCRIPT)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) -o $@ startup.o firmware.o
	$(SIZE) $@

# 4. ELF → raw binary
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# 5. raw binary → hex (one 32-bit word per line, for $readmemh)
$(HEX): $(BIN) bin2hex.py
	python3 bin2hex.py $< $@
	@echo "✓ $(HEX) ready  ($$(( $(shell wc -c < $(BIN)) / 4 )) words)"

# Disassembly for debugging
disasm: $(ELF)
	$(OBJDUMP) -d -M no-aliases $<

# Run on Verilator
run: $(HEX)
	$(VSIM) +firmware=$(abspath $(HEX)) +uart_baudrate=$(BAUD)

clean:
	rm -f startup.o firmware.o $(ELF) $(BIN) $(HEX) trace.vcd
