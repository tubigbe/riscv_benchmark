// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vservant_sim__Syms.h"


void Vservant_sim___024root__trace_chg_0_sub_0(Vservant_sim___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vservant_sim___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root__trace_chg_0\n"); );
    // Init
    Vservant_sim___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vservant_sim___024root*>(voidSelf);
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vservant_sim___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vservant_sim___024root__trace_chg_0_sub_0(Vservant_sim___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root__trace_chg_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelfRef.__Vm_traceActivity[0U])) {
        bufp->chgWData(oldp+0,(vlSymsp->TOP__servant_sim.__PVT__firmware_file),1024);
        bufp->chgIData(oldp+32,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__f),32);
        bufp->chgWData(oldp+33,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__mux__DOT__genblk1__DOT__signature_file),1024);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U] 
                     | vlSelfRef.__Vm_traceActivity
                     [2U]))) {
        bufp->chgIData(oldp+65,(vlSymsp->TOP__servant_sim__dut.__PVT__wb_mem_adr),32);
        bufp->chgBit(oldp+66,((1U & ((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)) 
                                     & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                        >> 3U)))));
        bufp->chgBit(oldp+67,(vlSymsp->TOP__servant_sim__dut.__PVT__wb_mem_stb));
        bufp->chgBit(oldp+68,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc));
        bufp->chgBit(oldp+69,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_ack));
        bufp->chgBit(oldp+70,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__dbus_ack));
        bufp->chgBit(oldp+71,(((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc)) 
                               & (IData)(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack))));
        bufp->chgBit(oldp+72,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_wreq));
        bufp->chgBit(oldp+73,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_rreq));
        bufp->chgBit(oldp+74,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_wreq) 
                               | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rgnt))));
        bufp->chgSData(oldp+75,((0x7ffU & (vlSymsp->TOP__servant_sim__dut.__PVT__wb_mem_adr 
                                           >> 2U))),11);
        bufp->chgCData(oldp+76,(vlSymsp->TOP__servant_sim__dut__ram.__PVT__we),4);
    }
    if (VL_UNLIKELY(vlSelfRef.__Vm_traceActivity[2U])) {
        bufp->chgBit(oldp+77,(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_ack));
        bufp->chgBit(oldp+78,(vlSymsp->TOP__servant_sim__dut.__PVT__q));
        bufp->chgBit(oldp+79,(vlSymsp->TOP__servant_sim__dut.__PVT__timer_irq));
        bufp->chgIData(oldp+80,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__wb_dbus_dat),32);
        bufp->chgCData(oldp+81,((((8U & (((3U == (3U 
                                                  & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                          << 3U) | 
                                         (0xfffffff8U 
                                          & (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                              << 2U) 
                                             | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                 << 3U) 
                                                & (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                   << 2U)))))) 
                                  | (4U & (((2U == 
                                             (3U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                            << 2U) 
                                           | (0xfffffffcU 
                                              & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                 << 1U))))) 
                                 | ((2U & (((1U == 
                                             (3U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                            << 1U) 
                                           | ((0xfffffffeU 
                                               & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                              | (((~ 
                                                   (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                    >> 1U)) 
                                                  & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                                 << 1U)))) 
                                    | (0U == (3U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data))))),4);
        bufp->chgIData(oldp+82,(vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt),32);
        bufp->chgBit(oldp+83,((1U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo)));
        bufp->chgBit(oldp+84,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                     >> 3U))));
        bufp->chgBit(oldp+85,(((~ (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                   >> 0x1fU)) & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__wb_ext_stb))));
        bufp->chgBit(oldp+86,(vlSymsp->TOP__servant_sim__dut.__PVT__wb_gpio_rdt));
        bufp->chgBit(oldp+87,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__wb_ext_stb) 
                               & (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                  >> 0x1fU))));
        bufp->chgIData(oldp+88,(vlSymsp->TOP__servant_sim__dut.__PVT__timer__DOT__mtime),32);
        bufp->chgIData(oldp+89,((0xfffffffcU & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)),32);
        bufp->chgBit(oldp+90,(vlSymsp->TOP__servant_sim__dut.__PVT__wb_ext_stb));
        bufp->chgIData(oldp+91,(((vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                  >> 0x1fU) ? vlSymsp->TOP__servant_sim__dut.__PVT__timer__DOT__mtime
                                  : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__wb_gpio_rdt))),32);
        bufp->chgBit(oldp+92,(vlSymsp->TOP__servant_sim__dut.__PVT__wb_ext_ack));
        bufp->chgSData(oldp+93,(vlSymsp->TOP__servant_sim__dut.__PVT__rf_waddr),10);
        bufp->chgCData(oldp+94,((3U & ((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                                        ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r)
                                        : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r)))),2);
        bufp->chgBit(oldp+95,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wen0_r)) 
                               | ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt) 
                                  & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wen1_r)))));
        bufp->chgSData(oldp+96,(vlSymsp->TOP__servant_sim__dut.__PVT__rf_raddr),10);
        bufp->chgBit(oldp+97,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rgate));
        bufp->chgCData(oldp+98,(vlSymsp->TOP__servant_sim__dut.__PVT__rf_rdata),2);
        bufp->chgIData(oldp+99,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr),32);
        bufp->chgBit(oldp+100,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__wb_dbus_stb));
        bufp->chgIData(oldp+101,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__dbus_rdt),32);
        bufp->chgBit(oldp+102,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__wb_dbus_stb) 
                                & ((0U == (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                           >> 0x1eU)) 
                                   & (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0)))));
        bufp->chgCData(oldp+103,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)
                                   ? 0x23U : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7))),6);
        bufp->chgCData(oldp+104,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)
                                   ? 0x22U : (0x20U 
                                              | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)))),6);
        bufp->chgBit(oldp+105,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__wen0));
        bufp->chgBit(oldp+106,(((0U != (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb)) 
                                & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en) 
                                   | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)))));
        bufp->chgBit(oldp+107,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__wdata0));
        bufp->chgBit(oldp+108,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)
                                       ? vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr
                                       : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in)))));
        bufp->chgCData(oldp+109,((0x1fU & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                           >> 4U))),6);
        bufp->chgCData(oldp+110,((((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0) 
                                   << 5U) | ((0x1cU 
                                              & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20) 
                                                 & ((- (IData)(
                                                               (1U 
                                                                & (~ (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                    << 2U))) 
                                             | (3U 
                                                & ((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                                                     << 1U) 
                                                    | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)) 
                                                   | (((- (IData)((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en))) 
                                                       & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)) 
                                                      | ((- (IData)(
                                                                    (1U 
                                                                     & (~ (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                         & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20)))))))),6);
        bufp->chgBit(oldp+111,((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))));
        bufp->chgBit(oldp+112,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__rs2));
        bufp->chgIData(oldp+113,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data),32);
        bufp->chgCData(oldp+114,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3),3);
        bufp->chgCData(oldp+115,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7),5);
        bufp->chgCData(oldp+116,((0x1fU & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                           >> 4U))),5);
        bufp->chgCData(oldp+117,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20),5);
        bufp->chgCData(oldp+118,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl),4);
        bufp->chgCData(oldp+119,(((((IData)((1U != 
                                             (0x1dU 
                                              & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))) 
                                    << 3U) | (((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
                                               | (8U 
                                                  != 
                                                  (9U 
                                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))) 
                                              << 2U)) 
                                  | ((((1U == (3U & 
                                               ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                >> 1U))) 
                                       | ((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16) 
                                          | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en))) 
                                      << 1U) | (1U 
                                                & (~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op)))))),4);
        bufp->chgBit(oldp+120,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                      >> 2U))));
        bufp->chgBit(oldp+121,((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))));
        bufp->chgBit(oldp+122,((1U & (~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))));
        bufp->chgBit(oldp+123,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_two_stage_op));
        bufp->chgBit(oldp+124,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op));
        bufp->chgBit(oldp+125,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20));
        bufp->chgBit(oldp+126,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                      >> 4U))));
        bufp->chgBit(oldp+127,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op));
        bufp->chgBit(oldp+128,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op));
        bufp->chgBit(oldp+129,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en));
        bufp->chgBit(oldp+130,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en));
        bufp->chgBit(oldp+131,((IData)((0U == (5U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))));
        bufp->chgBit(oldp+132,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype) 
                                 & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bad_pc)) 
                                | ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4) 
                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr)))));
        bufp->chgBit(oldp+133,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg_q) 
                                      | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                          & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add)) 
                                         | ((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                              >> 1U) 
                                             & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0))) 
                                            | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                                >> 2U) 
                                               & (((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                                   & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                      ^ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))) 
                                                  | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                      >> 1U) 
                                                     & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                        & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)))))))))));
        bufp->chgBit(oldp+134,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid)
                                 ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2_q)
                                 : ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit) 
                                    & (~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                          >> 2U))))));
        bufp->chgBit(oldp+135,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__csr_rd));
        bufp->chgBit(oldp+136,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl_pc_en));
        bufp->chgBit(oldp+137,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__jump));
        bufp->chgBit(oldp+138,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr));
        bufp->chgBit(oldp+139,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype));
        bufp->chgBit(oldp+140,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret));
        bufp->chgBit(oldp+141,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__imm));
        bufp->chgBit(oldp+142,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap));
        bufp->chgBit(oldp+143,(((0U == (7U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                                | ((3U == (3U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                                   | (((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7) 
                                       & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20)) 
                                      | (0U == (3U 
                                                & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                                   >> 3U))))))));
        bufp->chgBit(oldp+144,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__init));
        bufp->chgBit(oldp+145,((0U != (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb))));
        bufp->chgBit(oldp+146,((0U == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt))));
        bufp->chgBit(oldp+147,((IData)((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                         >> 2U) | (3U 
                                                   == 
                                                   (3U 
                                                    & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)))))));
        bufp->chgBit(oldp+148,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0));
        bufp->chgBit(oldp+149,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt1));
        bufp->chgBit(oldp+150,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt2));
        bufp->chgBit(oldp+151,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt3));
        bufp->chgBit(oldp+152,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt7));
        bufp->chgBit(oldp+153,(((2U == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                   >> 3U))));
        bufp->chgBit(oldp+154,(((3U == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb))));
        bufp->chgBit(oldp+155,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt_done));
        bufp->chgBit(oldp+156,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg_en));
        bufp->chgBit(oldp+157,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm30));
        bufp->chgBit(oldp+158,((1U & ((~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                          >> 4U)) | (IData)(
                                                            (1U 
                                                             == 
                                                             (3U 
                                                              & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))))));
        bufp->chgBit(oldp+159,((1U & (~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                         >> 2U)))));
        bufp->chgBit(oldp+160,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                 >> 4U) & ((0U == (3U 
                                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                                           | (3U == 
                                              (3U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode)))))));
        bufp->chgBit(oldp+161,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg_q));
        bufp->chgBit(oldp+162,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2_q));
        bufp->chgBit(oldp+163,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_sub));
        bufp->chgCData(oldp+164,((3U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3))),2);
        bufp->chgBit(oldp+165,((0U == (3U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                             >> 1U)))));
        bufp->chgBit(oldp+166,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig));
        bufp->chgBit(oldp+167,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu_cmp));
        bufp->chgCData(oldp+168,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel),3);
        bufp->chgBit(oldp+169,(((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__init)) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op))));
        bufp->chgBit(oldp+170,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b));
        bufp->chgBit(oldp+171,((1U & (~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                         >> 2U)))));
        bufp->chgBit(oldp+172,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                      >> 1U))));
        bufp->chgCData(oldp+173,((3U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                        >> 1U))),2);
        bufp->chgBit(oldp+174,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt) 
                                      >> 5U))));
        bufp->chgBit(oldp+175,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_misalign));
        bufp->chgBit(oldp+176,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bad_pc));
        bufp->chgBit(oldp+177,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en));
        bufp->chgBit(oldp+178,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mie_en));
        bufp->chgBit(oldp+179,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en));
        bufp->chgBit(oldp+180,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                      >> 4U))));
        bufp->chgBit(oldp+181,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en));
        bufp->chgCData(oldp+182,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr),2);
        bufp->chgBit(oldp+183,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en));
        bufp->chgBit(oldp+184,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in));
        bufp->chgBit(oldp+185,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__rs2))));
        bufp->chgBit(oldp+186,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en));
        bufp->chgBit(oldp+187,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__new_irq));
        bufp->chgCData(oldp+188,((3U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)),2);
        bufp->chgBit(oldp+189,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add));
        bufp->chgBit(oldp+190,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0))));
        bufp->chgBit(oldp+191,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r));
        bufp->chgBit(oldp+192,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy));
        bufp->chgBit(oldp+193,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r));
        bufp->chgBit(oldp+194,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))));
        bufp->chgBit(oldp+195,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b))));
        bufp->chgBit(oldp+196,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_b));
        bufp->chgBit(oldp+197,((1U & (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                                       & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)) 
                                      + ((~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig) 
                                             & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b))) 
                                         + (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy))))));
        bufp->chgBit(oldp+198,(((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add)) 
                                & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                   | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0)))));
        bufp->chgBit(oldp+199,((1U & (((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                       & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                          ^ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))) 
                                      | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                          >> 1U) & 
                                         ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                          & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)))))));
        bufp->chgCData(oldp+200,((7U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi))),3);
        bufp->chgBit(oldp+201,((1U & (((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0) 
                                       + ((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_1) 
                                          + (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r))) 
                                      >> 1U))));
        bufp->chgBit(oldp+202,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__q));
        bufp->chgBit(oldp+203,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r));
        bufp->chgBit(oldp+204,(((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                  >> 4U) & ((0U == 
                                             (3U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))) 
                                            | (3U == 
                                               (3U 
                                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))) 
                                & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0))));
        bufp->chgCData(oldp+205,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi),8);
        bufp->chgIData(oldp+206,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo),24);
        bufp->chgBit(oldp+207,((1U & ((IData)((0U == 
                                               (3U 
                                                & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data))) 
                                      | ((IData)((0U 
                                                  == 
                                                  (6U 
                                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)))) 
                                         | (((~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                                 >> 2U)) 
                                             & (~ (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                   >> 1U))) 
                                            | (((~ 
                                                 ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                                  >> 2U)) 
                                                & (~ vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data)) 
                                               | ((~ 
                                                   ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt) 
                                                    >> 1U)) 
                                                  & (~ 
                                                     (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                                      >> 1U))))))))));
        bufp->chgBit(oldp+208,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__shift_en));
        bufp->chgBit(oldp+209,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en));
        bufp->chgCData(oldp+210,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                   << 7U) | ((0x40U 
                                              & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                                 >> 1U)) 
                                             | (0x3fU 
                                                & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi) 
                                                   - (IData)(1U)))))),8);
        bufp->chgCData(oldp+211,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt),8);
        bufp->chgBit(oldp+212,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                                | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap))));
        bufp->chgBit(oldp+213,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4));
        bufp->chgBit(oldp+214,((1U & (((1U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr) 
                                       + ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt2) 
                                          + (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r))) 
                                      >> 1U))));
        bufp->chgBit(oldp+215,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r));
        bufp->chgBit(oldp+216,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a) 
                                      + ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b) 
                                         + (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r))))));
        bufp->chgBit(oldp+217,((1U & (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a) 
                                       + ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b) 
                                          + (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r))) 
                                      >> 1U))));
        bufp->chgBit(oldp+218,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r));
        bufp->chgBit(oldp+219,((1U & vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__wb_ibus_adr)));
        bufp->chgBit(oldp+220,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                                 | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap))
                                 ? ((~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0) 
                                        | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt1))) 
                                    & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__rs2))
                                 : ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__jump)
                                     ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bad_pc)
                                     : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4)))));
        bufp->chgBit(oldp+221,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a));
        bufp->chgBit(oldp+222,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b));
        bufp->chgIData(oldp+223,((vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                                  >> 2U)),30);
        bufp->chgCData(oldp+224,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode),5);
        bufp->chgBit(oldp+225,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21));
        bufp->chgBit(oldp+226,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op22));
        bufp->chgBit(oldp+227,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26));
        bufp->chgBit(oldp+228,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__imm25));
        bufp->chgBit(oldp+229,(((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op20) 
                                | ((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op21)) 
                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__op26)))));
        bufp->chgBit(oldp+230,((1U & (~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode) 
                                         >> 4U)))));
        bufp->chgBit(oldp+231,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie));
        bufp->chgBit(oldp+232,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mpie));
        bufp->chgBit(oldp+233,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie));
        bufp->chgBit(oldp+234,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause31));
        bufp->chgCData(oldp+235,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0),4);
        bufp->chgBit(oldp+236,((1U & ((0U == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt))
                                       ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0)
                                       : ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt_done) 
                                          & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause31))))));
        bufp->chgBit(oldp+237,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq_r));
        bufp->chgBit(oldp+238,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d));
        bufp->chgBit(oldp+239,((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt3) 
                                 & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie)) 
                                | (((2U == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                    & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb) 
                                       >> 3U)) | ((3U 
                                                   == (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt)) 
                                                  & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb))))));
        bufp->chgBit(oldp+240,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq));
        bufp->chgBit(oldp+241,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_rd));
        bufp->chgBit(oldp+242,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mscratch));
        bufp->chgBit(oldp+243,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtvec));
        bufp->chgBit(oldp+244,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mepc));
        bufp->chgBit(oldp+245,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtval));
        bufp->chgBit(oldp+246,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mstatus));
        bufp->chgBit(oldp+247,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mie));
        bufp->chgBit(oldp+248,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mcause));
        bufp->chgIData(oldp+249,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd),32);
        bufp->chgIData(oldp+250,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr),32);
        bufp->chgIData(oldp+251,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mstatus),32);
        bufp->chgIData(oldp+252,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mie),32);
        bufp->chgIData(oldp+253,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mcause),32);
        bufp->chgIData(oldp+254,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mscratch),32);
        bufp->chgIData(oldp+255,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtvec),32);
        bufp->chgIData(oldp+256,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mepc),32);
        bufp->chgIData(oldp+257,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtval),32);
        bufp->chgIData(oldp+258,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x1),32);
        bufp->chgIData(oldp+259,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x2),32);
        bufp->chgIData(oldp+260,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x3),32);
        bufp->chgIData(oldp+261,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x4),32);
        bufp->chgIData(oldp+262,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x5),32);
        bufp->chgIData(oldp+263,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x6),32);
        bufp->chgIData(oldp+264,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x7),32);
        bufp->chgIData(oldp+265,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x8),32);
        bufp->chgIData(oldp+266,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x9),32);
        bufp->chgIData(oldp+267,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x10),32);
        bufp->chgIData(oldp+268,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x11),32);
        bufp->chgIData(oldp+269,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x12),32);
        bufp->chgIData(oldp+270,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x13),32);
        bufp->chgIData(oldp+271,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x14),32);
        bufp->chgIData(oldp+272,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x15),32);
        bufp->chgIData(oldp+273,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x16),32);
        bufp->chgIData(oldp+274,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x17),32);
        bufp->chgIData(oldp+275,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x18),32);
        bufp->chgIData(oldp+276,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x19),32);
        bufp->chgIData(oldp+277,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x20),32);
        bufp->chgIData(oldp+278,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x21),32);
        bufp->chgIData(oldp+279,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x22),32);
        bufp->chgIData(oldp+280,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x23),32);
        bufp->chgIData(oldp+281,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x24),32);
        bufp->chgIData(oldp+282,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x25),32);
        bufp->chgIData(oldp+283,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x26),32);
        bufp->chgIData(oldp+284,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x27),32);
        bufp->chgIData(oldp+285,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x28),32);
        bufp->chgIData(oldp+286,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x29),32);
        bufp->chgIData(oldp+287,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x30),32);
        bufp->chgIData(oldp+288,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x31),32);
        bufp->chgBit(oldp+289,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LUI));
        bufp->chgBit(oldp+290,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AUIPC));
        bufp->chgBit(oldp+291,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JAL));
        bufp->chgBit(oldp+292,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JALR));
        bufp->chgBit(oldp+293,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BEQ));
        bufp->chgBit(oldp+294,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BNE));
        bufp->chgBit(oldp+295,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLT));
        bufp->chgBit(oldp+296,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGE));
        bufp->chgBit(oldp+297,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLTU));
        bufp->chgBit(oldp+298,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGEU));
        bufp->chgBit(oldp+299,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LB));
        bufp->chgBit(oldp+300,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LH));
        bufp->chgBit(oldp+301,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LW));
        bufp->chgBit(oldp+302,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LBU));
        bufp->chgBit(oldp+303,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LHU));
        bufp->chgBit(oldp+304,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SB));
        bufp->chgBit(oldp+305,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SH));
        bufp->chgBit(oldp+306,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SW));
        bufp->chgBit(oldp+307,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADDI));
        bufp->chgBit(oldp+308,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTI));
        bufp->chgBit(oldp+309,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTIU));
        bufp->chgBit(oldp+310,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XORI));
        bufp->chgBit(oldp+311,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ORI));
        bufp->chgBit(oldp+312,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ANDI));
        bufp->chgBit(oldp+313,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLLI));
        bufp->chgBit(oldp+314,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRLI));
        bufp->chgBit(oldp+315,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRAI));
        bufp->chgBit(oldp+316,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADD));
        bufp->chgBit(oldp+317,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SUB));
        bufp->chgBit(oldp+318,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLL));
        bufp->chgBit(oldp+319,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLT));
        bufp->chgBit(oldp+320,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTU));
        bufp->chgBit(oldp+321,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XOR));
        bufp->chgBit(oldp+322,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRL));
        bufp->chgBit(oldp+323,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRA));
        bufp->chgBit(oldp+324,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OR));
        bufp->chgBit(oldp+325,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AND));
        bufp->chgBit(oldp+326,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__FENCE));
        bufp->chgBit(oldp+327,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ECALL));
        bufp->chgBit(oldp+328,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__EBREAK));
        bufp->chgBit(oldp+329,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRW));
        bufp->chgBit(oldp+330,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRS));
        bufp->chgBit(oldp+331,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRC));
        bufp->chgBit(oldp+332,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRWI));
        bufp->chgBit(oldp+333,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRSI));
        bufp->chgBit(oldp+334,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRCI));
        bufp->chgBit(oldp+335,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OTHER));
        bufp->chgIData(oldp+336,((vlSymsp->TOP__servant_sim__dut__ram.__PVT__o_wb_rdt 
                                  >> 7U)),25);
        bufp->chgBit(oldp+337,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm31));
        bufp->chgSData(oldp+338,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20),9);
        bufp->chgBit(oldp+339,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm7));
        bufp->chgCData(oldp+340,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25),6);
        bufp->chgBit(oldp+341,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit));
        bufp->chgBit(oldp+342,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit));
        bufp->chgBit(oldp+343,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid));
        bufp->chgBit(oldp+344,((((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__init)) 
                                 & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op)) 
                                & (0U != (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7)))));
        bufp->chgBit(oldp+345,(((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg_q) 
                                  | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                      & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add)) 
                                     | ((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                          >> 1U) & 
                                         ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r) 
                                          & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__cnt0))) 
                                        | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                            >> 2U) 
                                           & (((~ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3)) 
                                               & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                  ^ (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0))) 
                                              | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                  >> 1U) 
                                                 & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__op_b) 
                                                    & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0)))))))) 
                                 & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en)) 
                                | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__csr_rd) 
                                    & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en)) 
                                   | ((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid)
                                         ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg2_q)
                                         : ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit) 
                                            & (~ ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3) 
                                                  >> 2U)))) 
                                       & (IData)((0U 
                                                  == 
                                                  (5U 
                                                   & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))))) 
                                      | (((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype) 
                                          & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bad_pc)) 
                                         | ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4) 
                                            & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr))))))));
        bufp->chgBit(oldp+346,(((0x10U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode))
                                 ? (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bad_pc)
                                 : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg_q))));
        bufp->chgBit(oldp+347,((1U & (~ (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0)))));
        bufp->chgBit(oldp+348,((1U & (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                      >> 1U))));
        bufp->chgBit(oldp+349,((1U & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel) 
                                      >> 1U))));
        bufp->chgBit(oldp+350,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__init_done));
        bufp->chgBit(oldp+351,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_csr__DOT__misalign_trap_sync_r));
        bufp->chgCData(oldp+352,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt),3);
        bufp->chgCData(oldp+353,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb),4);
        bufp->chgBit(oldp+354,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc));
        bufp->chgBit(oldp+355,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__take_branch));
        bufp->chgBit(oldp+356,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__last_init));
        bufp->chgBit(oldp+357,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending));
        bufp->chgBit(oldp+358,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__mux__DOT__sig_en));
        bufp->chgBit(oldp+359,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__mux__DOT__halt_en));
        bufp->chgBit(oldp+360,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__mux__DOT__sim_ack));
        bufp->chgBit(oldp+361,((0U != (vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                       >> 0x1eU))));
        bufp->chgBit(oldp+362,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rgnt));
        bufp->chgCData(oldp+363,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt),5);
        bufp->chgBit(oldp+364,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rtrig1));
        bufp->chgCData(oldp+365,((0x1fU & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt) 
                                           - (IData)(4U)))),5);
        bufp->chgCData(oldp+366,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r),2);
        bufp->chgCData(oldp+367,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r),3);
        bufp->chgBit(oldp+368,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wen0_r));
        bufp->chgBit(oldp+369,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__wen1_r));
        bufp->chgBit(oldp+370,((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))));
        bufp->chgCData(oldp+371,(((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                                   ? ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)
                                       ? 0x22U : (0x20U 
                                                  | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)))
                                   : ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)
                                       ? 0x23U : (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7)))),6);
        bufp->chgCData(oldp+372,(((1U & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rcnt))
                                   ? (((IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0) 
                                       << 5U) | ((0x1cU 
                                                  & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20) 
                                                     & ((- (IData)(
                                                                   (1U 
                                                                    & (~ (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                        << 2U))) 
                                                 | (3U 
                                                    & ((((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret) 
                                                         << 1U) 
                                                        | (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__trap)) 
                                                       | (((- (IData)((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en))) 
                                                           & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr)) 
                                                          | ((- (IData)(
                                                                        (1U 
                                                                         & (~ (IData)(vlSymsp->TOP__servant_sim__dut.cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0))))) 
                                                             & (IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20)))))))
                                   : (0x1fU & ((IData)(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20) 
                                               >> 4U)))),6);
        bufp->chgCData(oldp+373,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata0),2);
        bufp->chgBit(oldp+374,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rdata1));
        bufp->chgBit(oldp+375,(vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__rf_ram_if__DOT__rreq_r));
        bufp->chgCData(oldp+376,(vlSymsp->TOP__servant_sim__dut.__PVT__rf_ram__DOT__rdata),2);
        bufp->chgBit(oldp+377,(vlSymsp->TOP__servant_sim__dut.__PVT__rf_ram__DOT__regzero));
        bufp->chgCData(oldp+378,((vlSymsp->TOP__servant_sim__dut.__PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data 
                                  >> 0x1eU)),2);
        bufp->chgIData(oldp+379,(vlSymsp->TOP__servant_sim__dut.__PVT__timer__DOT__mtimecmp),32);
    }
    bufp->chgBit(oldp+380,(vlSelfRef.wb_clk));
    bufp->chgBit(oldp+381,(vlSelfRef.wb_rst));
    bufp->chgIData(oldp+382,(vlSelfRef.pc_adr),32);
    bufp->chgBit(oldp+383,(vlSelfRef.pc_vld));
    bufp->chgBit(oldp+384,(vlSelfRef.q));
}

void Vservant_sim___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vservant_sim___024root__trace_cleanup\n"); );
    // Init
    Vservant_sim___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vservant_sim___024root*>(voidSelf);
    Vservant_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
