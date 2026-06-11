// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim__Syms.h"
#include "Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3.h"

VL_INLINE_OPT void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___ico_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___ico_sequent__TOP__servant_sim__dut__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc 
        = ((~ (IData)(vlSymsp->TOP.wb_rst)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc));
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc) {
        vlSelfRef.__PVT__wb_mem_adr = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack 
            = vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack;
    } else {
        vlSelfRef.__PVT__wb_mem_adr = (0xfffffffcU 
                                       & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data);
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack = 0U;
    }
    vlSelfRef.__PVT__wb_mem_stb = (((IData)(vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb) 
                                    & ((0U == (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                               >> 0x1eU)) 
                                       & (IData)(vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0))) 
                                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack = 
        ((IData)(vlSelfRef.__PVT__wb_ext_ack) | (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)) 
                                                  & (IData)(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack)) 
                                                 | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack)));
    vlSelfRef.__PVT__cpu__DOT__rf_rreq = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
                                          | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending) 
                                             & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init)));
    vlSelfRef.__PVT__cpu__DOT__rf_wreq = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op) 
                                           & ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))
                                               ? (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt) 
                                                   >> 5U) 
                                                  & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init) 
                                                     | (IData)(vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3)))
                                               : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))) 
                                          | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack) 
                                             | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                  >> 4U) 
                                                 & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending)) 
                                                    & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))) 
                                                | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en) 
                                                   & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                       >> 1U) 
                                                      & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))))));
}

