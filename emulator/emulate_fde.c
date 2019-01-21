#include "emulate_fde.h"
#include "state.h"

uint32_t fetch() {
	if (regs.pc <= (long int) MEMORY_SIZE) {
		regs.pc += WORD_SIZE;
		return mem.mp[regs.pc - WORD_SIZE];
	}
	printf("Error: Out of bounds memory access at address 0x%08"PRIx32"\n", regs.pc);
	return EXIT_FAILURE;
}

bool checkCond(uint32_t cond) {
	switch (cond) {
		case (EQ):
			return regs.cpsr.Z;
		case (NE):
			return !regs.cpsr.Z;
		case (GE):
			return regs.cpsr.N == regs.cpsr.V;
		case (LT):
			return regs.cpsr.N != regs.cpsr.V;
		case (GT):
			return !regs.cpsr.Z && (regs.cpsr.N == regs.cpsr.V);
		case (LE):
			return regs.cpsr.Z || (regs.cpsr.N != regs.cpsr.V);
		case (AL):
			return true; // :D
		default:
			printf("Invalid condition code.");
			return false;
	}
}

size_t decode(uint32_t instr) {
	fetched = fetch();
	if (checkCond(instr & COND_MASK)) {
		if ((instr & MULT_MASK) == MULT) {
			multiply(instr);
		} else if ((instr & SDT_MASK) == SDT) {
			sdt(instr);
		} else if ((instr & DATA_MASK) == DATA) {
			compute(instr);
		} else if ((instr & BRANCH_MASK) == BRANCH) {
			regs.pc += branch(instr);
			fetched = fetch();
		}
	}
	if (instr == TERMINATE) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
