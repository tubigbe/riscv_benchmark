// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vservant_sim.h for the primary calling header

#ifndef VERILATED_VSERVANT_SIM_SERVANT__MZ1_DZ2_S1_CZ3_AZ3_H_
#define VERILATED_VSERVANT_SIM_SERVANT__MZ1_DZ2_S1_CZ3_AZ3_H_  // guard

#include "verilated.h"
class Vservant_sim_servant_ram__D2000_R4d494e49;


class Vservant_sim__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3 final : public VerilatedModule {
  public:
    // CELLS
    Vservant_sim_servant_ram__D2000_R4d494e49* ram;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(__PVT__wb_clk,0,0);
        VL_IN8(__PVT__wb_rst,0,0);
        VL_OUT8(__PVT__q,0,0);
        CData/*0:0*/ __PVT__timer_irq;
        CData/*0:0*/ __PVT__wb_mem_stb;
        CData/*0:0*/ __PVT__wb_gpio_rdt;
        CData/*0:0*/ __PVT__wb_ext_stb;
        CData/*0:0*/ __PVT__wb_ext_ack;
        CData/*1:0*/ __PVT__rf_rdata;
        CData/*1:0*/ __PVT__rf_ram__DOT__rdata;
        CData/*0:0*/ __PVT__rf_ram__DOT__regzero;
        CData/*1:0*/ rf_ram__DOT____Vlvbound_h83862b22__0;
        CData/*0:0*/ __PVT__cpu__DOT__wb_dbus_stb;
        CData/*0:0*/ __PVT__cpu__DOT__rf_wreq;
        CData/*0:0*/ __PVT__cpu__DOT__rf_rreq;
        CData/*0:0*/ __PVT__cpu__DOT__wen0;
        CData/*0:0*/ __PVT__cpu__DOT__wdata0;
        CData/*0:0*/ __PVT__cpu__DOT__mux__DOT__sig_en;
        CData/*0:0*/ __PVT__cpu__DOT__mux__DOT__halt_en;
        CData/*0:0*/ __PVT__cpu__DOT__mux__DOT__sim_ack;
        CData/*0:0*/ cpu__DOT__mux__DOT____VdfgRegularize_h9ba68636_0_0;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rgnt;
        CData/*4:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rcnt;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rtrig1;
        CData/*1:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__wdata0_r;
        CData/*2:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__wdata1_r;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__wen0_r;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__wen1_r;
        CData/*1:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rdata0;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rdata1;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rgate;
        CData/*0:0*/ __PVT__cpu__DOT__rf_ram_if__DOT__rreq_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__csr_rd;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl_pc_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__jump;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__imm;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__trap;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__init;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt0;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt1;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt2;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt3;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt7;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__cnt_done;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg_q;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2_q;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__dbus_ack;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu_cmp;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__rs2;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__op_b;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__mem_misalign;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bad_pc;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__new_irq;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__wb_ibus_cyc;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__wb_ibus_ack;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__init_done;
        CData/*2:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__o_cnt;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__ibus_cyc;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__take_branch;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__last_init;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__trap_pending;
        CData/*3:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__gen_cnt_w_eq_1__DOT__cnt_lsb;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__state__DOT__gen_csr__DOT__misalign_trap_sync_r;
    };
    struct {
        CData/*0:0*/ cpu__DOT__cpu__DOT__state__DOT____VdfgRegularize_hdb06c6f3_1_3;
        CData/*4:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__opcode;
        CData/*2:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__funct3;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__op20;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__op21;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__op22;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__op26;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__imm25;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__imm30;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_two_stage_op;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_shift_op;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_dbus_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_alu_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_utype;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_jal_or_jalr;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_op;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_ctrl_mret;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_e_op;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_sub;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_rd_csr_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mstatus_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mie_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_mcause_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_imm_en;
        CData/*1:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_csr_addr;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_cmp_sig;
        CData/*3:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_immdec_ctrl;
        CData/*2:0*/ __PVT__cpu__DOT__cpu__DOT__decode__DOT__co_alu_rd_sel;
        CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_7;
        CData/*0:0*/ cpu__DOT__cpu__DOT__decode__DOT____VdfgRegularize_h350184cc_0_16;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm31;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm7;
        CData/*5:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm30_25;
        CData/*4:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm24_20;
        CData/*4:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm11_7;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__signbit;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg__DOT__q;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg__DOT__c_r;
        CData/*0:0*/ cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_0;
        CData/*0:0*/ cpu__DOT__cpu__DOT__bufreg__DOT____VdfgRegularize_hac22bbf5_0_1;
        CData/*7:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dhi;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__shift_en;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__cnt_en;
        CData/*7:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dat_shamt;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_4_cy_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__pc_plus_offset_cy_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_a;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__ctrl__DOT__offset_b;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu__DOT__result_add;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu__DOT__cmp_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu__DOT__add_cy_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__alu__DOT__add_b;
        CData/*0:0*/ cpu__DOT__cpu__DOT__rf_if__DOT____VdfgRegularize_ha3dbe366_0_0;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__mem_if__DOT__signbit;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__mem_if__DOT__dat_valid;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mie;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mstatus_mpie;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mie_mtie;
    };
    struct {
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause31;
        CData/*3:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__mcause3_0;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__csr_in;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq_r;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__d;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_csr__DOT__csr__DOT__timer_irq;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_rd;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mscratch;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtvec;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mepc;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mtval;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mstatus;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mie;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__update_mcause;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LUI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AUIPC;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JAL;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__JALR;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BEQ;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BNE;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLT;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGE;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BLTU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__BGEU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LB;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LH;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LW;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LBU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__LHU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SB;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SH;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SW;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADDI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTIU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XORI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ORI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ANDI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLLI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRLI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRAI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ADD;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SUB;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLL;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLT;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SLTU;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__XOR;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRL;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__SRA;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OR;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__AND;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__FENCE;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__ECALL;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__EBREAK;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRW;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRS;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRC;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRWI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRSI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__CSRRCI;
        CData/*0:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__OTHER;
        SData/*9:0*/ __PVT__rf_waddr;
        SData/*9:0*/ __PVT__rf_raddr;
        SData/*8:0*/ __PVT__cpu__DOT__cpu__DOT__immdec__DOT__gen_immdec_w_eq_1__DOT__imm19_12_20;
    };
    struct {
        IData/*31:0*/ __PVT__wb_mem_adr;
        IData/*31:0*/ __PVT__timer__DOT__mtime;
        IData/*31:0*/ __PVT__timer__DOT__mtimecmp;
        IData/*31:0*/ __PVT__cpu__DOT__wb_dbus_dat;
        IData/*31:0*/ __PVT__cpu__DOT__mux__DOT__genblk1__DOT__f;
        VlWide<32>/*1023:0*/ __PVT__cpu__DOT__mux__DOT__genblk1__DOT__signature_file;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__dbus_rdt;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__wb_ibus_adr;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg__DOT__data;
        IData/*23:0*/ __PVT__cpu__DOT__cpu__DOT__bufreg2__DOT__dlo;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_rd;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_csr;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mstatus;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mie;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mcause;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mscratch;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtvec;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mepc;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__dbg_mtval;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x1;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x2;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x3;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x4;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x5;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x6;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x7;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x8;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x9;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x10;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x11;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x12;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x13;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x14;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x15;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x16;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x17;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x18;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x19;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x20;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x21;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x22;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x23;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x24;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x25;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x26;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x27;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x28;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x29;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x30;
        IData/*31:0*/ __PVT__cpu__DOT__cpu__DOT__gen_debug__DOT__debug__DOT__x31;
        VlUnpacked<CData/*1:0*/, 576> __PVT__rf_ram__DOT__memory;
    };

    // INTERNAL VARIABLES
    Vservant_sim__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3(Vservant_sim__Syms* symsp, const char* v__name);
    ~Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3();
    VL_UNCOPYABLE(Vservant_sim_servant__Mz1_Dz2_S1_Cz3_Az3);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
