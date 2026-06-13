#include <iostream>
#include <memory>
#include "Vserv_top.h"  // Verilator 编译 SERV 自动生成的头文件
#include "verilated.h"

int main(int argc, char** argv) {
    // 初始化 Verilator
    Verilated::commandArgs(argc, argv);
    auto top = std::make_unique<Vserv_top>();

    // 仿真状态变量
    uint64_t main_time = 0;       // 半周期计数器
    uint64_t current_cycle = 0;    // 真正的时钟周期计数器
    
    // 我们的核心监控变量
    uint32_t last_pc = 0;
    uint32_t pc_change_count = 0;
    uint64_t start_cycle = 0;

    // 复位阶段
    top->clk = 0;
    top->i_rst = 1; // 假设高电平复位
    for (int i = 0; i < 10; i++) {
        top->clk = !top->clk;
        top->eval();
        main_time++;
    }
    top->i_rst = 0; // 解除复位

    // 主仿真循环
    while (!Verilated::gotFinish()) {
        top->clk = !top->clk; // 翻转时钟
        top->eval();          // 更新硬件状态

        // 只在时钟上升沿进行逻辑判断
        if (top->clk == 1) {
            current_cycle++; // 周期数加 1

            // 获取当前 SERV 的指令地址
            uint32_t current_pc = top->o_ibus_adr; 

            // 检测 PC 是否发生变化
            if (current_pc != last_pc) {
                
                // 如果是第一次检测到变化，记录起始点
                if (pc_change_count == 0) {
                    start_cycle = current_cycle;
                    std::cout << "[Monitor] 开始统计，初始地址: 0x" << std::hex << current_pc << std::dec << std::endl;
                }

                pc_change_count++;
                std::cout << "[Monitor] 检测到第 " << pc_change_count 
                          << " 次地址变化 -> 新地址: 0x" << std::hex << current_pc 
                          << " (当前周期: " << std::dec << current_cycle << ")" << std::endl;

                // 当变化达到 4 次时
                if (pc_change_count == 4) {
                    uint64_t delta_cycles = current_cycle - start_cycle;
                    std::cout << "=========================================" << std::endl;
                    std::cout << "【统计结果】地址连续变化 4 次消耗的总 cycle 数: " << delta_cycles << std::endl;
                    std::cout << "=========================================" << std::endl;
                    
                    // 满足条件后，可以选择复位计数器进行下一轮统计，或者直接退出仿真
                    pc_change_count = 0; 
                    // break; // 如果只想抓一次，可以直接 break
                }

                last_pc = current_pc; // 更新上一轮的 PC
            }
        }

        main_time++;
    }

    top->final();
    return 0;
}