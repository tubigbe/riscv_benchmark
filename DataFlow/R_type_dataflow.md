# SERV R-Type Instruction Data Flow Analysis

## R-Type Decoding Core Logic

R-type instructions (OP type) have opcode = `5'b01100` (`inst[6:2]`).

Key: `opcode[3] = 1`, so **`op_b_sel = 1` and the B operand selects rs2** (not the immediate).

```verilog
// serv_decode.v:237
wire co_op_b_source = opcode[3];  // R-type: opcode[3]=1 → selects rs2
```

The only difference between R-type and I-type is this single mux.

---

## Example 1: `and x1, x2, x3`

Encoding: `0000000_00011_00010_111_00001_0110011`

### Decoding Control Signals

| Control Signal | Derivation | Value | Meaning |
|----------------|-----------|-------|---------|
| `opcode` | `inst[6:2]` | `5'b01100` | OP type |
| `funct3` | `inst[14:12]` | `3'b111` | AND |
| `co_op_b_source` | `opcode[3]` | **1** | B operand = rs2 |
| `co_alu_bool_op` | `funct3[1:0]` | **2'b11** | AND boolean operation |
| `co_alu_rd_sel[2]` | `funct3[2]` | **1** | Select boolean result |
| `co_rd_alu_en` | `!opcode[0] & opcode[2] & !opcode[4] & !MDU` | **1** | ALU result written to rd |

### Data Flow (32 cycles, 1 bit per cycle)

```
Register File                  Register File
   rs1 ──────────→ serv_alu.i_rs1 ─┐
   rs2 ─→ serv_bufreg2 ─→ op_b ──→ │
              ↑                     │
         i_op_b_sel=1              │
        (selects rs2, not imm)      │
                                    ↓
                              result_bool
                              = i_rs1 & i_op_b
                                    │
                                    ↓
                              o_rd → rd writeback
```

### ALU Boolean Operation Detail

`serv_alu.v:65`:

```verilog
wire [B:0] result_bool = ((i_rs1 ^ i_op_b) & ~{W{i_bool_op[0]}}) 
                        | ({W{i_bool_op[1]}} & i_op_b & i_rs1);
```

When `i_bool_op = 2'b11`:
- First term: `(i_rs1 ^ i_op_b) & ~1 = 0`
- Second term: `1 & i_op_b & i_rs1 = i_rs1 & i_op_b`

So `result_bool = i_rs1 & i_op_b` — bitwise AND.

### Boolean Operation Truth Table

| funct3 | bool_op | Operation | result_bool |
|--------|---------|-----------|-------------|
| 100 (XOR) | 2'b00 | XOR | `i_rs1 ^ i_op_b` |
| 110 (OR)  | 2'b10 | OR  | `i_rs1 \| i_op_b` |
| 111 (AND) | 2'b11 | AND | `i_rs1 & i_op_b` |

### o_rd Output Selection

`serv_alu.v:74-77`:

```verilog
assign o_rd = i_buf | 
              ({W{i_rd_sel[0]}} & result_add) |    // and: rd_sel[0]=0, skip
              ({W{i_rd_sel[1]}} & result_slt) |    // and: rd_sel[1]=0, skip
              ({W{i_rd_sel[2]}} & result_bool);    // and: rd_sel[2]=1, selected!
```

---

## Example 2: `srl x1, x2, x3`

Encoding: `0000000_00011_00010_101_00001_0110011`

### Decoding Control Signals

| Control Signal | Derivation | Value | Meaning |
|----------------|-----------|-------|---------|
| `co_op_b_source` | `opcode[3]` | **1** | B operand = rs2 (shift amount) |
| `co_shift_op` | `opcode[2] & !funct3[1] & !MDU` | **1** | Shift operation |
| `co_sh_right` | `funct3[2]` | **1** | Right shift |
| `co_bufreg_sh_signed` | `imm30` (funct7[5]) | **0** | Logical right shift (fill 0) |
| `co_alu_bool_op` | `funct3[1:0]` | **2'b01` | Output 0 (shift-dedicated) |

### Key Insight: Shifts Are NOT Computed by the ALU

SERV is a bit-serial processor with no barrel shifter. Shifts are implemented by **physically right-shifting the bufreg data register** — each clock cycle shifts `data[31:2]` right by one bit, discarding the LSB and filling the MSB with 0 (srl) or the sign bit (sra).

The ALU's role during shifts is **pass-through only** (forwarding `bufreg_q` to `o_rd`).

### Full Data Flow

#### Phase 1 — Init (32 cycles): Load rs1 into bufreg

```
Register File
  rs1 (x2) ──→ serv_bufreg.i_rs1 ──→ adder ──→ data[31:0] shifted in
              (bufreg_rs1_en=1)
              (bufreg_imm_en=0, no immediate added)
```

`serv_bufreg.v:64`:

