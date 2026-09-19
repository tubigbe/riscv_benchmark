#include <stdint.h>

extern void asm_uart_putchar(unsigned int c);

volatile uint32_t popcount_sink;

static void putstr(const char *s) {
    while (*s)
        asm_uart_putchar((unsigned int)*s++);
}

static void puthex(uint32_t v) {
    int i;
    for (i = 7; i >= 0; i--) {
        uint32_t nib = (v >> (i * 4)) & 0xF;
        asm_uart_putchar(nib < 10 ? ('0' + nib) : ('A' + nib - 10));
    }
}

/* Official Zbb "cpop rd, rs1".
 * GCC expands __builtin_popcount() into cpop when -march enables zbb
 * (build.sh --zbb -> -march=rv32i_zbb). The merged RTL recognises the official
 * cpop encoding and runs it on the custom popcount datapath.
 *
 * Was: asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0") -- our private custom-1
 * encoding, which the RTL no longer recognises. */
volatile static unsigned int popcnt_custom(unsigned int val) {
    return (unsigned int)__builtin_popcount(val);
}

int main(void){
    /* MUST stay volatile: with a plain literal, GCC constant-folds
     * __builtin_popcount(0x000fffff) into `li a5,20` and emits no cpop at all. */
    volatile uint32_t reg_x1 = 0x000fffff;

    popcount_sink = popcnt_custom(reg_x1);

    putstr("popcount_sink = 0x");
    puthex(popcount_sink);
    putstr("\n");

    *(volatile unsigned int *)0x90000000 = 0;
    return popcount_sink;
}
