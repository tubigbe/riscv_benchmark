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

volatile static unsigned int popcnt_custom(unsigned int val) {
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
}

int main(void){
    uint32_t reg_x1 = 0x0fffffff;

    popcount_sink = popcnt_custom(reg_x1);

    putstr("popcount_sink = 0x");
    puthex(popcount_sink);
    putstr("\n");

    *(volatile unsigned int *)0x90000000 = 0;
    return popcount_sink;
}
