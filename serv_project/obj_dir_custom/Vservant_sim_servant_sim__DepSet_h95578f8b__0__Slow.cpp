// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim_servant_sim.h"

VL_ATTR_COLD void Vservant_sim_servant_sim___ctor_var_reset(Vservant_sim_servant_sim* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vservant_sim_servant_sim___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->wb_clk = VL_RAND_RESET_I(1);
    vlSelf->wb_rst = VL_RAND_RESET_I(1);
    vlSelf->pc_adr = VL_RAND_RESET_I(32);
    vlSelf->pc_vld = VL_RAND_RESET_I(1);
    vlSelf->q = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(1024, vlSelf->__PVT__firmware_file);
}
