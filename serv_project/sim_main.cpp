/*
 * sim_main.cpp — Verilator testbench for SERV (servant_sim top module)
 *
 * Monitors PC address changes during simulation and reports the cycle cost
 * for each instruction, i.e. for every PC transition:
 *
 *     last_pc -> current_pc : N cycles
 *
 * Uses the full servant_sim SoC which includes the SERV CPU core, RAM,
 * timer, GPIO, and bus mux.
 *
 * Build & run: ./run_sim.sh
 */

#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>
#include <iomanip>
#include <sys/stat.h>

#include "Vservant_sim.h"  // Auto-generated header by Verilator for servant_sim
#include "verilated.h"

// Required by Verilator when $time is referenced in Verilog
double sc_time_stamp() { return 0; }

int main(int argc, char** argv) {
    // ── Redirect stdout to log file ──────────────────────────
    mkdir("log", 0755);  // Ensure log/ directory exists
    const char* logfile = "log/sim_log.txt";
    std::ofstream ofs(logfile);
    if (!ofs) {
        std::cerr << "[ERROR] Cannot open log file: " << logfile << std::endl;
        return 1;
    }
    // Save original cout buffer so we can restore it before ofs is destroyed
    std::streambuf* orig_buf = std::cout.rdbuf(ofs.rdbuf());

    // ── Initialise Verilator and the top-level module ────────
    Verilated::commandArgs(argc, argv);
    auto top = std::make_unique<Vservant_sim>();

    // Simulation state
    uint64_t main_time     = 0;  // Half-cycle time counter
    uint64_t current_cycle = 0;  // Rising-edge cycle counter

    // PC monitoring state
    uint32_t last_pc       = 0;
    uint64_t start_cycle   = 0;
    bool have_last_pc      = false;

    // ── Reset phase ──────────────────────────────────────────
    // servant_sim uses wb_clk / wb_rst, active-high reset
    top->wb_clk = 0;
    top->wb_rst = 1;

    for (int i = 0; i < 20; i++) {
        top->wb_clk = !top->wb_clk;
        top->eval();
        main_time++;
    }

    top->wb_rst = 0;  // Release reset

    std::cout << "[Monitor] Reset complete. Watching for PC changes..."
              << std::endl;

    // Safety limit to prevent infinite simulation
    const uint64_t MAX_CYCLES = 10000000;

    // ── Main simulation loop ─────────────────────────────────
    while (!Verilated::gotFinish() && current_cycle < MAX_CYCLES) {
        top->wb_clk = !top->wb_clk;  // Toggle clock
        top->eval();                 // Propagate combinational logic

        // Only sample signals on the rising clock edge
        if (top->wb_clk == 1) {
            current_cycle++;

            /*
             * pc_vld indicates that pc_adr holds a valid PC address
             * in this cycle.
             */
            if (top->pc_vld) {
                uint32_t current_pc = top->pc_adr;

                /*
                 * First valid PC:
                 * Only use it as the baseline.
                 * Do not print, because there is no previous PC yet.
                 */
                if (!have_last_pc) {
                    last_pc = current_pc;
                    start_cycle = current_cycle;
                    have_last_pc = true;

                    std::cout << std::hex
                              << "[Monitor] First valid PC = 0x"
                              << last_pc
                              << std::dec
                              << " at cycle "
                              << start_cycle
                              << std::endl;
                }

                /*
                 * Subsequent PC change:
                 * The elapsed cycles from start_cycle to current_cycle
                 * correspond to the cost of executing the instruction
                 * located at last_pc.
                 */
                else if (current_pc != last_pc) {
                    uint64_t delta_cycles = current_cycle - start_cycle;

                    std::cout << std::hex
                              << "0x" << last_pc
                              << " -> 0x" << current_pc
                              << std::dec
                              << " : " << delta_cycles
                              << " cycles"
                              << std::endl;

                    // Update baseline for the next instruction
                    last_pc = current_pc;
                    start_cycle = current_cycle;
                }
            }
        }

        main_time++;
    }

    // ── Simulation end ───────────────────────────────────────
    if (current_cycle >= MAX_CYCLES) {
        std::cout << "[Monitor] Reached max cycles ("
                  << MAX_CYCLES
                  << "). Exiting."
                  << std::endl;
    }

    top->final();

    // Restore original cout buffer before ofs is destroyed
    std::cout.rdbuf(orig_buf);
    return 0;
}