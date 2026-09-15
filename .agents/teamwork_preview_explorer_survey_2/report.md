# Survey Report: Random Forest Unification & Cross-Benchmark Comparison (R2 Preparation)

**Author**: `teamwork_preview_explorer`  
**Working Directory**: `/home/chenyoo/riscv_benchmark/.agents/teamwork_preview_explorer_survey_2/`  
**Date**: 2026-09-13  
**Target Milestone**: R2 (C Code Macro Unification for Random Forest)  
**Reference Document**: `/home/chenyoo/riscv_benchmark/ORIGINAL_REQUEST.md`

---

## 1. Executive Summary

This report provides a comprehensive, rigorous investigation of the C codebase for **Random Forest** and its comparison with **BNN (Binarized Neural Network)** and **Tsetlin Machine**, specifically addressing Requirement **R2** of the SERV ML Benchmarks project.

### Core Discoveries:
1. **File Inventory & Equivalence**:
   - `Codespace/SERV_codespace/random_forest/` contains 10 files; `Codespace/SERV_codespace/rf_v2_lucky/` contains 8 files.
   - 7 files are **byte-for-byte identical** between the two directories (`RF_model.c`, `RF_model.h`, `infer_one.h`, `main.c`, `samples.c`, `samples.h`, `startup.S`).
   - `compile.sh` and `predicted_class.txt` exist only in `random_forest/`.
   - **`infer_one.c` is the single file with code differences**.
2. **Popcount Mechanics**:
   - `random_forest/infer_one.c` computes popcount via `static unsigned int popcnt_sw(unsigned int x)` using a bit-serial shift loop (`while(x) { c += x & 1; x >>= 1; }`). It takes 526,208 total simulation cycles (9,013 instructions).
   - `rf_v2_lucky/infer_one.c` computes popcount via `volatile static unsigned int popcnt_custom(unsigned int val)` emitting the custom hardware instruction `.insn r 0x2B, 0, 0, %0, %1, x0`. On SERV v1.5 RTL (`v1.5_lucky`), it executes in exactly 42 cycles with zero follower stall, taking 492,928 total simulation cycles (8,381 instructions). The custom instruction saves 33,280 cycles across 20 invocations (~1,664 cycles per software call vs 42 cycles in hardware, a **39.6x speedup** on popcount).
3. **Macro & Assembly Conventions in BNN and Tsetlin Machine**:
   - Both `BNN/helpers.c` and `Tsetin_Machine/class_sum.c` use `#ifdef USE_CUSTOM_POPCOUNT` to switch between hardware inline assembly and a software fallback.
   - All implementations share the exact same R-type opcode and operand format: `.insn r 0x2B, 0, 0, %0, %1, x0` (custom-0 opcode `0101011`, funct3=0, funct7=0, rs2=x0).
   - `Tsetin_Machine/class_sum.c` uses `static inline unsigned int popcnt(unsigned int val)`, which is the cleanest, most efficient signature.
   - `BNN` and `Tsetlin Machine` use Brian Kernighan's algorithm (`v &= v - 1; count++;`) for their software fallbacks.
4. **Freestanding rv32i Compliance**:
   - Neither `random_forest` nor `rf_v2_lucky` contains hosted headers like `<stdio.h>`, `<stdlib.h>`, or unresolved host symbols. Both include only `<stdint.h>` in `main.c` (a standard freestanding compiler header).
   - `startup.S` in `random_forest` is identical to `build_codes/startup.S` and provides the exact stack setup (`sp=8192`), GPIO initialization, and halt write (`0x90000000`).
5. **Clear Unification & Deprecation Path**:
   - `infer_one.c` can be unified into a single file with `#ifdef USE_CUSTOM_POPCOUNT` in `random_forest/infer_one.c`, exposing `static inline unsigned int popcnt(unsigned int val)`.
   - `rf_v2_lucky` is completely redundant once `random_forest` is unified; it can be marked deprecated via a deprecation notice and archived safely without affecting any build flows.

---

## 2. File-by-File Comparison: `random_forest/` vs `rf_v2_lucky/`

### 2.1 Complete Directory Inventory

