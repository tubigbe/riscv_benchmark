// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vservant_sim.h for the primary calling header

#include "Vservant_sim__pch.h"
#include "Vservant_sim__Syms.h"
#include "Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3.h"

VL_ATTR_COLD void Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___stl_sequent__TOP__servant_sim__dut__0(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3___stl_sequent__TOP__servant_sim__dut__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17;
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_17 = 0;
    CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18;
    cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_18 = 0;
    // Body
    vlSelfRef.__PVT__cpu__DOT__wb_dbus_dat = (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                               << 0x18U) 
                                              | vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo);
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt1 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt7 = ((1U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 3U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq 
        = ((IData)(vlSelfRef.__PVT__timer_irq) & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie) 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_rdt = 
        ((0U != (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                 >> 0x1eU)) ? ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                >> 0x1fU) ? vlSelfRef.__PVT__timer__DOT__mtime
                                : (IData)(vlSelfRef.__PVT__wb_gpio_rdt))
          : vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt);
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d 
        = (1U & ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))
                  ? ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                     >> 4U) : (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)));
    vlSelfRef.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0 
        = (1U & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0) 
                 & ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                        >> 4U)) | (IData)((1U == (3U 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr 
        = ((((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20) 
             & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)) 
            << 1U) | (1U & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)) 
                            | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21))));
    vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en = 
        (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
          >> 3U) & (0x24000000U == (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                    >> 2U)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                  >> 1U) | ((0U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                          >> 1U))) 
                            | ((~ ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                   >> 2U)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))));
    vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en = (
                                                   (0U 
                                                    != vlSelfRef.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__f) 
                                                   & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                       >> 3U) 
                                                      & (0x20000000U 
                                                         == 
                                                         (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                          >> 2U))));
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
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 2U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr 
        = (IData)((0x11U == (0x11U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel 
        = ((4U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
           | (((1U == (3U & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                             >> 1U))) << 1U) | (0U 
                                                == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en 
        = (IData)((4U == (0x15U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3 
        = ((~ (IData)((0U != (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)))) 
           & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig 
        = (1U & (~ (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                     & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                        >> 1U)) | (IData)((6U == (6U 
                                                  & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)))))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt3 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                                    >> 3U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en 
        = (IData)((0U == (0x14U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_misalign 
        = (1U & ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                  & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                     | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                        >> 1U))) | ((vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                     & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                    >> 1U)));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc 
        = ((~ (IData)(vlSymsp->TOP.wb_rst)) & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc));
    vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16 
        = (IData)((5U == (5U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt0 = ((0U 
                                                  == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb));
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
    vlSelfRef.__PVT__rf_rdata = ((~ (- (IData)((IData)(vlSelfRef.__PVT__rf_ram__DOT__regzero)))) 
                                 & (IData)(vlSelfRef.__PVT__rf_ram__DOT__rdata));
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
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done = 
        ((7U == (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
         & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
            >> 3U));
    vlSelfRef.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7 
        = (IData)((0x14U == (0x14U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))));
    vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0 
        = (1U & (~ ((IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sig_en) 
                    | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__halt_en))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy 
        = (1U & (((1U & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr) 
                  + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2) 
                     + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r))) 
                 >> 1U));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4 
        = (1U & (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr 
                 + ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt2) 
                    + (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r))));
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op 
        = (1U & (((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                  >> 2U) | ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr) 
                            | (IData)((0U == (9U & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))));
    vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb = ((IData)(vlSelfRef.cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3) 
                                              & ((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__mem_misalign)) 
                                                 & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en)));
    if (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc) {
        vlSelfRef.__PVT__wb_mem_adr = vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr;
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack 
            = vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack;
    } else {
        vlSelfRef.__PVT__wb_mem_adr = (0xfffffffcU 
                                       & vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data);
        vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack = 0U;
    }
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__dbus_ack = 
        ((IData)(vlSelfRef.__PVT__wb_ext_ack) | (((~ (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)) 
                                                  & (IData)(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack)) 
                                                 | (IData)(vlSelfRef.__PVT__cpu__DOT__mux__DOT__sim_ack)));
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
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__rs2 = (1U 
                                                & ((IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1)
                                                    ? (IData)(vlSelfRef.__PVT__rf_rdata)
                                                    : (IData)(vlSelfRef.__PVT__cpu__DOT__rf_ram_if__DOT__rdata1)));
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
    vlSelfRef.__PVT__wb_mem_stb = (((IData)(vlSelfRef.__PVT__cpu__DOT__wb_dbus_stb) 
                                    & ((0U == (vlSelfRef.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                               >> 0x1eU)) 
                                       & (IData)(vlSelfRef.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0))) 
                                   | (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc));
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
    vlSelfRef.__PVT__cpu__DOT__cpu__DOT__imm = (1U 
                                                & ((IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__cnt_done)
                                                    ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl))
                                                     ? (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7)
                                                     : (IData)(vlSelfRef.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20))));
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
