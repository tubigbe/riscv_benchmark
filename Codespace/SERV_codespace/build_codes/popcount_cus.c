#include <stdint.h>

volatile uint32_t popcount_sink;

volatile static unsigned int popcnt_custom(unsigned int val) {
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
}

int main(void){
    uint32_t reg_x1 = 19149;

    popcount_sink = popcnt_custom(reg_x1);

    return popcount_sink;
}