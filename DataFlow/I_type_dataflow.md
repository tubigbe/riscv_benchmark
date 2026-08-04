# SERV I-Type Instruction Data Flow Analysis

## What is i_op_b?

`i_op_b` is the ALU's second operand input (B operand). SERV is a bit-serial processor, so it transfers only 1 bit per clock cycle (in the default `W=1` configuration, it is a 1-bit wire).

It is driven by a mux in `serv_bufreg2` that selects between the `rs2` register value and the immediate value:

```verilog
// serv_bufreg2.v:54
assign o_op_b = i_op_b_sel ? i_rs2 : i_imm;
```

The `op_b_sel` signal comes directly from the decoder via `opcode[3]` (`serv_decode.v:237`):

```verilog
wire co_op_b_source = opcode[3];
// 0 (OP_B_SOURCE_IMM) when OPIMM
// 1 (OP_B_SOURCE_RS2) when BRANCH or OP
```

For I-type instructions (OP-IMM, LOAD, STORE), `opcode[3] == 0`, so **`op_b_sel = 0` and the B operand selects the immediate**.

---

## I-Type Decoding Control Signals

Example: `addi x5, x6, 42` — encoding: `000000101010_00110_000_00101_0010011`

| Control Signal | Derivation | Value | Meaning |
|----------------|-----------|-------|---------|
| `opcode` | `inst[6:2]` | `5'b00100` | OP-IMM type |
| `funct3` | `inst[14:12]` | `3'b000` | ADDI |
| `co_op_b_source` | `opcode[3]` | **0** | B operand = imm |
| `co_rd_alu_en` | `!opcode[0] & opcode[2] & !opcode[4] & !MDU` | **1** | ALU result written to rd |
| `co_alu_rd_sel[0]` | `funct3 == 3'b000` | **1** | Select adder result |

ALU control for different I-type subtypes:

| Instruction | funct3 | alu_rd_sel | ALU Path |
|-------------|--------|------------|----------|
| addi | 000 | [0]=1 | Adder (result_add) |
| slti | 010 | [1]=1 | Less-than comparison (result_slt) |
| sltiu | 011 | [1]=1 | Unsigned comparison |
| xori | 100 | [2]=1 | Boolean XOR |
| ori | 110 | [2]=1 | Boolean OR |
| andi | 111 | [2]=1 | Boolean AND |
| slli | 001 | shift_op=1 | Shift (via bufreg) |
| srli/srai | 101 | shift_op=1 | Shift (via bufreg) |

---

## I-Type Immediate Full Data Flow Path

### Step 1: Instruction Fetch

The instruction word arrives on `i_wb_rdt` and is received by both `serv_decode` and `serv_immdec` simultaneously.

### Step 2: Immediate Latch (serv_immdec)

`serv_immdec.v:52-66` latches the immediate fields from the instruction:

```verilog
imm31       <= i_wb_rdt[31];                      // Sign bit
imm19_12_20 <= {i_wb_rdt[19:12], i_wb_rdt[20]};  // Bits 19:12 and bit 20
imm30_25    <= i_wb_rdt[30:25];                   // Bits 30:25
imm24_20    <= i_wb_rdt[24:20];                   // Bits 24:20
imm11_7     <= i_wb_rdt[11:7];                    // Bits 11:7 (also rd address)
```

For I-type, the immediate is the 12-bit field `inst[31:20]`, which gets sign-extended to 32 bits.

### Step 3: Bit-Serial Output (32 cycles)

The control signal `co_immdec_ctrl[1]` is set to 1 for I-type (`serv_decode.v:220`):

```verilog
assign co_immdec_ctrl[1] = (opcode[1:0] == 2'b00) | (opcode[2:1] == 2'b00);
// OP-IMM: opcode=00100, opcode[1:0]=00 → 1
```

One bit is emitted per cycle on `o_imm` (`serv_immdec.v:100`):

```verilog
assign o_imm = i_cnt_done ? signbit : i_ctrl[0] ? imm11_7[0] : imm24_20[0];
```

### Step 4: Mux Selects Immediate

`serv_bufreg2.v:54`:

