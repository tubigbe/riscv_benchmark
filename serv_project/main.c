#include <stdint.h>

// 声明你在 test_lw_cycles.s 里写好的函数
void measure_lw_cycles(void);

int main(void) {
    // 运行你的测试
    measure_lw_cycles();
    
    // 测试完成后，触发仿真结束
    // SERV 的 Testbench 检测到写入特定的虚拟地址，或者执行到 ebreak / 异常时会终止
    // 如果没有特定的退出机制，这里写一个死循环，供你在波形里观察
    while(1) {
        asm volatile("nop");
    }
    return 0;
}
