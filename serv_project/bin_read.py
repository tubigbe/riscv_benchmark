#!/usr/bin/env python3
# =================================================================
# Binary trace file viewer for SERV simulation output.
# Reads trace.bin (raw 32-bit PC values) and prints hex + decimal.
# Usage: ./bin_read.py [path_to_trace.bin] [num_words]
# =================================================================
import os
import struct

def read_trace_bin(file_path, show_words=40):
    """
    Read and print a binary trace file for visual inspection.
    :param file_path: absolute path to the .bin file
    :param show_words: how many 32-bit words to display (default 40)
    """
    if not os.path.exists(file_path):
        print(f"[ERROR] File not found: {file_path}")
        return

    file_size = os.path.getsize(file_path)
    print(f"[OK] Opened: {file_path}")
    print(f"[OK] Size: {file_size} bytes ({file_size // 4} 32-bit words)")
    print("-" * 65)
    print(f"{'Offset':<18} | {'Hex':<18} | {'Uint32'}")
    print("-" * 65)

    with open(file_path, 'rb') as f:
        word_idx = 0
        while word_idx < show_words:
            # Read 4 bytes (one 32-bit word from RV32I)
            chunk = f.read(4)

            if not chunk:
                print("[EOF] End of file reached")
                break

            if len(chunk) < 4:
                print(f"[WARN] Trailing bytes (not aligned): 0x{chunk.hex()}")
                break

            # Little-endian 32-bit unsigned int
            val = struct.unpack('<I', chunk)[0]
            offset = word_idx * 4

            print(f"0x{offset:06x} (Byte {offset:<4}) | 0x{val:08x}         | {val}")
            word_idx += 1

if __name__ == "__main__":
    TARGET_BIN = "/home/chenyoo/riscv_benchmark/serv_project/build/award-winning_serv_servant_1.4.0/verilator_tb/trace.bin"

    read_trace_bin(TARGET_BIN, show_words=50)