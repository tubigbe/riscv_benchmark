// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim_servant_ram__D8000_R4d494e49.h"

VL_ATTR_COLD void Vservant_sim_servant_ram__D8000_R4d494e49___ctor_var_reset(Vservant_sim_servant_ram__D8000_R4d494e49* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vservant_sim_servant_ram__D8000_R4d494e49___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__i_wb_clk = VL_RAND_RESET_I(1);
    vlSelf->__PVT__i_wb_rst = VL_RAND_RESET_I(1);
    vlSelf->__PVT__i_wb_adr = VL_RAND_RESET_I(13);
    vlSelf->__PVT__i_wb_dat = VL_RAND_RESET_I(32);
    vlSelf->__PVT__i_wb_sel = VL_RAND_RESET_I(4);
    vlSelf->__PVT__i_wb_we = VL_RAND_RESET_I(1);
    vlSelf->__PVT__i_wb_cyc = VL_RAND_RESET_I(1);
    vlSelf->__PVT__o_wb_rdt = VL_RAND_RESET_I(32);
    vlSelf->__PVT__o_wb_ack = VL_RAND_RESET_I(1);
    vlSelf->__PVT__we = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 8192; ++__Vi0) {
        vlSelf->mem[__Vi0] = VL_RAND_RESET_I(32);
    }
}