| File Name | `random_forest/` Size | `rf_v2_lucky/` Size | `cmp` / Difference Result | Description & Role |
|---|---|---|---|---|
| `RF_model.c` | 2,588 bytes | 2,588 bytes | **Identical** (0 diff) | Array `trees[][4]` storing decision tree nodes (feature, threshold, left, right). |
| `RF_model.h` | 110 bytes | 110 bytes | **Identical** (0 diff) | Header defining `TREES 10` and `extern int trees[][4];`. |
| `infer_one.h` | 114 bytes | 114 bytes | **Identical** (0 diff) | Header declaring `int infer_one(const int *x);`. |
| `samples.c` | 259 bytes | 259 bytes | **Identical** (0 diff) | Test dataset `raw_samples[10][4]` containing 10 test samples with 4 features each. |
| `samples.h` | 159 bytes | 159 bytes | **Identical** (0 diff) | Header defining `no_samples 10`, `CLASSES 3`, `RAW_FEATURES 4`, and `raw_samples` declaration. |
| `main.c` | 305 bytes | 305 bytes | **Identical** (0 diff) | Benchmark entry point iterating over samples and storing predictions in `result_array`. |
| `startup.S` | 970 bytes | 970 bytes | **Identical** (0 diff) | Startup assembly: sets `sp=8192`, raises GPIO, calls `main`, loops on `0x90000000`. |
| `infer_one.c` | 2,389 bytes | 2,244 bytes | **Differing** (see 2.2) | Tree traversal and class vote aggregation via popcount. |
| `compile.sh` | 1,967 bytes | *Absent* | **Only in `random_forest`** | Legacy compile script (`rv32e`, `/opt/riscv/bin/riscv64-unknown-elf-gcc`). |
| `predicted_class.txt` | 20 bytes | *Absent* | **Only in `random_forest`** | Ground truth class labels for the 10 samples: `2, 2, 1, 2, 2, 2, 2, 0, 0, 1`. |

### 2.2 Detailed Diff of `infer_one.c`

A unified diff between `Codespace/SERV_codespace/random_forest/infer_one.c` and `Codespace/SERV_codespace/rf_v2_lucky/infer_one.c` reveals:

```diff
--- Codespace/SERV_codespace/random_forest/infer_one.c
+++ Codespace/SERV_codespace/rf_v2_lucky/infer_one.c
@@ -1,22 +1,18 @@
 #include "infer_one.h"
 
-// Software popcount (standard RV32I): count set bits by looping.
-// v1 counterpart of the custom popcount instruction used in v2 —
-// the two infer_one implementations are otherwise identical.
-static unsigned int popcnt_sw(unsigned int x)
+// Custom popcount instruction: rd = number of set bits in val
+volatile static unsigned int popcnt_custom(unsigned int val)
 {
-    unsigned int c = 0;
-    while (x) {
-        c += x & 1;
-        x >>= 1;
-    }
-    return c;
+    unsigned int rd;
+    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
+                 : "=r"(rd) : "r"(val));
+    return rd;
 }
 
 // Returns prediction for one datapoint
 int infer_one(const int *x)
 {
-    // Each tree's class vote (0..CLASSES-1) is packed into a 2-bit field
+    // Each tre e's class vote (0..CLASSES-1) is packed into a 2-bit field
     // of a 32-bit word. CLASSES=3 -> 2 bits/vote; TREES=10 -> 20 bits, fits.
     unsigned int packed_votes = 0;
     int vote_count = 0;
@@ -57,15 +53,14 @@
             row = right + row;
     }
 
-    // Majority vote using the software popcount (v2 uses the custom
-    // popcount instruction for exactly the same masks).
+    // Majority vote using the custom popcount instruction.
     // In each 2-bit field: 00 = class 0, 01 = class 1, 10 = class 2.
     unsigned int lo = packed_votes & 0x55555555;         // low bit of each field
     unsigned int hi = (packed_votes >> 1) & 0x55555555;  // high bit of each field
 
     // count1 = fields equal to 01, count2 = fields equal to 10
-    unsigned int count1 = popcnt_sw(lo & ~hi);
-    unsigned int count2 = popcnt_sw(hi & ~lo);
+    unsigned int count1 = popcnt_custom(lo & ~hi);
+    unsigned int count2 = popcnt_custom(hi & ~lo);
     unsigned int count0 = (unsigned int)vote_count - count1 - count2;
 
     int best_class = 0, best_count = (int)count0;
```