```verilog
data[31:2] <= {i_init ? q : {W{data[31] & i_sh_signed}}, data[31:3]};
//            ↑ init: load adder output    ↑ non-init: right-shift + sign extend
```

Meanwhile, `serv_bufreg2` loads the shift amount (rs2) into the `dhi[5:0]` counter during init.

#### Phase 2 — Right-shift phase: Physical right-shift of bufreg

After init completes, `serv_state` keeps `bufreg_en` active (`serv_state.v:139`):

```verilog
o_bufreg_en = ... | (i_shift_op & init_done & (i_sh_right | i_sh_done));
```

Each cycle, bufreg's data register shifts right by one bit:

```verilog
// srl: sh_signed=0, fill MSB with 0
data[31:2] <= {1'b0, data[31:3]};
data[1:0]  <= {data[2], data[1]};
```

`serv_bufreg2`'s counter decrements by 1 each cycle. When it reaches 0, `o_sh_done = 1`.

#### Phase 3 — Writeback

`serv_state.v:114`:

```verilog
o_rf_wreq = (i_shift_op & (i_sh_right ? (i_sh_done & (last_init | !o_cnt_en & init_done)) : last_init)) | ...;
```

The right-shifted result is output from `bufreg.o_q` → enters `serv_alu.i_buf`.

### ALU's Role During Shifts

```verilog
// serv_alu.v:65
result_bool = ((i_rs1 ^ i_op_b) & ~1) | (1 & i_op_b & i_rs1);
//            ↑ cleared to 0              ↑ bool_op=01, outputs 0
// result_bool = 0

// serv_alu.v:74-77
o_rd = i_buf | (0 & result_add) | (0 & result_slt) | (0 & result_bool);
//    = i_buf    // ALU only does one thing: pass bufreg_q through
```

`i_buf` is connected to `bufreg_q` (`serv_top.v:479`). **ALU's o_rd = bufreg_q** — the ALU itself performs no computation.

### srl Data Flow Summary

```
                Phase 1 (init)              Phase 2 (right-shift)
                ─────────────              ─────────────────────
Register File   rs1 ──→ bufreg.data         bufreg.data physically shifted
  rs2 ──→ bufreg2.dhi[5:0] (shift counter)  counter decrements
                                      │
                                      ↓ sh_done
                                      │
              bufreg.o_q ──→ serv_alu.i_buf ──→ alu.o_rd (= i_buf)
                                                      │
                                              rf_if.rd = alu_rd (rd_alu_en=1)
                                                      │
                                              o_wdata0 ──→ register file writeback to rd
```

---

## R-Type vs I-Type Core Differences

| | R-type (`and`, `add`) | I-type (`andi`, `addi`) |
|---|---|---|
| `op_b_sel` | `opcode[3]=1` → **rs2** | `opcode[3]=0` → **imm** |
| B operand source | Register file | Immediate decoder |
| Boolean op | `i_rs1 & i_rs2` | `i_rs1 & imm` |
| ALU uses same logic | Yes | Yes |

| | R-type (`srl`, `sll`) | I-type (`srli`, `slli`) |
|---|---|---|
| `op_b_sel` | 1 → **rs2** (shift amount) | 0 → **imm** (shift amount) |
| Shift amount source | rs2 register | Immediate `inst[24:20]` |
| Shift implementation | bufreg physical shift | bufreg physical shift |

---

## Key File References

| File | Lines | Content |
|------|-------|---------|
| `serv_decode.v` | 237 | `co_op_b_source = opcode[3]` |
| `serv_decode.v` | 86 | `co_shift_op = (opcode[2] & !funct3[1]) & !MDU` |
| `serv_decode.v` | 133 | `co_sh_right = funct3[2]` |
| `serv_decode.v` | 153 | `co_bufreg_sh_signed = imm30` |
| `serv_decode.v` | 212 | `co_alu_bool_op = funct3[1:0]` |
| `serv_decode.v` | 231-233 | `co_alu_rd_sel` |
| `serv_decode.v` | 91 | `co_rd_alu_en` |
| `serv_alu.v` | 43-45 | Adder |
| `serv_alu.v` | 65 | Boolean operations (XOR/OR/AND) |
| `serv_alu.v` | 74-77 | o_rd output mux |
| `serv_bufreg.v` | 52 | rs1+imm adder |
| `serv_bufreg.v` | 64 | data register load/shift |
| `serv_bufreg.v` | 70 | `o_q = data[0]` output |
| `serv_bufreg2.v` | 54 | op_b mux |
| `serv_bufreg2.v` | 76 | Shift amount counter `cnt_next` |
| `serv_bufreg2.v` | 88 | `o_sh_done = dat_shamt[5]` |
| `serv_state.v` | 114 | `o_rf_wreq` shift writeback trigger |
| `serv_state.v` | 139 | `o_bufreg_en` bufreg enable |
| `serv_rf_if.v` | 66-70 | rd writeback mux |
| `serv_top.v` | 477-480 | alu instantiation (i_buf = bufreg_q) |
