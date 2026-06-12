#include <stdint.h>

volatile uint32_t test_data = 0x12345678;

void measure_lw_cycles(void) {
    // 显式指定寄存器，强行错开，防止 GCC 乱连连看
    register uint32_t start_cycle asm("t0");
    register uint32_t end_cycle   asm("t1");
    register uint32_t dummy_target asm("t2");
    
    volatile uint32_t *ptr = &test_data;

    // ==========================================
    // 1. 测量基准开销 (Baseline Overhead)
    // ==========================================
    asm volatile (
        "rdcycle %0\n\t"
        "rdcycle %1\n\t"
        : "=r" (start_cycle), "=r" (end_cycle)
        :: "memory"
    );
    uint32_t baseline_overhead = end_cycle - start_cycle;

    // ==========================================
    // 2. 测量包含 lw 的总周期 (Experiment)
    // ==========================================
    asm volatile (
        "rdcycle %0\n\t"
        "lw %1, 0(%3)\n\t"
        "rdcycle %2\n\t"
        : "=r" (start_cycle), "=r" (dummy_target), "=r" (end_cycle)
        : "r" (ptr)
        : "memory"
    );
    uint32_t total_cycles = end_cycle - start_cycle;

    uint32_t lw_pure_cycles = total_cycles - baseline_overhead;
}
