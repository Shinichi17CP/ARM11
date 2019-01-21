#include "utils.h"

uint32_t convertCPSR(){
    return regs.cpsr.N << N_POS | regs.cpsr.Z << Z_POS
           | regs.cpsr.C << C_POS | regs.cpsr.V << V_POS;
}

uint32_t printGpio(uint32_t addr) {
   switch (addr) {
       case (PIN_0_9):
           printf("One GPIO pin from 0 to 9 has been accessed\n");
           return addr;
       case (PIN_10_19):
           printf("One GPIO pin from 10 to 19 has been accessed\n");
           return addr;
       case (PIN_20_29):
           printf("One GPIO pin from 20 to 29 has been accessed\n");
           return addr;
       case (PIN_OFF):
           printf("PIN OFF\n");
           return addr;
       case (PIN_ON):
           printf("PIN ON\n");
           return addr;
       default:
           printf("Error: Out of bounds memory access at address 0x%08"PRIx32"\n", addr);
           return 0;
   }
}

uint32_t fetchReg(size_t r) {
    if (r < NUM_GENREG) {
        return regs.reg[r];
    } else if (r == PC_REG){
        return regs.pc;
    } else if (r == CPSR_REG) {
        return convertCPSR();
    } else {
        printf("Error: Access of register %zu not allowed.", r);
        return 0;
    }
}

void storeReg(size_t n, uint32_t data) {
    regs.reg[n] = data;
}

// Creates mask such that the last n bits are 1
uint32_t createRightMask(size_t n) {
    uint32_t mask = 0;
    for (size_t i = 0; i < n; i++) {
        mask |= (1 << i);
    }
    return mask;
}

// Creates mask such that the first n bits are 1
uint32_t createLeftMask(size_t n) {
    uint32_t mask = 0;
    for (size_t i = 0; i < n; i++) {
        mask |= (1 << (WORD_SIZE_BITS - i - 1));
    }
    return mask;
}

uint32_t fetchMem(uint32_t addr) {
    if (addr > (long int) MEMORY_SIZE) {
        return printGpio(addr);
    }
    if (addr % WORD_SIZE == 0) {
        return mem.mp[addr];
    } else {
        size_t offset = addr % WORD_SIZE;
        uint32_t aligned = addr - offset;
        uint32_t MSA = fetchMem(aligned + WORD_SIZE) & createRightMask(offset * BYTE);
        MSA = MSA << (WORD_SIZE_BITS - (offset * BYTE));
        uint32_t LSA = fetchMem(aligned) & createLeftMask(WORD_SIZE_BITS - offset * BYTE);
        LSA = LSA >> (offset * BYTE);
        return MSA | LSA;
    }
}

void storeMem(uint32_t addr, uint32_t data) {
    if (addr > (long int) MEMORY_SIZE) {
        printGpio(addr);
    } else if (addr % WORD_SIZE == 0) {
        mem.mp[addr] = data;
    } else {
        uint32_t oldData, preserve, storeData;
        size_t offset = addr % WORD_SIZE;
        uint32_t aligned = addr - offset;

        // Store the LSBs of the data
        oldData = fetchMem(aligned);
        preserve = oldData & createRightMask(offset * BYTE);
        storeData = data & createRightMask(WORD_SIZE_BITS - offset * BYTE);
        storeData = storeData << (offset * BYTE);
        storeMem(aligned, storeData | preserve);

        // Store the MSBs of the data
        oldData = fetchMem(aligned + WORD_SIZE);
        preserve = oldData & createLeftMask(WORD_SIZE_BITS - offset * BYTE);
        storeData = data & createLeftMask(offset * BYTE);
        storeData = storeData >> (WORD_SIZE_BITS - offset * BYTE);
        storeMem(aligned + WORD_SIZE, storeData | preserve);
    }
}

uint32_t barrelShift(uint32_t code, uint32_t data, size_t n) {
    if (n == 0) {
        return data;
    } else {
        switch (code) {
            case(LSL):
                regs.cpsr.C = (data & (1 << (WORD_SIZE_BITS - n))) != 0;
                return data << n;
            case(LSR):
                regs.cpsr.C = (data & (1 << (n - 1))) != 0;
                return (data >> n) & createRightMask(WORD_SIZE_BITS - n);
            case(ASR):
                regs.cpsr.C = (data & (1 << (n - 1))) != 0;
                return data >> n;
            case(ROR):
                regs.cpsr.C = (data & (1 << (n - 1))) != 0;
                uint32_t rotated = data << (WORD_SIZE_BITS - n);
                return (data >> n) | rotated;
            default:
                printf("Invalid shift opcode");
                return data;
        }
    }
}