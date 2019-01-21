#include "multiply.h"

uint32_t multiply(uint32_t instr) {

    uint32_t contentInRm = fetchReg(MUL_RM_MASK & instr);
    uint32_t contentInRs = fetchReg((MUL_RS_MASK & instr) >> RS_MUL_SHIFT);
    uint32_t contentInRn = fetchReg((MUL_RN_MASK & instr) >> RN_MUL_SHIFT);
    uint32_t res;

    if ((instr & MUL_COND_MASK) == 0) {
        res = contentInRm * contentInRs;
    } else {
        res = contentInRm * contentInRs + contentInRn;
    }

    storeReg(((MUL_RD_MASK & instr) >> RD_MUL_SHIFT), res);

    if ((instr & S_MASK) != 0) {
        regs.cpsr.N = (res & N_MASK) != 0;
        regs.cpsr.Z = res == 0;
    }
    return res;
}
