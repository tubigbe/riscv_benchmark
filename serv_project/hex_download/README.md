# HEX Files for Dynamic Power Testing (Vivado / Windows)

Both hex files were compiled under the **latest RTL (e81a9cf)** — the hex is
RTL-independent (it is the compiled firmware / machine code).

For dynamic power testing, load each hex into the RAM of the corresponding
synthesized design:

| File | Corresponds to | RTL to synthesize | Firmware |
|------|----------------|-------------------|----------|
| `popcount_sw_bench.hex` | Original software popcount (no custom instruction) | baseline SERV (no custom logic) | software 32-bit loop, 5 words |
| `popcount_v2_bench.hex` | Latest memory-range popcount custom instruction | `e81a9cf` (with range popcount) | one range `popcount rd, rs1, rs2`, 5 words |

Both compute the same workload: total popcount of
`{0x00000000, 0xFFFFFFFF, 0xDEADBEEF, 0x55555555, 0xAAAAAAAA}` = 88 = 0x58.

- `popcount_sw_bench.hex`: contains **0** custom instructions.
- `popcount_v2_bench.hex`: contains **1** custom instruction (`0x00E787AB`,
  `popcount a5, a5(start), a4(end)`), which occupies ~250 of the ~464 cycles.

Verification: each writes the result low byte (0x58) to `0x80000000`, then
writes to `0x90000000` (halt).
