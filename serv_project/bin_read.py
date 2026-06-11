#!/usr/bin/env python3
import os
import struct

def read_trace_bin(file_path, show_words=40):
    """
    读取并打印二进制 trace 文件，用于肉眼校验数据是否正确
    :param file_path: bin 文件的绝对路径
    :param show_words: 默认展示前多少个 32 位字(Word)
    """
    if not os.path.exists(file_path):
        print(f"❌ 错误：找不到文件 {file_path}")
        return

    file_size = os.path.getsize(file_path)
    print(f"📂 成功打开二进制文件: {file_path}")
    print(f"📏 文件总大小: {file_size} 字节 (约 {file_size // 4} 个 32位字)")
    print("-" * 65)
    print(f"{'文件偏移量 (Offset)':<18} | {'十六进制数据 (Hex)':<18} | {'十进制数值 (Uint32)'}")
    print("-" * 65)

    with open(file_path, 'rb') as f:
        word_idx = 0
        while word_idx < show_words:
            # 每次读取 4 个字节（32位处理器的一个标准字长）
            chunk = f.read(4)
            
            if not chunk:
                print("🏁 已经到达文件末尾 (EOF)")
                break
                
            if len(chunk) < 4:
                print(f"⚠️ 读到文件末尾，剩余未对齐的残余字节: 0x{chunk.hex()}")
                break

            # '<I' 代表使用小端序（Little-Endian）解析为 32 位无符号整数
            # 如果你发现解析出来的 PC 顺序反了，可以改成 '>I'（大端序）对比看看
            val = struct.unpack('<I', chunk)[0]
            offset = word_idx * 4

            # 打印展示
            print(f"0x{offset:06x} (Byte {offset:<4}) | 0x{val:08x}         | {val}")
            word_idx += 1

if __name__ == "__main__":
    # 指向你的二进制 trace 文件路径
    TARGET_BIN = "/home/chenyoo/riscv_benchmark/serv_project/build/award-winning_serv_servant_1.4.0/verilator_tb/trace.bin"
    
    # 默认查看前 50 组数据
    read_trace_bin(TARGET_BIN, show_words=50)