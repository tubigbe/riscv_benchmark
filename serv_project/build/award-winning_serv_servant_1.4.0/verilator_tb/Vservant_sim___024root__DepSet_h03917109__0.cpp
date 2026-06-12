// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim__Syms.h"
#include "Vservant_sim___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__ico(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG

void Vservant_sim___024root___eval_triggers__ico(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vservant_sim___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___ico_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);
void Vservant_sim___024root___ico_sequent__TOP__0(Vservant_sim___024root* vlSelf);
void Vservant_sim_servant_ram__D2000_R4d494e49___ico_sequent__TOP__servant_sim__dut__ram__0(Vservant_sim_servant_ram__D2000_R4d494e49* vlSelf);

void Vservant_sim___024root___eval_ico(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___ico_sequent__TOP__servant_sim__dut__0((&vlSymsp->TOP__servant_sim__dut));
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
        Vservant_sim___024root___ico_sequent__TOP__0(vlSelf);
        Vservant_sim_servant_ram__D2000_R4d494e49___ico_sequent__TOP__servant_sim__dut__ram__0((&vlSymsp->TOP__servant_sim__dut__ram));
    }
}

VL_INLINE_OPT void Vservant_sim___024root___ico_sequent__TOP__0(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pc_adr = vlSymsp->TOP__servant_sim__dut.__PVT__wb_mem_adr;
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__act(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG

void Vservant_sim___024root___eval_triggers__act(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, ((IData)(vlSelfRef.wb_clk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__wb_clk__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__wb_clk__0 = vlSelfRef.wb_clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vservant_sim___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);
void Vservant_sim_servant_ram__D2000_R4d494e49___nba_sequent__TOP__servant_sim__dut__ram__0(Vservant_sim_servant_ram__D2000_R4d494e49* vlSelf);
void Vservant_sim___024root___nba_sequent__TOP__0(Vservant_sim___024root* vlSelf);
void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__1(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf);

void Vservant_sim___024root___eval_nba(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__0((&vlSymsp->TOP__servant_sim__dut));
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        Vservant_sim_servant_ram__D2000_R4d494e49___nba_sequent__TOP__servant_sim__dut__ram__0((&vlSymsp->TOP__servant_sim__dut__ram));
        Vservant_sim___024root___nba_sequent__TOP__0(vlSelf);
        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__1((&vlSymsp->TOP__servant_sim__dut));
        Vservant_sim_servant_ram__D2000_R4d494e49___ico_sequent__TOP__servant_sim__dut__ram__0((&vlSymsp->TOP__servant_sim__dut__ram));
        Vservant_sim___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vservant_sim___024root___nba_sequent__TOP__0(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.q = vlSymsp->TOP__servant_sim__dut.__PVT__q;
    vlSelfRef.pc_vld = vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack;
}
