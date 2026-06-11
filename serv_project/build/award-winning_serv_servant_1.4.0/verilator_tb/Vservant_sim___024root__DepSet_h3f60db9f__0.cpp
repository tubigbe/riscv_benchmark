// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim___024root.h"

void Vservant_sim___024root___eval_triggers__ico(Vservant_sim___024root* vlSelf);
void Vservant_sim___024root___eval_ico(Vservant_sim___024root* vlSelf);

bool Vservant_sim___024root___eval_phase__ico(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vservant_sim___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vservant_sim___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vservant_sim___024root___eval_act(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vservant_sim___024root___eval_triggers__act(Vservant_sim___024root* vlSelf);

bool Vservant_sim___024root___eval_phase__act(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vservant_sim___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vservant_sim___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vservant_sim___024root___eval_nba(Vservant_sim___024root* vlSelf);

bool Vservant_sim___024root___eval_phase__nba(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vservant_sim___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__ico(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__nba(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vservant_sim___024root___dump_triggers__act(Vservant_sim___024root* vlSelf);
#endif  // VL_DEBUG

void Vservant_sim___024root___eval(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vservant_sim___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("src/award-winning_serv_servant_1.4.0/bench/servant_sim.v", 2, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vservant_sim___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vservant_sim___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("src/award-winning_serv_servant_1.4.0/bench/servant_sim.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vservant_sim___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("src/award-winning_serv_servant_1.4.0/bench/servant_sim.v", 2, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vservant_sim___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vservant_sim___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vservant_sim___024root___eval_debug_assertions(Vservant_sim___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.wb_clk & 0xfeU))) {
        Verilated::overWidthError("wb_clk");}
    if (VL_UNLIKELY((vlSelfRef.wb_rst & 0xfeU))) {
        Verilated::overWidthError("wb_rst");}
}
#endif  // VL_DEBUG