VL_INLINE_OPT void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17;
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17 = 0;
    CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18;
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18 = 0;
    CData/*0:0*/ __Vdly__wb_ext_ack;
    __Vdly__wb_ext_ack = 0;
    IData/*31:0*/ __Vdly__timer__DOT__mtime;
    __Vdly__timer__DOT__mtime = 0;
    CData/*0:0*/ __Vdly__cpu__DOT__mux__DOT__sim_ack;
    __Vdly__cpu__DOT__mux__DOT__sim_ack = 0;
    CData/*1:0*/ __Vdly__cpu__DOT__rf_ram_if__DOT__wdata0_r;
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata0_r = 0;
    CData/*2:0*/ __Vdly__cpu__DOT__rf_ram_if__DOT__wdata1_r;
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata1_r = 0;
    CData/*4:0*/ __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt;
    __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt = 0;
    CData/*2:0*/ __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt;
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt = 0;
    CData/*3:0*/ __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb;
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb = 0;
    SData/*8:0*/ __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20 = 0;
    CData/*5:0*/ __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25 = 0;
    CData/*4:0*/ __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7 = 0;
    IData/*31:0*/ __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data;
    __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data = 0;
    IData/*23:0*/ __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo;
    __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo = 0;
    CData/*0:0*/ __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie;
    __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie = 0;
    CData/*3:0*/ __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0;
    __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 = 0;
    IData/*31:0*/ __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
    __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd = 0;
    IData/*31:0*/ __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr = 0;
    CData/*1:0*/ __VdlyVal__rf_ram__DOT__memory__v0;
    __VdlyVal__rf_ram__DOT__memory__v0 = 0;
    SData/*9:0*/ __VdlyDim0__rf_ram__DOT__memory__v0;
    __VdlyDim0__rf_ram__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__rf_ram__DOT__memory__v0;
    __VdlySet__rf_ram__DOT__memory__v0 = 0;
    // Body
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata0_r = vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r;
    __Vdly__timer__DOT__mtime = vlSelfRef.__PVT__timer__DOT__mtime;
    __Vdly__wb_ext_ack = vlSelfRef.__PVT__wb_ext_ack;
    __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt = vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt;
    __Vdly__cpu__DOT__mux__DOT__sim_ack = vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack;
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata1_r = vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r;
    __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo;
    __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
    __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data;
    __VdlySet__rf_ram__DOT__memory__v0 = 0U;
    __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie;
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb;
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt;
    __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20;
    __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7 
        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7;
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata0_r = (((IData)(vlSelfRef.__PVT__cpu__DOT__wdata0) 
                                                   << 1U) 
                                                  | (1U 
                                                     & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r) 
                                                        >> 1U)));
    __Vdly__timer__DOT__mtime = ((IData)(1U) + vlSelfRef.__PVT__timer__DOT__mtime);
    __Vdly__wb_ext_ack = 0U;
    if (((IData)(vlSelfRef.__PVT__wb_ext_stb) & (~ (IData)(vlSelfRef.__PVT__wb_ext_ack)))) {
        __Vdly__wb_ext_ack = 1U;
    }
    __Vdly__cpu__DOT__mux__DOT__sim_ack = 0U;
    if (vlSymsp->TOP.wb_rst) {
        __Vdly__timer__DOT__mtime = 0U;
        __Vdly__wb_ext_ack = 0U;
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb) 
         & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack)))) {
        if (VL_UNLIKELY(((IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en) 
                         & (0U != vlSelfRef.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__f)))) {
            VL_FWRITEF_NX(vlSelfRef.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__f,"%c",0,
                          8,(0xffU & vlSelfRef.__PVT__cpu__DOT__wb_dbus_dat));
        } else if (VL_UNLIKELY(vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en)) {
            VL_WRITEF_NX("Test complete\n",0);
            VL_FINISH_MT("src/award-winning_serv_servile_1.4.0/servile/servile_mux.v", 87, "");
        }
        __Vdly__cpu__DOT__mux__DOT__sim_ack = ((IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en) 
                                               | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en));
    }
    __Vdly__cpu__DOT__rf_ram_if__DOT__wdata1_r = ((4U 
                                                   & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)
                                                        ? vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr
                                                        : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in)) 
                                                      << 2U)) 
                                                  | (3U 
                                                     & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r) 
                                                        >> 1U)));
    vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0 
        = (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0) 
                 >> 1U));
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__shift_en) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack))) {
        __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
            = (0xffffffU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack)
                             ? vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_rdt
                             : ((0x800000U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                              << 0x17U)) 
                                | (0x7fffffU & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
                                                >> 1U)))));
    }
    if ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
          | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)) 
         | (IData)(vlSymsp->TOP.wb_rst))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_csr__DOT__misalign_trap_sync_r 
            = ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
                   | (IData)(vlSymsp->TOP.wb_rst))) 
               & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending) 
                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)) 
                  | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_csr__DOT__misalign_trap_sync_r)));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc 
            = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en) 
               | (IData)(vlSymsp->TOP.wb_rst));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en) 
         | (IData)(vlSymsp->TOP.wb_rst))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr 
            = ((IData)(vlSymsp->TOP.wb_rst) ? 0U : 
               (((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap))
                   ? ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0) 
                          | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt1))) 
                      & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__rs2))
                   : ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__jump)
                       ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bad_pc)
                       : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4))) 
                 << 0x1fU) | (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr 
                              >> 1U)));
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_en) {
        __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data 
            = ((3U & __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data) 
               | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)
                     ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__q)
                     : ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                         >> 0x1fU) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm30))) 
                   << 0x1fU) | (0x7ffffffcU & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                               >> 1U))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)
          ? ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0) 
             | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt1))
          : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_en))) {
        __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data 
            = ((0xfffffffcU & __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data) 
               | ((2U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)
                           ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__q)
                           : (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                              >> 2U)) << 1U)) | (1U 
                                                 & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                    >> 1U))));
    }
    if ((((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1) 
          & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wen0_r)) 
         | ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wen1_r)))) {
        vlSelfRef.rf_ram__DOT____Vlvbound_h83862b22__0 
            = (3U & ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                      ? (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r)
                      : (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r)));
        if ((0x23fU >= (IData)(vlSelfRef.__PVT__rf_waddr))) {
            __VdlyVal__rf_ram__DOT__memory__v0 = vlSelfRef.rf_ram__DOT____Vlvbound_h83862b22__0;
            __VdlyDim0__rf_ram__DOT__memory__v0 = vlSelfRef.__PVT__rf_waddr;
            __VdlySet__rf_ram__DOT__memory__v0 = 1U;
        }
    }
    if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))) {
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0 
            = vlSelfRef.__PVT__rf_rdata;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wen0_r 
            = vlSelfRef.__PVT__cpu__DOT__wen0;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wen1_r 
            = ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
               & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en) 
                  | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)));
    }
    if (((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)) 
          | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en) 
              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt3)) 
             & (0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)))) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret))) {
        __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie 
            = ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
               & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret)
                   ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mpie)
                   : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in)));
    }
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb 
        = ((0xeU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                    << 1U)) | (1U & ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                       >> 3U) & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done))) 
                                     | ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_wreq) 
                                        | (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgnt)))));
    __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt = 
        (7U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
               + (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                        >> 3U))));
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
         | ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
            & ((1U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                             >> 1U))) | ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16) 
                                         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en)))))) {
        __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20 
            = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack)
                ? ((0x1feU & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                              >> 0xbU)) | (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                                                 >> 0x14U)))
                : ((0x100U & (((8U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl))
                                ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit)
                                : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20)) 
                              << 8U)) | (0xffU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                                  >> 1U))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
         | ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
            & (IData)((1U != (0x1dU & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))))) {
        __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25 
            = (0x3fU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack)
                         ? (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                            >> 0x19U) : ((0x20U & (
                                                   ((4U 
                                                     & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl))
                                                     ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm7)
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl))
                                                      ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit)
                                                      : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20))) 
                                                   << 5U)) 
                                         | (0x1fU & 
                                            ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25) 
                                             >> 1U)))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
         | ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
            & ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
               | (IData)((8U != (9U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20 
            = (0x1fU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack)
                         ? (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                            >> 0x14U) : ((0x10U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25) 
                                                   << 4U)) 
                                         | (0xfU & 
                                            ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20) 
                                             >> 1U)))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
         | ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
            & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op))))) {
        __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7 
            = (0x1fU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack)
                         ? (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                            >> 7U) : ((0x10U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25) 
                                                << 4U)) 
                                      | (0xfU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7) 
                                                 >> 1U)))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mie_en) 
         & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt7))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy));
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2_q;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r = 0U;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_en));
    vlSelfRef.__PVT__rf_ram__DOT__regzero = (1U & (~ (IData)(
                                                             (0U 
                                                              != 
                                                              (0x3fU 
                                                               & ((IData)(vlSelfRef.__PVT__rf_raddr) 
                                                                  >> 4U))))));
    vlSelfRef.__PVT__rf_ram__DOT__rdata = ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgate)
                                            ? ((0x23fU 
                                                >= (IData)(vlSelfRef.__PVT__rf_raddr))
                                                ? vlSelfRef.__PVT__rf_ram__DOT__memory
                                               [vlSelfRef.__PVT__rf_raddr]
                                                : 0U)
                                            : 0U);
    if (vlSelfRef.__PVT__cpu__DOT__wen0) {
        __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd 
            = (((IData)(vlSelfRef.__PVT__cpu__DOT__wdata0) 
                << 0x1fU) | (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd 
                             >> 1U));
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_rd) {
        if ((0x10U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
            if ((8U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                        if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x31 
                                = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                        } else {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x30 
                                = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                        }
                    } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x29 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    } else {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x28 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    }
                } else if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x27 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    } else {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x26 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    }
                } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x25 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x24 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x23 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    } else {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x22 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    }
                } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x21 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x20 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x19 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x18 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x17 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            } else {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x16 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            }
        } else if ((8U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
            if ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x15 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    } else {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x14 
                            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                    }
                } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x13 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x12 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x11 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x10 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x9 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            } else {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x8 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            }
        } else if ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
            if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x7 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                } else {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x6 
                        = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
                }
            } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x5 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            } else {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x4 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            }
        } else if ((2U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
            if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x3 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            } else {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x2 
                    = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
            }
        } else if ((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) {
            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x1 
                = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
        }
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r = 0U;
    if ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu_cmp;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy;
        __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr 
            = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in) 
                << 0x1fU) | (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr 
                             >> 1U));
    } else {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_sub;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mscratch) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mscratch 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtvec) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtvec 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mepc) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mepc 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtval) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtval 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mstatus) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mstatus 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mie) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mie 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mcause) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mcause 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    }
    vlSelfRef.__PVT__wb_gpio_rdt = vlSelfRef.__PVT__q;
    vlSelfRef.__PVT__timer_irq = VL_LTES_III(32, 0U, 
                                             (vlSelfRef.__PVT__timer__DOT__mtime 
                                              - vlSelfRef.__PVT__timer__DOT__mtimecmp));
    if (((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en) 
           & (0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb))) 
          & (0U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt))) 
         | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)))) {
        __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
            = ((7U & (IData)(__Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)) 
               | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op) 
                    & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20))) 
                   | ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
                      & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in))) 
                  << 3U));
        __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
            = ((0xbU & (IData)(__Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)) 
               | (4U & ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq) 
                          | (~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                >> 4U))) << 2U) | (0x7ffffffcU 
                                                   & (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
                                                       << 2U) 
                                                      & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0) 
                                                         >> 1U))))));
        __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
            = ((0xdU & (IData)(__Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)) 
               | (2U & (((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq) 
                           | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op)) 
                          | (IData)((8U == (0x18U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))) 
                         << 1U) | (0x7ffffffeU & ((
                                                   (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
                                                   << 1U) 
                                                  & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0) 
                                                     >> 1U))))));
        __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
            = ((0xeU & (IData)(__Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)) 
               | (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq) 
                         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op)) 
                        | ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
                           & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0) 
                              >> 1U)))));
    }
    if ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en) 
          & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause31 
            = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)
                ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq)
                : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in));
    }
    vlSelfRef.__PVT__wb_ext_ack = __Vdly__wb_ext_ack;
    if (vlSymsp->TOP.wb_rst) {
        __Vdly__cpu__DOT__mux__DOT__sim_ack = 0U;
    }
    vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack = __Vdly__cpu__DOT__mux__DOT__sim_ack;
    vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r 
        = __Vdly__cpu__DOT__rf_ram_if__DOT__wdata1_r;
    vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r 
        = __Vdly__cpu__DOT__rf_ram_if__DOT__wdata0_r;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25 
        = __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20 
        = __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20;
    if (__VdlySet__rf_ram__DOT__memory__v0) {
        vlSelfRef.__PVT__rf_ram__DOT__memory[__VdlyDim0__rf_ram__DOT__memory__v0] 
            = __VdlyVal__rf_ram__DOT__memory__v0;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd 
        = __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7 
        = __Vdly__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr 
        = __Vdly__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
    vlSelfRef.__PVT__timer__DOT__mtime = __Vdly__timer__DOT__mtime;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0 
        = __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0;
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done 
            = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init) 
               & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done)));
    }
    if (vlSymsp->TOP.wb_rst) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done = 0U;
        __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb = 0U;
        __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt = 0U;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt 
        = __Vdly__cpu__DOT__cpu__DOT__state__DOT__o_cnt;
    if ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__shift_en) 
          | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en)) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi 
            = (0xffU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack)
                         ? (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_rdt 
                            >> 0x18U) : ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt) 
                                         & (0xdfU | 
                                            (0x20U 
                                             & ((~ 
                                                 (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op) 
                                                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt7)) 
                                                  & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en)))) 
                                                << 5U))))));
    }
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
         & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mpie 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie;
    }
    vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgnt 
        = vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rreq_r;
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
         | (0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)))) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm7 
            = (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack)
                      ? (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                         >> 7U) : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit)));
    }
    if (((0x1fU == (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt)) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__rf_rreq))) {
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgate 
            = vlSelfRef.__PVT__cpu__DOT__rf_rreq;
    }
    __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt = (0x1fU 
                                              & ((IData)(1U) 
                                                 + (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt)));
    if (((IData)(vlSelfRef.__PVT__cpu__DOT__rf_rreq) 
         | (IData)(vlSelfRef.__PVT__cpu__DOT__rf_wreq))) {
        __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt = ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_wreq) 
                                                  << 1U);
    }
    if (vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1) {
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata1 
            = (1U & ((IData)(vlSelfRef.__PVT__rf_rdata) 
                     >> 1U));
    }
    vlSelfRef.__PVT__rf_rdata = ((~ (- (IData)((IData)(vlSelfRef.__PVT__rf_ram__DOT__regzero)))) 
                                 & (IData)(vlSelfRef.__PVT__rf_ram__DOT__rdata));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc 
        = ((~ (IData)(vlSymsp->TOP.wb_rst)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_rd 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__wen0));
    vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1 
        = (1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__rs2 = (1U 
                                                & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1)
                                                    ? (IData)(vlSelfRef.__PVT__rf_rdata)
                                                    : (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata1)));
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm25 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x19U));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OTHER = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRCI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRSI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRWI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRC = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRS = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRW = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__EBREAK = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ECALL = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__FENCE = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AND = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OR = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRA = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRL = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XOR = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLT = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLL = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SUB = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLTU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LH = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LB = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLT = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGEU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGE = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BNE = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BEQ = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JALR = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JAL = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AUIPC = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LUI = 0U;
        if (((((((((0x37U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                   | (0x17U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                  | (0x6fU == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                 | (0x67U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                | (0x63U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
               | (0x1063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
              | (0x4063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
             | (0x5063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))) {
            if ((0x37U != (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                if ((0x17U != (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                    if ((0x6fU != (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        if ((0x67U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            if ((0x63U != (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x1063U != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x4063U == 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLT = 1U;
                                    }
                                    if ((0x4063U != 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGE = 1U;
                                    }
                                }
                                if ((0x1063U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BNE = 1U;
                                }
                            }
                            if ((0x63U == (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BEQ = 1U;
                            }
                        }
                        if ((0x67U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JALR = 1U;
                        }
                    }
                    if ((0x6fU == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JAL = 1U;
                    }
                }
                if ((0x17U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AUIPC = 1U;
                }
            }
            if ((0x37U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LUI = 1U;
            }
        }
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LW = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LBU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LHU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SB = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SH = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SW = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADDI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTIU = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XORI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ORI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ANDI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLLI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRLI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRAI = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADD = 0U;
        if ((1U & (~ ((((((((0x37U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                            | (0x17U == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                           | (0x6fU == (0x7fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                          | (0x67U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                         | (0x63U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                        | (0x1063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                       | (0x4063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                      | (0x5063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))))) {
            if ((1U & (~ ((((((((0x6063U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                | (0x7063U == (0x707fU 
                                               & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                               | (3U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                              | (0x1003U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                             | (0x2003U == (0x707fU 
                                            & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                            | (0x4003U == (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                           | (0x5003U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                          | (0x23U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))))) {
                if ((1U & (~ ((((((((0x1023U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                    | (0x2023U == (0x707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                   | (0x13U == (0x707fU 
                                                & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                  | (0x2013U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                 | (0x3013U == (0x707fU 
                                                & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                | (0x4013U == (0x707fU 
                                               & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                               | (0x6013U == (0x707fU 
                                              & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                              | (0x7013U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))))) {
                    if ((1U & (~ ((((((((0x1013U == 
                                         (0xfe00707fU 
                                          & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                        | (0x5013U 
                                           == (0xfe00707fU 
                                               & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                       | (0x40005013U 
                                          == (0xfe00707fU 
                                              & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                      | (0x33U == (0xfe00707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                     | (0x40000033U 
                                        == (0xfe00707fU 
                                            & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                    | (0x1033U == (0xfe00707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                   | (0x2033U == (0xfe00707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                  | (0x3033U == (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))))) {
                        if ((1U & (~ ((((((((0x4033U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                            | (0x5033U 
                                               == (0xfe00707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                           | (0x40005033U 
                                              == (0xfe00707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                          | (0x6033U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                         | (0x7033U 
                                            == (0x707fU 
                                                & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                        | (0xfU == 
                                           (0x707fU 
                                            & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                       | (0x73U == vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                      | (0x100073U 
                                         == vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))))) {
                            if ((0x1073U != (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x2073U != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x3073U != 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        if ((0x5073U 
                                             != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            if ((0x6073U 
                                                 != 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                if (
                                                    (0x7073U 
                                                     != 
                                                     (0x707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OTHER = 1U;
                                                }
                                                if (
                                                    (0x7073U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRCI = 1U;
                                                }
                                            }
                                            if ((0x6073U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRSI = 1U;
                                            }
                                        }
                                        if ((0x5073U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRWI = 1U;
                                        }
                                    }
                                    if ((0x3073U == 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRC = 1U;
                                    }
                                }
                                if ((0x2073U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRS = 1U;
                                }
                            }
                            if ((0x1073U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRW = 1U;
                            }
                        }
                        if (((((((((0x4033U == (0x707fU 
                                                & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                                   | (0x5033U == (0xfe00707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                  | (0x40005033U == 
                                     (0xfe00707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                 | (0x6033U == (0x707fU 
                                                & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                                | (0x7033U == (0x707fU 
                                               & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                               | (0xfU == (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                              | (0x73U == vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                             | (0x100073U == vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            if ((0x4033U != (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x5033U != (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x40005033U 
                                         != (0xfe00707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        if ((0x6033U 
                                             != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            if ((0x7033U 
                                                 != 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                if (
                                                    (0xfU 
                                                     != 
                                                     (0x707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    if (
                                                        (0x73U 
                                                         != vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) {
                                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__EBREAK = 1U;
                                                    }
                                                    if (
                                                        (0x73U 
                                                         == vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) {
                                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ECALL = 1U;
                                                    }
                                                }
                                                if (
                                                    (0xfU 
                                                     == 
                                                     (0x707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__FENCE = 1U;
                                                }
                                            }
                                            if ((0x7033U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AND = 1U;
                                            }
                                        }
                                        if ((0x6033U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OR = 1U;
                                        }
                                    }
                                    if ((0x40005033U 
                                         == (0xfe00707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRA = 1U;
                                    }
                                }
                                if ((0x5033U == (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRL = 1U;
                                }
                            }
                            if ((0x4033U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XOR = 1U;
                            }
                        }
                    }
                    if (((((((((0x1013U == (0xfe00707fU 
                                            & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                               | (0x5013U == (0xfe00707fU 
                                              & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                              | (0x40005013U == (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                             | (0x33U == (0xfe00707fU 
                                          & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                            | (0x40000033U == (0xfe00707fU 
                                               & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                           | (0x1033U == (0xfe00707fU 
                                          & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                          | (0x2033U == (0xfe00707fU 
                                         & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                         | (0x3033U == (0xfe00707fU 
                                        & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))) {
                        if ((0x1013U != (0xfe00707fU 
                                         & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            if ((0x5013U != (0xfe00707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x40005013U != 
                                     (0xfe00707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x33U != (0xfe00707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        if ((0x40000033U 
                                             != (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            if ((0x1033U 
                                                 != 
                                                 (0xfe00707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                if (
                                                    (0x2033U 
                                                     != 
                                                     (0xfe00707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTU = 1U;
                                                }
                                                if (
                                                    (0x2033U 
                                                     == 
                                                     (0xfe00707fU 
                                                      & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLT = 1U;
                                                }
                                            }
                                            if ((0x1033U 
                                                 == 
                                                 (0xfe00707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLL = 1U;
                                            }
                                        }
                                        if ((0x40000033U 
                                             == (0xfe00707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SUB = 1U;
                                        }
                                    }
                                    if ((0x33U == (0xfe00707fU 
                                                   & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADD = 1U;
                                    }
                                }
                                if ((0x40005013U == 
                                     (0xfe00707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRAI = 1U;
                                }
                            }
                            if ((0x5013U == (0xfe00707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRLI = 1U;
                            }
                        }
                        if ((0x1013U == (0xfe00707fU 
                                         & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLLI = 1U;
                        }
                    }
                }
                if (((((((((0x1023U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                           | (0x2023U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                          | (0x13U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                         | (0x2013U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                        | (0x3013U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                       | (0x4013U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                      | (0x6013U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                     | (0x7013U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))) {
                    if ((0x1023U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SH = 1U;
                    }
                    if ((0x1023U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        if ((0x2023U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SW = 1U;
                        }
                        if ((0x2023U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            if ((0x13U == (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADDI = 1U;
                            }
                            if ((0x13U != (0x707fU 
                                           & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x2013U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTI = 1U;
                                }
                                if ((0x2013U != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x3013U == 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTIU = 1U;
                                    }
                                    if ((0x3013U != 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        if ((0x4013U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XORI = 1U;
                                        }
                                        if ((0x4013U 
                                             != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            if ((0x6013U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ORI = 1U;
                                            }
                                            if ((0x6013U 
                                                 != 
                                                 (0x707fU 
                                                  & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ANDI = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (((((((((0x6063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)) 
                       | (0x7063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                      | (3U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                     | (0x1003U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                    | (0x2003U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                   | (0x4003U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                  | (0x5003U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) 
                 | (0x23U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt)))) {
                if ((0x6063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLTU = 1U;
                }
                if ((0x6063U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                    if ((0x7063U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        if ((3U != (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            if ((0x1003U == (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LH = 1U;
                            }
                            if ((0x1003U != (0x707fU 
                                             & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                if ((0x2003U == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LW = 1U;
                                }
                                if ((0x2003U != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                    if ((0x4003U == 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LBU = 1U;
                                    }
                                    if ((0x4003U != 
                                         (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                        if ((0x5003U 
                                             == (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LHU = 1U;
                                        }
                                        if ((0x5003U 
                                             != (0x707fU 
                                                 & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SB = 1U;
                                        }
                                    }
                                }
                            }
                        }
                        if ((3U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                            vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LB = 1U;
                        }
                    }
                    if ((0x7063U == (0x707fU & vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt))) {
                        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGEU = 1U;
                    }
                }
            }
        }
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op22 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x16U));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x1aU));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x15U));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm31 
            = (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
               >> 0x1fU);
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3 
            = (7U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0xcU));
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d 
        = (1U & ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))
                  ? ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                     >> 4U) : (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel 
        = ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
           | (((1U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                             >> 1U))) << 1U) | (0U 
                                                == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig 
        = (1U & (~ (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                     & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                        >> 1U)) | (IData)((6U == (6U 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mie 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mie_en));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mstatus 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mcause 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mscratch 
        = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en)) 
           & (0U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtvec 
        = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en)) 
           & (1U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mepc 
        = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en)) 
           & (2U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtval 
        = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en)) 
           & (3U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)));
    if ((((~ (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
              >> 0x1fU)) & (IData)(vlSelfRef.__PVT__wb_ext_stb)) 
         & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
            >> 3U))) {
        vlSelfRef.__PVT__q = (1U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo);
    }
    if ((((IData)(vlSelfRef.__PVT__wb_ext_stb) & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                  >> 0x1fU)) 
         & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
            >> 3U))) {
        vlSelfRef.__PVT__timer__DOT__mtimecmp = vlSelfRef.__PVT__cpu__DOT__wb_dbus_dat;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm30 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x1eU));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20 
            = (1U & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                     >> 0x14U));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq 
            = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq) 
               & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq_r)));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode 
            = (0x1fU & (vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                        >> 2U));
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq_r 
            = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                  >> 1U) | ((0U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                          >> 1U))) 
                            | ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                   >> 2U)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie 
        = __Vdly__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie;
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb 
        = __Vdly__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb;
    if (vlSymsp->TOP.wb_rst) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie = 0U;
    }
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__jump = 
            ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init) 
             & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__take_branch));
    }
    if (vlSymsp->TOP.wb_rst) {
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__jump = 0U;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgnt = 0U;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rgate = 0U;
        __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt = 0U;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt 
            = __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
            = __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
            = __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rreq_r 
            = vlSelfRef.__PVT__cpu__DOT__rf_rreq;
        vlSelfRef.__PVT__timer__DOT__mtimecmp = 0U;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq = 0U;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rreq_r = 0U;
    } else {
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt 
            = __Vdly__cpu__DOT__rf_ram_if__DOT__rcnt;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
            = __Vdly__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
            = __Vdly__cpu__DOT__cpu__DOT__bufreg__DOT__data;
        vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rreq_r 
            = vlSelfRef.__PVT__cpu__DOT__rf_rreq;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt1 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt7 = ((1U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 3U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 2U));
    vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3 
        = ((~ (IData)((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)))) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt3 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 3U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done = 
        ((7U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
         & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
            >> 3U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2_q 
        = (((3U == (3U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi)) 
           | (((2U == (3U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
               & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
                  >> 0x10U)) | (((1U == (3U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                 & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo 
                                    >> 8U)) | ((0U 
                                                == 
                                                (3U 
                                                 & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                               & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_misalign 
        = (1U & ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                  & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                     | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                        >> 1U))) | ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                     & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                    >> 1U)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr 
        = ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20) 
             & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)) 
            << 1U) | (1U & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)) 
                            | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy 
        = (1U & (((1U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr) 
                  + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2) 
                     + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r))) 
                 >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4 
        = (1U & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr 
                 + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2) 
                    + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq 
        = ((IData)(vlSelfRef.__PVT__timer_irq) & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie) 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie)));
    vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0 
        = (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0) 
                 & ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                        >> 4U)) | (IData)((1U == (3U 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))));
    vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en = 
        (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
          >> 3U) & (0x24000000U == (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                    >> 2U)));
    vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en = (
                                                   (0U 
                                                    != vlSelfRef.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__f) 
                                                   & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                       >> 3U) 
                                                      & (0x20000000U 
                                                         == 
                                                         (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                          >> 2U))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr 
        = (IData)((0x11U == (0x11U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en 
        = (IData)((4U == (0x15U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en 
        = (IData)((0U == (0x14U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16 
        = (IData)((5U == (5U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_sub 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                  >> 1U) | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                            | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                 >> 3U) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm30)) 
                               | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                  >> 4U)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op 
        = (1U & ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                     >> 1U)) & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                >> 2U)));
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18 
        = (IData)((0U == (0x11U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl 
        = (((8U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                   >> 1U)) | ((IData)((0x10U == (0x11U 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))) 
                              << 2U)) | ((((0U == (3U 
                                                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                                           | (0U == 
                                              (3U & 
                                               ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                >> 1U)))) 
                                          << 1U) | 
                                         (8U == (0xfU 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))));
    vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7 
        = (IData)((0x14U == (0x14U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0 
        = (1U & (~ ((IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en) 
                    | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                  >> 2U) | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr) 
                            | (IData)((0U == (9U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))));
    vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3) 
                                              & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_misalign)) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype 
        = ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
               >> 4U)) & (IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_two_stage_op 
        = (1U & ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                     >> 2U)) | ((IData)(((1U == (3U 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))) 
                                         & (IData)(cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18))) 
                                | (IData)(((2U == (6U 
                                                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))) 
                                           & (IData)(cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret 
        = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
           & ((~ (IData)((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))) 
              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a 
        = (((0U == (7U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
            | ((3U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
               | (((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20)) 
                  | (0U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                  >> 3U)))))) & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr);
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op 
        = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
           & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21)) 
              & (~ (IData)((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en 
        = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
           & (0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en 
        = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
           & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
              >> 2U));
    vlSelfRef.__PVT__wb_ext_stb = ((IData)(vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb) 
                                   & ((IData)(vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0) 
                                      & (0U != (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                >> 0x1eU))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init = ((~ 
                                                  ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq) 
                                                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done))) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_two_stage_op));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op) 
                                                 | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__new_irq) 
                                                    | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_csr__DOT__misalign_trap_sync_r)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en) 
           & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20)) 
              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21)));
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17 
        = ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en) 
           & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20) 
              | ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21)) 
                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit 
        = ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en)) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm31));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__imm = (1U 
                                                & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)
                                                    ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl))
                                                     ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7)
                                                     : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en 
        = ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)) 
           & (0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__shift_en 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op)
            ? ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
               & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init) 
                  & (0U == (6U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)))))
            : ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
               & ((IData)((0U == (3U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data))) 
                  | ((IData)((0U == (6U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)))) 
                     | (((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                             >> 2U)) & (~ (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                           >> 1U))) 
                        | (((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                >> 2U)) & (~ vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                           | ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                  >> 1U)) & (~ (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                >> 1U)))))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op) 
           & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)) 
              | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                    >> 2U))));
    vlSelfRef.__PVT__rf_waddr = ((((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                                    ? ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)
                                        ? 0x22U : (0x20U 
                                                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)))
                                    : ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)
                                        ? 0x23U : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))) 
                                  << 4U) | (0xfU & 
                                            (((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt) 
                                              - (IData)(4U)) 
                                             >> 1U)));
    vlSelfRef.__PVT__cpu__DOT__wen0 = ((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
                                       & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
                                          | (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init)) 
                                              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op)) 
                                             & (0U 
                                                != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mie_en 
        = ((IData)(cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17) 
           & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20)) 
              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op22)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en 
        = ((IData)(cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17) 
           & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op22)) 
              & (~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20))));
    vlSelfRef.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
           | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en) 
              | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__csr_rd = (
                                                   ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en) 
                                                    & ((0U 
                                                        != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
                                                       & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt3) 
                                                           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie)) 
                                                          | (((2U 
                                                               == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                              & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                                 >> 3U)) 
                                                             | ((3U 
                                                                 == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                                & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)))))) 
                                                   | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en) 
                                                       & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__rs2)) 
                                                      | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en) 
                                                         & ((0U 
                                                             != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
                                                            & ((0U 
                                                                == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt))
                                                                ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)
                                                                : 
                                                               ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
                                                                & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause31)))))));
    vlSelfRef.__PVT__rf_raddr = ((((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                                    ? (((IData)(vlSelfRef.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0) 
                                        << 5U) | ((0x1cU 
                                                   & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20) 
                                                      & ((- (IData)(
                                                                    (1U 
                                                                     & (~ (IData)(vlSelfRef.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                         << 2U))) 
                                                  | (3U 
                                                     & ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)) 
                                                        | (((- (IData)((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en))) 
                                                            & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)) 
                                                           | ((- (IData)(
                                                                         (1U 
                                                                          & (~ (IData)(vlSelfRef.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20)))))))
                                    : (0x1fU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                                >> 4U))) 
                                  << 4U) | (0xfU & 
                                            ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt) 
                                             >> 1U)));
    vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_1 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__imm) 
           & ((~ ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                    >> 4U) & ((0U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                              | (3U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))) 
                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0))) 
              & (~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                    >> 2U))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b = ((8U 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))
                                                  ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__rs2)
                                                  : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__imm));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in 
        = ((1U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))
            ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d)
            : ((2U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))
                ? ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__csr_rd) 
                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d))
                : ((3U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))
                    ? ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d)) 
                       & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__csr_rd))
                    : ((0U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))) 
                       & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__csr_rd)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c 
        = (1U & (((IData)(vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0) 
                  + ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_1) 
                     + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r))) 
                 >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__q 
        = (1U & ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0) 
                 + ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_1) 
                    + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en)
            ? (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b) 
                << 7U) | ((0x40U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                    >> 1U)) | (0x3fU 
                                               & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                                  - (IData)(1U)))))
            : (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b) 
                << 7U) | (0x7fU & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                   >> 1U))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_b 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b) 
           ^ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_sub));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_en 
        = (((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
            & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__init) 
               | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap) 
                   | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                      >> 4U)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_two_stage_op)))) 
           | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op) 
              & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done) 
                 & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt) 
                     >> 5U) | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                               >> 2U)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy 
        = (1U & (((1U & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)) 
                  + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_b) 
                     + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r))) 
                 >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add 
        = (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0) 
                 + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_b) 
                    + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_q = 
        (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
         & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_en));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu_cmp = 
        (1U & ((0U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                             >> 1U))) ? ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add)) 
                                         & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                            | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0)))
                : (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                    & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)) 
                   + ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                          & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b))) 
                      + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype)
            ? ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                 >> 2U) | (3U == (3U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)))) 
               & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__imm))
            : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_q));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__take_branch 
        = (IData)((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                    >> 4U) & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                              | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu_cmp) 
                                 ^ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a) 
                  + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b) 
                     + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r))) 
                 >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bad_pc = (1U 
                                                   & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0)) 
                                                      & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a) 
                                                         + 
                                                         ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b) 
                                                          + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r)))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending 
        = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__take_branch) 
            & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
               >> 1U)) | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en) 
                          & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_misalign)));
    vlSelfRef.__PVT__cpu__DOT__wdata0 = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__trap)
                                          ? ((0x10U 
                                              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))
                                              ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bad_pc)
                                              : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_q))
                                          : ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg_q) 
                                               | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                   & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add)) 
                                                  | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                       >> 1U) 
                                                      & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                                         & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0))) 
                                                     | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                         >> 2U) 
                                                        & (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                                            & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                               ^ (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))) 
                                                           | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                               >> 1U) 
                                                              & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)))))))) 
                                              & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en)) 
                                             | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__csr_rd) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en)) 
                                                | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid)
                                                      ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2_q)
                                                      : 
                                                     ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit) 
                                                      & (~ 
                                                         ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                          >> 2U)))) 
                                                    & (IData)(
                                                              (0U 
                                                               == 
                                                               (5U 
                                                                & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))) 
                                                   | (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype) 
                                                       & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bad_pc)) 
                                                      | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4) 
                                                         & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr)))))));
}

VL_INLINE_OPT void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__1(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___nba_sequent__TOP__servant_sim__dut__1\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__wb_mem_stb = (((IData)(vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb) 
                                    & ((0U == (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                               >> 0x1eU)) 
                                       & (IData)(vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0))) 
                                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc));
    vlSelfRef.__PVT__cpu__DOT__wb_dbus_dat = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                               << 0x18U) 
                                              | vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo);
    vlSelfRef.__PVT__wb_mem_adr = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)
                                    ? vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr
                                    : (0xfffffffcU 
                                       & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack = 
        ((IData)(vlSelfRef.__PVT__wb_ext_ack) | (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)) 
                                                  & (IData)(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack)) 
                                                 | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack 
        = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc) 
           & (IData)(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_rdt = 
        ((0U != (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                 >> 0x1eU)) ? ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                >> 0x1fU) ? vlSelfRef.__PVT__timer__DOT__mtime
                                : (IData)(vlSelfRef.__PVT__wb_gpio_rdt))
          : vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt);
    vlSelfRef.__PVT__cpu__DOT__rf_wreq = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op) 
                                           & ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))
                                               ? (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt) 
                                                   >> 5U) 
                                                  & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init) 
                                                     | (IData)(vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3)))
                                               : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))) 
                                          | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack) 
                                             | ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                  >> 4U) 
                                                 & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending)) 
                                                    & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))) 
                                                | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en) 
                                                   & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                       >> 1U) 
                                                      & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init))))));
    vlSelfRef.__PVT__cpu__DOT__rf_rreq = ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack) 
                                          | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending) 
                                             & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init)));
}