```verilog
assign o_op_b = i_op_b_sel ? i_rs2 : i_imm;
// i_op_b_sel = 0 (I-type) → selects i_imm
```

The immediate bit passes through `o_op_b` into the ALU.

### Step 5: ALU Computation

For `addi`, `serv_alu.v:43-45`:

```verilog
wire [B:0] add_b = i_op_b^{W{i_sub}};  // i_sub=0 for addi, add_b = i_op_b
assign {add_cy, result_add} = i_rs1 + add_b + add_cy_r;  // 1-bit addition
```

For `andi`, `serv_alu.v:65`:

```verilog
result_bool = ((i_rs1 ^ i_op_b) & ~{W{i_bool_op[0]}}) | ({W{i_bool_op[1]}} & i_op_b & i_rs1);
// i_bool_op = 2'b11 (AND) → result_bool = i_rs1 & i_op_b
```

### Step 6: Writeback to rd

The ALU result flows through `serv_rf_if.v:66-70`:

```verilog
wire [B:0] rd = {W{i_rd_alu_en}} & i_alu_rd | ...;  // rd_alu_en=1, selects ALU result
assign o_wdata0 = i_trap ? mtval : rd;              // Written to register file
```

---

## LOAD Instruction Special Path

For I-type LOAD instructions (`lw`, `lb`, etc.):

- The immediate is used for **address computation** (in `serv_bufreg`, computing `rs1 + imm`)
- The ALU is not directly in the data path
- `serv_bufreg.v:52`: `{c, q} = {1'b0, (i_rs1 & {W{i_rs1_en}})} + {1'b0, (i_imm & {W{i_imm_en}} & ~clr_lsb)} + c_r`
- Memory read data is formatted by `serv_mem_if` and written directly to rd
- `co_rd_mem_en = (!opcode[2] & !opcode[0]) = 1`, `co_rd_alu_en = 0`

---

## Key Signal Connection Table

| Signal | Driven by | Consumed by | Purpose |
|--------|-----------|-------------|---------|
| `op_b` (`serv_top.v:154`) | `serv_bufreg2.o_op_b` | `serv_alu.i_op_b` | ALU second operand |
| `op_b_sel` (`serv_top.v:155`) | `serv_decode.o_op_b_source` | `serv_bufreg2.i_op_b_sel` | 0=imm, 1=rs2 |
| `imm` (`serv_top.v:114`) | `serv_immdec.o_imm` | `serv_bufreg.i_imm`, `serv_bufreg2.i_imm` | Bit-serial immediate |
| `rs1` (`serv_top.v:150`) | `serv_rf_if.o_rs1` | `serv_alu.i_rs1`, `serv_bufreg.i_rs1` | Register source 1 |
| `alu_rd` (`serv_top.v:104`) | `serv_alu.o_rd` | `serv_rf_if.i_alu_rd` | ALU result → rd |
| `rd_alu_en` (`serv_top.v:100`) | `serv_decode.o_rd_alu_en` | `serv_rf_if.i_rd_alu_en` | Gate ALU result into rd |

---

## Key File References

| File | Lines | Content |
|------|-------|---------|
| `serv_top.v` | 154-155 | op_b / op_b_sel declaration |
| `serv_top.v` | 407-430 | bufreg2 instantiation |
| `serv_top.v` | 463-480 | alu instantiation |
| `serv_alu.v` | 27 | i_op_b port |
| `serv_alu.v` | 43-45 | Adder uses i_op_b |
| `serv_alu.v` | 65 | Boolean op uses i_op_b |
| `serv_alu.v` | 74-77 | o_rd output mux |
| `serv_bufreg2.v` | 54 | op_b mux: `i_op_b_sel ? i_rs2 : i_imm` |
| `serv_decode.v` | 237 | `co_op_b_source = opcode[3]` |
| `serv_decode.v` | 91 | `co_rd_alu_en` |
| `serv_decode.v` | 231-233 | `co_alu_rd_sel` |
| `serv_decode.v` | 212 | `co_alu_bool_op = funct3[1:0]` |
| `serv_immdec.v` | 52-66 | Immediate field latching |
| `serv_immdec.v` | 100 | `o_imm` serial output |
| `serv_rf_if.v` | 66-70 | rd writeback mux |
