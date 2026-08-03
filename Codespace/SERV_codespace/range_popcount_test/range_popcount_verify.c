/*
 * range_popcount_verify.c
 *
 * Test for the custom memory-range popcount instruction:
 *     popcount rd, rs1(start_addr), rs2(end_addr)
 *
 * A 10-word data array is placed in RAM. The start and end addresses of the
 * array are passed to the custom instruction (via .insn inline assembly) and
 * the result is compared against a software popcount over the same range.
 *
 * Expected popcount of the 10 words:
 *   0x00000000(0) 0xFFFFFFFF(32) 0xDEADBEEF(24) 0x55555555(16)
 *   0xAAAAAAAA(16) 0x0F0F0F0F(16) 0xF0F0F0F0(16) 0x12345678(13)
 *   0x89ABCDEF(20) 0x00000001(1)  =>  total 154 = 0x9A
 *
 * Build: ./build.sh --folder=range_popcount_test --build --run
 */

extern void asm_uart_putchar(unsigned char ch);

static void print_str(const char *s) {
    while (*s) asm_uart_putchar((unsigned char)*s++);
}

static void print_hex(unsigned int val) {
    for (int i = 7; i >= 0; i--) {
        unsigned int nibble = (val >> (i * 4)) & 0xF;
        if (nibble < 10)
            asm_uart_putchar('0' + nibble);
        else
            asm_uart_putchar('a' + nibble - 10);
    }
}

/* Division-free decimal printer (RV32I has no hardware divide) */
static void print_uint(unsigned int val) {
    char buf[12];
    int pos = 11;
    buf[11] = '\0';
    do {
        unsigned int r = val;
        unsigned int q = 0;
        while (r >= 10) { r -= 10; q++; }
        buf[--pos] = '0' + r;
        val = q;
    } while (val);
    print_str(&buf[pos]);
}

/*
 * Custom instruction: popcount rd, rs1(start_addr), rs2(end_addr)
 *   opcode = 0x2B (custom-0), funct3 = 000, funct7 = 000
 *   Encoding: funct7=0000000 rs2 rs1 funct3=000 rd 0101011
 */
static unsigned int popcnt_range_custom(unsigned int start, unsigned int end) {
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, %2"
                 : "=r"(rd) : "r"(start), "r"(end));
    return rd;
}

/*
 * Software popcount over memory range [start, end] (inclusive, word-granular).
 * Uses only standard RV32I instructions.
 */
static unsigned int popcnt_range_sw(unsigned int start, unsigned int end) {
    unsigned int count = 0;
    unsigned int addr = start;
    while (addr <= end) {
        unsigned int word = *(volatile unsigned int *)addr;
        for (int i = 0; i < 32; i++) {
            if ((word >> i) & 1)
                count++;
        }
        addr += 4;
    }
    return count;
}

/* 10 test words (word-aligned by the compiler) */
static unsigned int test_data[10] = {
    0x00000000,
    0xFFFFFFFF,
    0xDEADBEEF,
    0x55555555,
    0xAAAAAAAA,
    0x0F0F0F0F,
    0xF0F0F0F0,
    0x12345678,
    0x89ABCDEF,
    0x00000001
};

int main(void) {
    unsigned int start = (unsigned int)&test_data[0];
    unsigned int end   = (unsigned int)&test_data[9];

    unsigned int custom_res = popcnt_range_custom(start, end);
    unsigned int sw_res     = popcnt_range_sw(start, end);

    /* Signature-based result (captured by fusesoc to a file):
     *   0x80000000 <- 'P' if pass, 'F' if fail
     *   0x80000004 <- custom result (low byte)
     *   0x80000008 <- sw result (low byte)
     */
    *(volatile unsigned char *)0x80000000 =
        (custom_res == sw_res) ? 'P' : 'F';
    *(volatile unsigned char *)0x80000004 = (unsigned char)custom_res;
    *(volatile unsigned char *)0x80000008 = (unsigned char)sw_res;

    *(volatile unsigned int *)0x90000000 = 0;
    return 0;
}
