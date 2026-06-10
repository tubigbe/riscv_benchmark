#include <stdint.h>

#define OUT  0x00020000u
#define HALT 0x00020008u

static void putc_i(char c)
{
    *(volatile uint32_t *)OUT = (uint32_t)c;
}

static void puts_i(const char *s)
{
    while (*s) {
        putc_i(*s++);
    }
}

static void halt_i(void)
{
    *(volatile uint32_t *)HALT = 1u;
    while (1) {}
}

static void put_small(uint32_t x)
{
    if (x >= 30u) {
        putc_i('3');
        putc_i((char)('0' + x - 30u));
    } else if (x >= 20u) {
        putc_i('2');
        putc_i((char)('0' + x - 20u));
    } else if (x >= 10u) {
        putc_i('1');
        putc_i((char)('0' + x - 10u));
    } else {
        putc_i((char)('0' + x));
    }
}

static __attribute__((noinline)) uint32_t popcount32(uint32_t x)
{
    uint32_t c = 0u;

    for (uint32_t i = 0u; i < 32u; i++) {
        c += x & 1u;
        x >>= 1;
    }

    return c;
}

static void run_test(const char *name, uint32_t x)
{
    uint32_t r = popcount32(x);

    puts_i(name);
    puts_i(" = ");
    put_small(r);
    puts_i("\n");
}

int main(void)
{
    puts_i("Simple popcount on Ibex\n");

    run_test("zero", 0x00000000u);
    run_test("one", 0x00000001u);
    run_test("all_ones", 0xFFFFFFFFu);
    run_test("deadbeef", 0xDEADBEEFu);
    run_test("baadf00d", 0xBAADF00Du);
    run_test("single_msb", 0x80000000u);

    puts_i("Done.\n");

    halt_i();
    return 0;
}
