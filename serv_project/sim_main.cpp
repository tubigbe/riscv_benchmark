/*
 * sim_main.cpp — Verilator testbench for SERV (servant_sim top module)
 *
 * Monitors PC address changes during simulation and reports the cycle cost
 * for every 4 consecutive PC steps. Uses the full servant_sim SoC which
 * includes the SERV CPU core, RAM, timer, GPIO, and bus mux.
 *
 * Build & run:  ./run_sim.sh
 */

#include <iostream>
#include <memory>
#include <cstdint>

#include "Vservant_sim.h"  // Auto-generated header by Verilator for servant_sim
#include "verilated.h"

// Required by Verilator when $time is referenced in Verilog
double sc_time_stamp() { return 0; }

int main(int argc, char** argv) {
    // ── Initialise Verilator and the top-level module ────────
    Verilated::commandArgs(argc, argv);
    auto top = std::make_unique<Vservant_sim>();

    // Simulation state
    uint64_t main_time    = 0;   // Half-cycle time counter
    uint64_t current_cycle = 0;  // Rising-edge cycle counter

    // PC monitoring state
    uint32_t last_pc         = 0;
    uint32_t pc_change_count = 0;
    uint64_t start_cycle     = 0;
    bool     tracking_started = false;

    // ── Reset phase ──────────────────────────────────────────
    // servant_sim uses wb_clk / wb_rst (active-high reset)
    top->wb_clk = 0;
    top->wb_rst = 1;
    for (int i = 0; i < 20; i++) {
        top->wb_clk = !top->wb_clk;
        top->eval();
        main_time++;
    }
    top->wb_rst = 0;  // Release reset

    std::cout << "[Monitor] Reset complete. Watching for PC changes..." << std::endl;

    // Safety limit to prevent infinite simulation
    const uint64_t MAX_CYCLES = 500000;

    // ── Main simulation loop ─────────────────────────────────
    while (!Verilated::gotFinish() && current_cycle < MAX_CYCLES) {
        top->wb_clk = !top->wb_clk;  // Toggle clock
        top->eval();                  // Propagate combinational logic

        // Only sample signals on the rising clock edge
        if (top->wb_clk == 1) {
            current_cycle++;

            // pc_vld indicates that pc_adr holds a valid address this cycle
            if (top->pc_vld) {
                uint32_t current_pc = top->pc_adr;

                // Detect a PC change
                if (current_pc != last_pc) {

                    // Record the baseline on the very first change
                    if (!tracking_started) {
                        start_cycle = current_cycle;
                        tracking_started = true;
                        std::cout << "[Monitor] Tracking started, initial address: 0x"
                                  << std::hex << current_pc << std::dec << std::endl;
                    }

                    pc_change_count++;
                    std::cout << "[Monitor] PC change #" << pc_change_count
                              << " -> new address: 0x" << std::hex << current_pc
                              << " (cycle: " << std::dec << current_cycle << ")" << std::endl;

                    // Report after every 4 PC changes
                    if (pc_change_count == 4) {
                        uint64_t delta_cycles = current_cycle - start_cycle;
                        std::cout << "=========================================" << std::endl;
                        std::cout << "[Result] 4 PC changes took " << delta_cycles << " cycles" << std::endl;
                        std::cout << "=========================================" << std::endl;

                        // Reset counters for the next window
                        pc_change_count = 0;
                        start_cycle = current_cycle;
                    }

                    last_pc = current_pc;
                }
            }
        }

        main_time++;
    }

    // ── Simulation end ───────────────────────────────────────
    if (current_cycle >= MAX_CYCLES) {
        std::cout << "[Monitor] Reached max cycles (" << MAX_CYCLES << "). Exiting." << std::endl;
    }

    top->final();
    return 0;
}