#### Key Differences:
1. **Popcount implementation**:
   - `random_forest`: Defines `static unsigned int popcnt_sw(unsigned int x)` with a bit shift loop.
   - `rf_v2_lucky`: Defines `volatile static unsigned int popcnt_custom(unsigned int val)` with inline assembly `.insn r 0x2B, 0, 0, %0, %1, x0`.
2. **Call sites**:
   - `random_forest`: Calls `popcnt_sw(lo & ~hi)` and `popcnt_sw(hi & ~lo)`.
   - `rf_v2_lucky`: Calls `popcnt_custom(lo & ~hi)` and `popcnt_custom(hi & ~lo)`.
3. **Minor comment differences**:
   - Line 15 in `rf_v2_lucky` has a minor typo: `"// Each tre e's class vote"` (extra space) vs `"// Each tree's class vote"` in `random_forest`.
   - Line 56 in `rf_v2_lucky` updates the comment to reflect custom popcount instruction usage.

---

## 3. Popcount Implementations in `infer_one.c` (SW vs HW)

### 3.1 Random Forest Vote Encoding & Popcount Role

In both implementations:
- 10 trees (`TREES=10`) evaluate the input features for 3 possible classes (`CLASSES=3`, labels 0, 1, 2).
- Each tree's vote is represented in 2 bits:
  - `00` (0): Class 0
  - `01` (1): Class 1
  - `10` (2): Class 2
- The 10 votes are shifted and packed into bits `0..19` of `packed_votes` (`packed_votes |= (unsigned int)cls << (2 * vote_count);`).
- To find the majority class, the algorithm separates the low and high bits of each 2-bit field:
  ```c
  unsigned int lo = packed_votes & 0x55555555;         // low bit of each field
  unsigned int hi = (packed_votes >> 1) & 0x55555555;  // high bit of each field
  ```
- The votes are then extracted via popcount:
  - Votes for Class 1 (`01`): `lo & ~hi` has a 1-bit where the field was `01`. `count1 = popcount(lo & ~hi)`.
  - Votes for Class 2 (`10`): `hi & ~lo` has a 1-bit where the field was `10`. `count2 = popcount(hi & ~lo)`.
  - Votes for Class 0 (`00`): `count0 = vote_count - count1 - count2`.
- Finally, argmax selects the class with the highest vote count (`best_class`).

### 3.2 Software Popcount in `random_forest/infer_one.c`

```c
static unsigned int popcnt_sw(unsigned int x)
{
    unsigned int c = 0;
    while (x) {
        c += x & 1;
        x >>= 1;
    }
    return c;
}
```

- **Mechanism**: Loops while `x != 0`. On each iteration:
  - Masks the lowest bit with `x & 1`.
  - Accumulates it into `c`.
  - Shifts `x` right by 1 (`x >>= 1`).
- **Iteration Count**: Depends on the highest set bit in `x`. For Random Forest, votes occupy up to bit 19, so the loop can iterate up to 20 times per call.
- **Instruction Overhead**: When compiled with `-O2`, GCC inlines this loop into basic blocks using `andi`, `add`, `srli`, and conditional branch `bnez`. On SERV's bit-serial architecture, every `srli` and branch requires multiple cycles (e.g. `srli` is ~69 cycles, `bnez` is ~68 cycles).
- **Execution Cost**:
  - Total instructions in simulation: **9,013**
  - Total simulation cycles: **526,208** (verified from `serv_project/log/compare_origin_sw.txt` and `A_v1_origin.txt`).

### 3.3 Hardware Popcount in `rf_v2_lucky/infer_one.c`

```c
volatile static unsigned int popcnt_custom(unsigned int val)
{
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
}
```

- **Mechanism**: Directly executes the custom popcount instruction supported by the SERV customized ALU (`serv_customized_alu.v`) and top-level datapath (`serv_top.v`).
- **Opcode Encoding**:
  - `.insn r 0x2B, 0, 0, %0, %1, x0`
  - Opcode `0x2B` (`0101011` in binary, RISC-V custom-0).
  - Funct3 = `0`, Funct7 = `0`.
  - Source register 1 (`rs1`) = input `%1` (`val`).
  - Source register 2 (`rs2`) = `x0` (zero register).
  - Destination register (`rd`) = output `%0` (`rd`).
