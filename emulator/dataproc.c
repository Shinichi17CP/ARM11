#include "dataproc.h"


uint32_t getOp2(uint32_t instr) {
    if ((instr & I_MASK) == 0) {
        uint32_t rmValue = fetchReg(instr & RM_MASK);
        uint32_t shiftCode = instr & SHIFT_TYPE_MASK;
        if ((instr & SHIFT_BY) == 0) {
            size_t n = (instr & INT_MASK) >> INT_SHIFT;
            return barrelShift(shiftCode, rmValue, n);
        } else {
            uint32_t rsValue = fetchReg((instr & RS_MASK) >> RS_SHIFT);
            return barrelShift(shiftCode, rmValue, rsValue);
        }

    } else {
        uint32_t imm = instr & IMMEDIATE_MASK;
        size_t n = (instr & ROTATE_MASK) >> ROTATE_SHIFT;
        return barrelShift(ROR, imm, n);
    }
}

void setCPSR(uint32_t result, bool bitC) {
    regs.cpsr.Z = result == 0;
    regs.cpsr.N = (result & N_MASK) != 0;
    regs.cpsr.C = bitC;
}

bool getAddCarry(uint32_t op1, uint32_t op2, uint32_t result) {
    bool msbOp1 = (op1 & (1 << (WORD_SIZE_BITS - 1))) != 0;
    bool msbOp2 = (op2 & (1 << (WORD_SIZE_BITS - 1))) != 0;
    bool msbRes = (result & (1 << (WORD_SIZE_BITS - 1))) != 0;
    return (msbOp1 && msbOp2) || (!msbRes &&
                ((msbOp1 && !msbOp2) || (!msbOp1 && msbOp2)));
}

bool getSubCarry(uint32_t op1, uint32_t op2, uint32_t result) {
    bool msbOp1 = (op1 & (1 << (WORD_SIZE_BITS - 1))) != 0;
    bool msbOp2 = (op2 & (1 << (WORD_SIZE_BITS - 1))) != 0;
    bool msbRes = (result & (1 << (WORD_SIZE_BITS - 1))) != 0;
    return (!msbOp1 && msbRes) || (msbOp1 && msbOp2 && msbRes);
}

uint32_t compute(uint32_t instr) {
    uint32_t opcode = instr & OPCODE_MASK;
    bool write = true;
    bool previousC = regs.cpsr.C;
    uint32_t rn = (instr & RN_MASK) >> RN_SHIFT;
    uint32_t rd = (instr & RD_MASK) >> RD_SHIFT;
    uint32_t op2 = getOp2(instr);
    bool bitC = regs.cpsr.C;
    uint32_t result;
    switch (opcode) {
        case (TST):
            write = false;
        case (AND):
            result = fetchReg(rn) & op2;
            break;
        case (TEQ):
            write = false;
        case (EOR):
            result = fetchReg(rn) ^ op2;
            break;
        case (ORR):
            result = fetchReg(rn) | op2;
            break;
        case (MOV):
            result = op2;
            break;


        case (CMP):
            write = false;
        case (SUB):
            result = fetchReg(rn) - op2;
            bitC = !getSubCarry(fetchReg(rn), op2, result);
            break;
        case (RSB):
            result = op2 - fetchReg(rn);
            break;
        case (ADD):
            result = fetchReg(rn) + op2;
            bitC = getAddCarry(fetchReg(rn), op2, result);
            break;
        default:
            printf("Invalid opcode\n");
            result = fetchReg(rn);
            break;
    }
    if ((instr & S_MASK) == S_MASK) {
        setCPSR(result, bitC);
    } else {
        regs.cpsr.C = previousC;
    }
    if (write) {
        storeReg(rd, result);
    }
    return result;
}
