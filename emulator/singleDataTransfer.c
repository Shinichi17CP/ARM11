#include "singleDataTransfer.h"

/*Finding offset:
 * if I == 1 then Offset is a shifted register
 * if I == 0 then Offset is an unsigned 12 bit immediate offset
 */
uint32_t getOffset(uint32_t instr) {
    if ((instr & I_MASK) == 0) {
        return (instr & SDT_OFFSET_MASK);
    } else {
        uint32_t rmValue = fetchReg(instr & RM_MASK);
        uint32_t shiftCode = instr & SHIFT_TYPE_MASK;
        uint32_t result;
        bool previousC = regs.cpsr.C;
        if ((instr & SHIFT_BY) == 0) {
            size_t n = (instr & INT_MASK) >> INT_SHIFT;
            result = barrelShift(shiftCode, rmValue, n);
        } else {
            uint32_t rsValue = fetchReg((instr & RS_MASK) >> RS_SHIFT);
            result = barrelShift(shiftCode, rmValue, rsValue);
        }
        regs.cpsr.C = previousC;
        return result;
    }
}

void sdt(uint32_t instr){
    
    size_t numRn = (instr & RN_MASK) >> RN_SHIFT;
    size_t numRd = (instr & RD_MASK) >> RD_SHIFT;

    uint32_t contentInRn = fetchReg(numRn);
    uint32_t contentInRd = fetchReg(numRd);
    uint32_t offset = getOffset(instr);


    /*Pre/Post indexing bit checking:
     * if P == 1 (pre-indexing) offset is +/- to Rn before transferring data
     * if P == 0 (post-indexing) offset is +/- to Rn after transferring data
     */
    if ((instr & P_MASK) == P_MASK) {
        if ((instr & U_MASK) == U_MASK) {
            if ((instr & L_MASK) == L_MASK) {
                storeReg(numRd, fetchMem(contentInRn + offset));
            } else {
                storeMem(contentInRn + offset, contentInRd);
            }

        } else if ((instr & L_MASK) == L_MASK) {
            storeReg(numRd, fetchMem(contentInRn - offset));
        } else {
            storeMem(contentInRn - offset, contentInRd);
        }

    } else {
        if ((instr & U_MASK) == U_MASK) {
            if ((instr & L_MASK) == L_MASK) {
                storeReg(numRd, fetchMem(contentInRn));
                contentInRn += offset;
            } else {
                storeMem(contentInRn, contentInRd);
                contentInRn += offset;
            }

        } else if ((instr & L_MASK) == L_MASK) {
            storeReg(numRd, fetchMem(contentInRn));
            contentInRn -= offset;
        } else {
            storeMem(contentInRn, contentInRd);
            contentInRn -= offset;
        }
        storeReg(numRn, contentInRn);
    }
}
