#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════════════
#  Reproduce the memory-range popcount custom-instruction test
#
#  Tests popcount rd, rs1(start), rs2(end) over a 10-word array and
#  verifies the custom-instruction result equals the software popcount.
#
#  Usage: ./reproduce_range_popcount.sh
#
#  Result: "==> PASS" if a6 == a1 (custom == software), else FAIL.
# ═══════════════════════════════════════════════════════════════════════
set -euo pipefail
cd "$(dirname "$0")"

echo "════════════════════════════════════════════════"
echo "  Range Popcount Reproduction"
echo "════════════════════════════════════════════════"

# [1/3] Build firmware
echo ""
echo "[1/3] Building firmware..."
./build.sh --folder=range_popcount_test --build > /tmp/rep_build.log 2>&1
echo "  firmware.hex generated ($(wc -l < firmware.hex) words)"

# [2/3] Run fusesoc simulation (rebuilds Verilator model on first run)
echo ""
echo "[2/3] Running fusesoc simulation..."
SIM_TIMEOUT=120 timeout 250 ./build.sh --run > /tmp/rep_sim.log 2>&1 || {
    echo "  [ERROR] simulation failed — see /tmp/rep_sim.log"
    exit 1
}
grep -q "Test complete" /tmp/rep_sim.log && echo "  Simulation completed" || echo "  [WARN] no 'Test complete'"

# [3/3] Verify PASS/FAIL from the PC trace
echo ""
echo "[3/3] Verifying result from PC trace..."
python3 << 'PYEOF'
data = open('build/award-winning_serv_servant_1.4.0/verilator_tb/trace.bin','rb').read()
import struct
pcs = [struct.unpack('<I', data[i:i+4])[0] for i in range(0, len(data), 4)]
seen = []
for p in pcs:
    if not seen or seen[-1] != p:
        seen.append(p)
tail = " -> ".join(hex(p) for p in seen[-15:])
print(f"  PC tail: {tail}")
if 0x88 in seen:
    print("")
    print("  ════════════════════════════════════════")
    print("  ==> PASS (custom result == software result)")
    print("  ════════════════════════════════════════")
else:
    print("  ==> FAIL")
PYEOF
