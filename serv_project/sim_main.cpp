#include <iostream>
#include <memory>
#include <cstdint>
#include "Vservant_sim.h"  // Verilator 编译 servant_sim 自动生成的头文件
#include "verilated.h"

// Called by $time in Verilog
double sc_time_stamp() { return 0; }

int main(int argc, char** argv) {
    // 初始化 Verilator
    Verilated::commandArgs(argc, argv);
    auto top = std::make_unique<Vservant_sim>();

    // 仿真状态变量
    uint64_t main_time = 0;       // 半周期计数器
    uint64_t current_cycle = 0;    // 真正的时钟周期计数器
    
    // 核心监控变量
    uint32_t last_pc = 0;
    uint32_t pc_change_count = 0;
    uint64_t start_cycle = 0;
    bool tracking_started = false;

    // 复位阶段 (servant_sim 使用 wb_clk / wb_rst，高电平复位)
    top->wb_clk = 0;
    top->wb_rst = 1;
    for (int i = 0; i < 20; i++) {
        top->wb_clk = !top->wb_clk;
        top->eval();
        main_time++;
    }
    top->wb_rst = 0; // 解除复位

    std::cout << "[Monitor] 复位完成，开始监控 PC 变化..." << std::endl;

    // 最大仿真周期 (防止无限运行)
    const uint64_t MAX_CYCLES = 500000;

    // 主仿真循环
    while (!Verilated::gotFinish() && current_cycle < MAX_CYCLES) {
        top->wb_clk = !top->wb_clk; // 翻转时钟
        top->eval();                 // 更新硬件状态

        // 只在时钟上升沿进行逻辑判断
        if (top->wb_clk == 1) {
            current_cycle++; // 周期数加 1

            // 当 pc_vld 拉高时，pc_adr 上是有效的地址
            if (top->pc_vld) {
                uint32_t current_pc = top->pc_adr;

                // 检测 PC 是否发生变化
                if (current_pc != last_pc) {
                    
                    // 第一次检测到变化，记录起始点
                    if (!tracking_started) {
                        start_cycle = current_cycle;
                        tracking_started = true;
                        std::cout << "[Monitor] 开始统计，初始地址: 0x" 
                                  << std::hex << current_pc << std::dec << std::endl;
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
                        
                        // 重置计数器，进行下一轮统计
                        pc_change_count = 0;
                        start_cycle = current_cycle;
                    }

                    last_pc = current_pc; // 更新上一轮的 PC
                }
            }
        }

        main_time++;
    }

    if (current_cycle >= MAX_CYCLES) {
        std::cout << "[Monitor] 达到最大仿真周期 (" << MAX_CYCLES << ")，退出。" << std::endl;
    }

    top->final();
    return 0;
}