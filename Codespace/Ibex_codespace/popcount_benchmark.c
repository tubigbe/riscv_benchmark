#include <stdint.h>

#define IBEX_SIM_HALT_ADDR 0x00020008u

void popcount(uint32_t in_reg){
    uint32_t count0 = 0;
    uint32_t count1 = 0;

    for(int i = 0; i < 32; i++){
        uint32_t temp = in_reg >> i;
        temp = temp & 1;
        if(temp == 1) {
            count1 = count1 + 1;
        } else {
            count0 = count0 + 1;
        }
    }
}

#ifndef ITERATIONS
#define ITERATIONS 1000u
#endif

static void ibex_halt(void)
{
    volatile uint32_t *halt_reg = (volatile uint32_t *)IBEX_SIM_HALT_ADDR;
    *halt_reg = 1u;

    while (1) {
    }
}

int main(void)
{
    uint32_t x = 0xDEADBEEFu;

    for (uint32_t i = 0u; i < ITERATIONS; i++) {
        popcount(x);
        x = x + 0x9E3779B9u;
    }

    ibex_halt();

    return 0;
}