- **Execution Cycles on SERV v1.5 RTL (`v1.5_lucky`)**:
  - **Stage 1 (32 cycles)**: The 32-bit `rs1` is shifted through `cus_alu`, which accumulates set bits into a 6-bit counter `pr_partial[5:0]`. Simultaneously, `o_wdata0` is forced to `0` and `o_wen0=1`, clearing `rd` in the register file.
  - **Stage 2 (6 cycles)**: Shifts the 6-bit result from `pr_partial` into `rd` via `o_serial`.
  - **In-Window Writeback**: Writeback finishes completely inside the instruction's own window. Zero follower stall (follower instructions run at full speed, e.g. `not` takes 36 cycles, `sw` takes 70 cycles).
  - **Instruction Latency**: Fixed **42 cycles** per popcount.
- **Execution Cost**:
  - Total instructions in simulation: **8,381**
  - Total simulation cycles: **492,928** (verified from `serv_project/log/C_v2_popcount_v15lucky.txt`).

### 3.4 Quantitative Comparison & Speedup Analysis

From the official simulation traces on SERV v1.5 RTL (`fusesoc_libraries/serv_v1.5_rtl`):

| Metric | Software Popcount (`random_forest`) | Hardware Popcount (`rf_v2_lucky`) | Absolute Delta | Relative Change |
|---|---|---|---|---|
| Total Simulated Instructions | 9,013 | 8,381 | −632 instructions | −7.01% |
| Popcount Instructions Executed | 0 (inlined loops) | 20 (`.insn`) | +20 | N/A |
| Total Simulation Cycles | 526,208 | 492,928 | **−33,280 cycles** | **−6.33% total runtime** |
| Cycles per Popcount Call | ~1,664 cycles (avg) | **42 cycles (exact)** | −1,622 cycles | **39.6x speedup on popcount** |

*Analysis*: Over 10 inference samples, popcount is called exactly 20 times (2 calls per sample). The software bit-serial shift loop required 33,280 cycles across those 20 calls, averaging 1,664 cycles per call. Replacing this loop with the 42-cycle custom instruction reduces the overall benchmark runtime by 33,280 cycles.

---

## 4. Cross-Benchmark Survey: BNN & Tsetlin Machine Conventions

To ensure complete architectural consistency across the three benchmarks, we inspected `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/BNN/helpers.c` and `/home/chenyoo/riscv_benchmark/Codespace/SERV_codespace/Tsetin_Machine/class_sum.c`.

### 4.1 BNN Popcount Implementation (`BNN/helpers.c`)

Lines 36–52:
```c
int popcount32(int32_t x) {
#ifdef USE_CUSTOM_POPCOUNT
    int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(x));
    return rd;
#else
    /* Software fallback: iterate once per set bit. */
    int count = 0;
    uint32_t v = (uint32_t)x;
    while (v) {
        v &= v - 1;   /* clear the lowest set bit */
        count++;
    }
    return count;
#endif
}
```

- **Function Name**: `popcount32`
- **Linkage**: Non-static extern function.
- **Parameters & Return**: `int popcount32(int32_t x)`. Uses signed 32-bit types, internally casts to `uint32_t` for the software loop.
- **Macro Guard**: `#ifdef USE_CUSTOM_POPCOUNT`
- **Inline Assembly**: Identical `.insn r 0x2B, 0, 0, %0, %1, x0`.
- **Software Fallback**: Brian Kernighan's bit-clearing loop (`v &= v - 1; count++;`).

### 4.2 Tsetlin Machine Popcount Implementation (`Tsetin_Machine/class_sum.c`)

Lines 19–34:
```c
static inline unsigned int popcnt(unsigned int val)
{
#ifdef USE_CUSTOM_POPCOUNT
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
#else
    unsigned int n = 0;
    while (val) {
        val &= val - 1;   /* clear the lowest set bit */
        n++;
    }
    return n;
#endif
}
```

- **Function Name**: `popcnt`
- **Linkage**: `static inline`.
- **Parameters & Return**: `static inline unsigned int popcnt(unsigned int val)`. Uses unsigned integer types.
- **Macro Guard**: `#ifdef USE_CUSTOM_POPCOUNT`
- **Inline Assembly**: Identical `.insn r 0x2B, 0, 0, %0, %1, x0`.
- **Software Fallback**: Brian Kernighan's bit-clearing loop (`val &= val - 1; n++;`).

