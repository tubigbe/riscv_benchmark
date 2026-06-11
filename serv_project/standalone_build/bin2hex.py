#!/usr/bin/env python3
"""Convert raw binary to hex words for Verilog $readmemh."""
import sys

def bin2hex(bin_path, hex_path):
    data = open(bin_path, "rb").read()
    # pad to 4-byte boundary
    data += b"\x00" * ((4 - len(data) % 4) % 4)
    with open(hex_path, "w") as f:
        for i in range(0, len(data), 4):
            word = int.from_bytes(data[i : i + 4], "little")
            f.write(f"{word:08x}\n")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.bin> <output.hex>", file=sys.stderr)
        sys.exit(1)
    bin2hex(sys.argv[1], sys.argv[2])
