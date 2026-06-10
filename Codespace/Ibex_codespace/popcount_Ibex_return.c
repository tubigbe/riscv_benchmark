#include <stdint.h>

#define IBEX_SIM_PRINT_ADDR 0x00020000u
#define IBEX_SIM_HALT_ADDR  0x00020008u

volatile uint32_t popcount_sink;

static void ibex_putchar(char c)
{
    volatile uint32_t *print_reg = (volatile uint32_t *)IBEX_SIM_PRINT_ADDR;
    *print_reg = (uint32_t)c;
}

static void ibex_puts(const char *s)
{
    while (*s) {
        ibex_putchar(*s);
        s++;
    }
}

static void ibex_halt(void)
{
    volatile uint32_t *halt_reg = (volatile uint32_t *)IBEX_SIM_HALT_ADDR;
    *halt_reg = 1u;

    while (1) {
    }
}

__attribute__((noinline, used)) uint32_t popcount(uint32_t in_reg){
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

    return count1;
}

int main(void)
{
    uint32_t reg_x1 = 19149u;

    popcount_sink = popcount(reg_x1);

    ibex_puts("Done.\n");

    ibex_halt();

    return 0;
}