### 4.3 Side-by-Side Comparison of Popcount Conventions

| Characteristic | `BNN/helpers.c` | `Tsetin_Machine/class_sum.c` | `random_forest/infer_one.c` (Current) | `rf_v2_lucky/infer_one.c` (Current) | Recommended Unified `infer_one.c` |
|---|---|---|---|---|---|
| **Macro Name** | `USE_CUSTOM_POPCOUNT` | `USE_CUSTOM_POPCOUNT` | None | None | `USE_CUSTOM_POPCOUNT` |
| **Function Identifier** | `popcount32` | `popcnt` | `popcnt_sw` | `popcnt_custom` | `popcnt` |
| **Linkage** | Extern | `static inline` | `static` | `volatile static` | `static inline` |
| **Return Type** | `int` | `unsigned int` | `unsigned int` | `volatile unsigned int` | `unsigned int` |
| **Argument Type** | `int32_t x` | `unsigned int val` | `unsigned int x` | `unsigned int val` | `unsigned int val` |
| **Custom Assembly** | `.insn r 0x2B, 0, 0, %0, %1, x0` | `.insn r 0x2B, 0, 0, %0, %1, x0` | N/A | `.insn r 0x2B, 0, 0, %0, %1, x0` | `.insn r 0x2B, 0, 0, %0, %1, x0` |
| **Operand Mappings** | `"=r"(rd) : "r"(x)` | `"=r"(rd) : "r"(val)` | N/A | `"=r"(rd) : "r"(val)` | `"=r"(rd) : "r"(val)` |
| **SW Algorithm** | Kernighan (`v &= v - 1`) | Kernighan (`val &= val - 1`) | Shift (`x >>= 1`) | N/A | Shift (`val >>= 1`) *(see 4.4)* |
| **Freestanding Headers** | `<stdint.h>`, `<stddef.h>` | `<limits.h>` | `"infer_one.h"` | `"infer_one.h"` | `"infer_one.h"` |

### 4.4 Analysis of Software Fallback: Shift Loop vs Kernighan's Algorithm

An important design choice in unifying `infer_one.c` is whether the `#else` software branch should keep the original shift loop (`while (val) { c += val & 1; val >>= 1; }`) or adopt Kernighan's algorithm (`while (val) { val &= val - 1; c++; }`):

1. **Option A — Preserve Original Shift Loop (Recommended)**:
   - *Rationale*: All historical baseline measurements (`serv_project/log/compare_origin_sw.txt`, `A_v1_origin.txt`) were generated using this exact shift loop, yielding exactly **526,208 cycles**.
   - Preserving it ensures 100% cycle-reproducibility against the historical baseline when running without `--popcount`.
2. **Option B — Adopt Kernighan's Algorithm**:
   - *Rationale*: Matches the exact algorithmic pattern in `BNN` and `Tsetlin Machine`.
   - *Tradeoff*: Reduces software popcount iterations from $M$ (highest bit index $\le 20$) to $K$ (number of 1-bits $\le 10$). This would alter the software cycle count and cause a slight delta against `compare_origin_sw.txt`.

**Recommendation**: Retain the original shift loop in `random_forest/infer_one.c` for exact baseline cycle fidelity, or provide an annotated comment acknowledging both.

---

## 5. Header Inclusions & Freestanding rv32i Compliance Audit

A complete audit of all source files in `random_forest/`, `rf_v2_lucky/`, `BNN/`, and `Tsetin_Machine/` was conducted to verify freestanding compliance.

### 5.1 Standards for Freestanding RISC-V Compilation
In freestanding mode (`-ffreestanding -nostdlib -nostartfiles`):
- Standard C runtime libraries (`libc`) are absent. Any call to `printf`, `malloc`, `exit`, etc., or inclusion of hosted headers like `<stdio.h>`, `<stdlib.h>`, `<unistd.h>` will fail at link time or pull in undefined host symbols.
- The compiler guarantees the presence of standard freestanding headers: `<float.h>`, `<iso646.h>`, `<limits.h>`, `<stdalign.h>`, `<stdarg.h>`, `<stdbool.h>`, `<stddef.h>`, `<stdint.h>`, `<stdnoreturn.h>`.

