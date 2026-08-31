# RF Self-Loop Port Reference (Popcount v4)

## Overview

When `i_is_customized=1` and `i_init=1` (Stage 1 of the custom instruction), the RF write ports are re-targeted:

- **Port 0**: writes rs1 address (via ALU result from `o_wdata0` = `rd` mux containing `alu_rd`)
- **Port 1**: writes rs2 address (via raw rs2 value from `i_rdata1`)

When `i_init=0` (Stage 2), normal write path resumes (rd/CSR writes).

---

## rs1 Path (Address +4)

```
RF RAM read
  → i_rdata0 ──────────────────────────────────────────────┐
  → rf_if.o_rs1 (= rs1_raw)                                │ +4前
  → cus_alu.o_rs1 (passthrough during stage 1)              │
  → serv_alu.i_rs1                                          │
  → ALU computes rs1 + 4                                    │
  → serv_alu.o_rd (alu_rd)                          +4后    │
  → rf_if.i_alu_rd                                          │
  → rd mux: {i_rd_alu_en} & i_alu_rd | ...                  │
  → rf_if.o_wdata0 ────────────────────────────────────────┘
  → RF RAM write port 0 → rs1 address
```

### rs1 Port Names

| Signal | Module | Direction | Description |
|--------|--------|-----------|-------------|
| `i_rdata0` | `serv_rf_if.v` | input | Raw bit from RF RAM read port 0 |
| `o_rs1` | `serv_rf_if.v` | output | = `i_rdata0`, passes to downstream |
| `rs1_raw` | `serv_top.v` | wire | = `rf_if.o_rs1`, raw rs1 bit |
| `o_rs1` | `serv_customized_alu.v` | input | = `rs1_raw`, input to cus_alu |
| `rs1` | `serv_customized_alu.v` | output | cus_alu output → ALU input |
| `i_rs1` | `serv_alu.v` | input | = `cus_alu.rs1`, ALU operand |
| `o_rd` | `serv_alu.v` | output | ALU result (rs1+4) |
| `alu_rd` | `serv_top.v` | wire | = `serv_alu.o_rd` |
| `i_alu_rd` | `serv_rf_if.v` | input | = `alu_rd`, feeds rd mux |
| `o_wdata0` | `serv_rf_if.v` | output | Write data to RF RAM port 0 (carries `alu_rd` via `rd` mux) |
| `o_wreg0` | `serv_rf_if.v` | output | Write address = `{1'b0, i_rs1_raddr}` when self-loop active |
| `o_wen0` | `serv_rf_if.v` | output | Write enable = `cnt_en & 1` when self-loop active |

---

## rs2 Path (Constant Self-Loop)

```
RF RAM read
  → i_rdata1 ──────────────┐
  → rf_if.o_rs2 (= rs2)    │ rs2 output
  → [compare with rs1]     │
                           │
  → rf_if.o_wdata1 ────────┘ rs2 write-back (when is_customized & init)
  → RF RAM write port 1 → rs2 address
```

### rs2 Port Names

| Signal | Module | Direction | Description |
|--------|--------|-----------|-------------|
| `i_rdata1` | `serv_rf_if.v` | input | Raw bit from RF RAM read port 1 |
| `o_rs2` | `serv_rf_if.v` | output | = `i_rdata1`, passes to downstream |
| `rs2` | `serv_top.v` | wire | = `rf_if.o_rs2`, raw rs2 bit |
| `o_wdata1` | `serv_rf_if.v` | output | = `i_rdata1` when self-loop active, writes rs2 back |
| `o_wreg1` | `serv_rf_if.v` | output | Write address = `{1'b0, i_rs2_raddr}` when self-loop active |
| `o_wen1` | `serv_rf_if.v` | output | Write enable = `cnt_en & 1` when self-loop active |

---

## Control Signals

| Signal | Module | Direction | Description |
|--------|--------|-----------|-------------|
| `i_is_customized` | `serv_rf_if.v` | input | From `serv_top.v` wire `is_customized`, set by `serv_decode.v` |
| `i_init` | `serv_rf_if.v` | input | From `serv_top.v` wire `init`, from `serv_state.v` (1=Stage 1, 0=Stage 2) |

---

## Files Modified

| File | Change |
|------|--------|
| `serv_rf_if.v` | +2 input ports (`i_is_customized`, `i_init`); 4 output overrides (`o_wreg0`, `o_wreg1`, `o_wen0`, `o_wen1`, `o_wdata1`) in both WITH_CSR and gen_no_csr paths |
| `serv_top.v` | rf_if instance: +2 port connections (`.i_is_customized(is_customized)`, `.i_init(init)`) |

No changes to: `serv_rf_ram_if.v`, `serv_rf_ram.v`, `serv_customized_alu.v`
