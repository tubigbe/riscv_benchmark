// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim__Syms.h"
#include "Vservant_sim___024root.h"

VL_ATTR_COLD void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___eval_static__TOP__servant_sim__dut(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);
VL_ATTR_COLD void Vservant_sim___024root____Vm_traceActivitySetAll(Vservant_sim___024root* vlSelf);

VL_ATTR_COLD void Vservant_sim___024root___eval_static(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___eval_static__TOP__servant_sim__dut((&vlSymsp->TOP__servant_sim__dut));
    Vservant_sim___024root____Vm_traceActivitySetAll(vlSelf);
}

VL_ATTR_COLD void Vservant_sim_servant_sim___eval_initial__TOP__servant_sim(Vservant_sim_servant_sim* vlSelf);
VL_ATTR_COLD void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___eval_initial__TOP__servant_sim__dut(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);

VL_ATTR_COLD void Vservant_sim___024root___eval_initial(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vservant_sim_servant_sim___eval_initial__TOP__servant_sim((&vlSymsp->TOP__servant_sim));
    Vservant_sim___024root____Vm_traceActivitySetAll(vlSelf);
    Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___eval_initial__TOP__servant_sim__dut((&vlSymsp->TOP__servant_sim__dut));
    vlSelfRef.__Vtrigprevexpr___TOP__wb_clk__0 = vlSelfRef.wb_clk;
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__stl(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vservant_sim___024root___eval_triggers__stl(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vservant_sim___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

void Vservant_sim___024root___nba_sequent__TOP__0(Vservant_sim___024root* vlSelf);
VL_ATTR_COLD void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___stl_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);
void Vservant_sim___024root___ico_sequent__TOP__0(Vservant_sim___024root* vlSelf);
void Vservant_sim_servant_ram__D2000_R4d494e49___ico_sequent__TOP__servant_sim__dut__ram__0(Vservant_sim_servant_ram__D2000_R4d494e49* vlSelf);

VL_ATTR_COLD void Vservant_sim___024root___eval_stl(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vservant_sim___024root___nba_sequent__TOP__0(vlSelf);
        Vservant_sim___024root____Vm_traceActivitySetAll(vlSelf);
        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___stl_sequent__TOP__servant_sim__dut__0((&vlSymsp->TOP__servant_sim__dut));
        Vservant_sim___024root___ico_sequent__TOP__0(vlSelf);
        Vservant_sim_servant_ram__D2000_R4d494e49___ico_sequent__TOP__servant_sim__dut__ram__0((&vlSymsp->TOP__servant_sim__dut__ram));
    }
}