### 5.2 Header Audit by Benchmark

#### Random Forest (`random_forest/` and `rf_v2_lucky/`)
- `main.c`: Includes `#include <stdint.h>`, `#include "RF_model.h"`, `#include "samples.h"`, `#include "infer_one.h"`.
  - `<stdint.h>` is a standard freestanding header.
  - No hosted headers. No standard library calls.
- `RF_model.c`: `#include "RF_model.h"`
- `RF_model.h`: `#include "samples.h"`
- `infer_one.c`: `#include "infer_one.h"`
- `infer_one.h`: `#include "RF_model.h"`, `#include "samples.h"`
- `samples.c`: `#include "samples.h"`
- `samples.h`: Pure definitions (`#define`, `extern`).
- `startup.S`: Clean assembly providing `_start`, GPIO init, and `HALT` loop.
- **Compliance Status**: **100% Freestanding Compliant**. No host references found.

#### BNN (`Codespace/SERV_codespace/BNN/`)
- `main_bnn.c`:
  - Line 1: `#include <stdint.h>` (freestanding compliant)
  - Line 2: `#include <stddef.h>` (freestanding compliant)
  - Line 3: `//#include <stdio.h>` (**commented out**, clean)
- `helpers.c`:
  - Line 1: `#include <stdint.h>` (freestanding compliant)
  - Line 2: `#include <stddef.h>` (freestanding compliant)
- `layer0.h`, `layer1_uint32.h`, `samples_bnn.h`: Include `<stdint.h>`.
- **Compliance Status**: **100% Freestanding Compliant**.
- **Startup Code Notice**: BNN has no local `startup.S`; it relies on the R1 fallback to `Codespace/SERV_codespace/build_codes/startup.S`.

#### Tsetlin Machine (`Codespace/SERV_codespace/Tsetin_Machine/`)
- `class_sum.c`:
  - Line 1: `#include <limits.h> // for INT_MIN` (freestanding compliant)
- `clause_output.c`:
  - Line 1: `//#include "datapoint.h"` (commented out, clean)
- All other files include local project headers.
- **Compliance Status**: **100% Freestanding Compliant**.
- **Startup Code Notice**: Tsetlin Machine has no local `startup.S`; it also relies on the R1 fallback to `build_codes/startup.S`.

---

## 6. Recommended Unification Plan for Milestone 2 (R2)

### 6.1 Proposed Drop-in Content for `random_forest/infer_one.c`

To unify `random_forest/infer_one.c` seamlessly while matching the conventions of `Tsetin_Machine/class_sum.c` and `BNN/helpers.c`, apply the following implementation:

```c
#include "infer_one.h"

/*
 * Portable population count:
 *  - Modified SERV (built with -DUSE_CUSTOM_POPCOUNT):
 *      uses the hardware popcount instruction (.insn r 0x2B, 0, 0)
 *      with 42-cycle in-window writeback on SERV v1.5 RTL.
 *  - Original SERV (default build, no flag):
 *      software popcount fallback loop that runs on standard RV32I.
 */
static inline unsigned int popcnt(unsigned int val)
{
#ifdef USE_CUSTOM_POPCOUNT
    unsigned int rd;
    asm volatile(".insn r 0x2B, 0, 0, %0, %1, x0"
                 : "=r"(rd) : "r"(val));
    return rd;
#else
    unsigned int c = 0;
    while (val) {
        c += val & 1;
        val >>= 1;
    }
    return c;
#endif
}

// Returns prediction for one datapoint
int infer_one(const int *x)
{
    // Each tree's class vote (0..CLASSES-1) is packed into a 2-bit field
    // of a 32-bit word. CLASSES=3 -> 2 bits/vote; TREES=10 -> 20 bits, fits.
    unsigned int packed_votes = 0;
    int vote_count = 0;

    int row = 0;

    while (trees[row][0] != 0 || trees[row][1] != 0 ||
           trees[row][2] != 0 || trees[row][3] != 0)
    {
        int feature = trees[row][0];
        int value   = trees[row][1];

        // leaf?
        if (value == -1)
        {
            int cls = (int)feature;
            packed_votes |= (unsigned int)cls << (2 * vote_count);
            vote_count++;

            // skip to next tree
            while (!(trees[row][0] == 0 && trees[row][1] == 0 &&
                     trees[row][2] == 0 && trees[row][3] == 0))
                row++;

            // skip the {0,0,0,0}
            row++;
            continue;
        }

        int fidx = (int)feature;
        int split = value;
        int left  = (int)trees[row][2];
        int right = (int)trees[row][3];

        if (x[fidx] < split)
            row = left + row;
        else
            row = right + row;
    }

    // Majority vote using popcount (hardware instruction or software fallback).
    // In each 2-bit field: 00 = class 0, 01 = class 1, 10 = class 2.
    unsigned int lo = packed_votes & 0x55555555;         // low bit of each field
    unsigned int hi = (packed_votes >> 1) & 0x55555555;  // high bit of each field

    // count1 = fields equal to 01, count2 = fields equal to 10
    unsigned int count1 = popcnt(lo & ~hi);
    unsigned int count2 = popcnt(hi & ~lo);
    unsigned int count0 = (unsigned int)vote_count - count1 - count2;

    int best_class = 0, best_count = (int)count0;
    if ((int)count1 > best_count) { best_class = 1; best_count = (int)count1; }
    if ((int)count2 > best_count) { best_class = 2; best_count = (int)count2; }

    return best_class;
}
```

