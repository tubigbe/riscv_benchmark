# =================================================================
# Auto-capture disassembly PC addresses
# =================================================================
ELF_FILE="~/riscv_benchmark/serv_project/firmware.elf"
OBJDUMP=riscv64-unknown-elf-objdump
TRACE_BIN="~/riscv_benchmark/serv_project/build/award-winning_serv_servant_1.4.0/verilator_tb/trace.bin"

# Auto-extract main's start address (first instruction after <main> label)
START_PC=$( $OBJDUMP -d $ELF_FILE | awk '/<main>:/ {getline; print $1}' | tr -d ':' )

# Auto-extract main's end address (first ret after <main>)
STOP_PC=$( $OBJDUMP -d $ELF_FILE | awk '/<main>:/, /ret/ {if($0 ~ /ret/) print $1}' | head -n 1 | tr -d ':' )

echo "============================================"
echo "  Start PC (main):  0x${START_PC}"
echo "  Stop  PC (ret):   0x${STOP_PC}"
echo "============================================"

# =================================================================
# Parse binary trace.bin and count cycles between start/stop PCs
# trace.bin = raw 32-bit integers, one PC per clock cycle
# =================================================================
python3 -c "
import struct, sys

start = 0x${START_PC}
stop  = 0x${STOP_PC}

with open('${TRACE_BIN}', 'rb') as f:
    data = f.read()

pcs = struct.unpack(f'<{len(data)//4}I', data)

# Find first occurrence of start PC
try:
    start_idx = next(i for i, pc in enumerate(pcs) if pc == start)
except StopIteration:
    print(f'ERROR: Start PC 0x{start:08x} not found in trace')
    sys.exit(1)

# Find first occurrence of stop PC AFTER start
try:
    stop_idx = next(i for i, pc in enumerate(pcs) if i > start_idx and pc == stop)
except StopIteration:
    print(f'ERROR: Stop PC 0x{stop:08x} not found after start')
    sys.exit(1)

cycles = stop_idx - start_idx
print(f'  main() cycle cost: {cycles} cycles')
print(f'  (from trace index {start_idx} to {stop_idx})')
"
