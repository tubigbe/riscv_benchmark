// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim__Syms.h"
#include "Vservant_sim_servant_sim.h"

VL_ATTR_COLD void Vservant_sim_servant_sim___eval_initial__TOP__servant_sim(Vservant_sim_servant_sim* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vservant_sim_servant_sim___eval_initial__TOP__servant_sim\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    // Body
    __Vtemp_1[0U] = 0x653d2573U;
    __Vtemp_1[1U] = 0x6d776172U;
    __Vtemp_1[2U] = 0x666972U;
    if (VL_UNLIKELY(VL_VALUEPLUSARGS_INW(1024, VL_CVT_PACK_STR_NW(3, __Vtemp_1), 
                                         vlSelfRef.__PVT__firmware_file))) {
        VL_WRITEF_NX("Loading RAM from %0s\n",0,1024,
                     vlSelfRef.__PVT__firmware_file.data());
        VL_READMEM_N(true, 32, 2048, 0, VL_CVT_PACK_STR_NW(32, vlSelfRef.__PVT__firmware_file)
                     ,  &(vlSymsp->TOP__servant_sim__dut__ram.mem)
                     , 0, ~0ULL);
    }
}
