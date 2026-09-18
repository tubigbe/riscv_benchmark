#include "infer_one.h"

static inline unsigned int popcnt(unsigned int val)
{
#ifdef USE_CUSTOM_POPCOUNT
    unsigned int rd;
    /* Official Zbb "cpop rd, rs1" encoding:
     *   opcode=0010011 (OP-IMM), funct3=001, imm[11:0]=0x602
     * Hand-written .insn keeps zbb/zbs invisible to the compiler, so no
     * Zb* instruction other than this one can ever reach the binary.
     * Do NOT add zbs to -march: `binvi rd, rs1, 2` would collide with the
     * RTL's minimal cpop detection and silently be taken as a popcount. */
    asm volatile(".insn i 0x13, 1, %0, %1, 0x602"
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