### 6.2 Analysis of the Unified Design
1. **Single Point of Control**: Both callers inside `infer_one()` simply call `popcnt(...)`. The macro `#ifdef USE_CUSTOM_POPCOUNT` controls the hardware vs software implementation cleanly inside the `popcnt` definition without cluttering the business logic.
2. **Inlining & Zero Overhead**: Marked `static inline`. When compiled with `-O2`, GCC completely inlines the `.insn` instruction or the software loop, matching the exact disassembly and cycle characteristics observed in `rf_v2_lucky` and `random_forest`.
3. **No Signature or Type Mismatches**: Takes `unsigned int val` and returns `unsigned int`. Matches the bitwise expressions `lo & ~hi` and `hi & ~lo`.
4. **No Other Files Need Modification**:
   - `RF_model.c`, `RF_model.h`, `infer_one.h`, `main.c`, `samples.c`, `samples.h`, `startup.S` remain unchanged.
   - `predicted_class.txt` is retained for verification.
   - `compile.sh` can remain untouched as an obsolete legacy script.

### 6.3 Deprecation & Archival Strategy for `rf_v2_lucky`

Since all functional code from `rf_v2_lucky` is subsumed by `random_forest` with `#ifdef USE_CUSTOM_POPCOUNT`:
1. **Deprecation Notice**: Place a `README.md` (or `DEPRECATED.md`) in `Codespace/SERV_codespace/rf_v2_lucky/`:
   ```markdown
   # DEPRECATED: rf_v2_lucky

   This directory has been unified into `Codespace/SERV_codespace/random_forest/`.
   To build this configuration, use:
       ./build.sh --folder=random_forest --popcount --build
   ```
2. **Preservation**: The git tag `v1.5_lucky` (commit `271570b`) permanently preserves the historical milestone. Leaving the folder in place with a deprecation notice satisfies Acceptance Criteria ("Redundant `rf_v2_lucky` directory can be safely archived or deprecated") while avoiding accidental breakage of any external historical scripts.

---

## 7. Verification Plan for Milestone 2 (R2)

Once implemented during Milestone 2, the changes should be verified as follows:

```bash
# 1. Compile software version (should produce binary WITHOUT .insn)
cd /home/chenyoo/riscv_benchmark/serv_project
./build.sh --folder=random_forest --build
riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Expect: NO MATCHES (clean software build)

# 2. Compile hardware popcount version (should produce binary WITH .insn)
./build.sh --folder=random_forest --popcount --build
riscv64-unknown-elf-objdump -d firmware.elf | grep -i "\.insn"
# Expect: Matches for .insn r 0x2b, 0, 0 (clean custom popcount build)

# 3. Simulate and verify cycle counts match historical targets:
# SW build simulation should match 526,208 cycles.
# HW build simulation should match 492,928 cycles.
```

---
*Report completed for Teamwork Preview Explorer Survey 2.*
