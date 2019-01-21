#include "branch.h"

#define SIGN_EXTEND 0xFC000000
#define B_SHIFT 2

/*Branch Instruction
 * Offset is shifted left 2 bits, sign extended to 32 bits and then added to the PC */

uint32_t branch(uint32_t instr) {
    uint32_t offset = instr & OFFSET_MASK;
    offset = offset << B_SHIFT;
    if (offset & MSB_MASK) {
        offset = offset | SIGN_EXTEND;
    }
    return offset;
}
