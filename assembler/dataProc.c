#include "dataProc.h"

char *ALInstr[ALInstrSize] = {"add", "sub", "rsb", "and", "eor", "orr"};
char *flagsInstr[flagsInstrSize] = {"tst", "teq", "cmp"};

uint32_t getOpcodeDP(char *opcode) {
	if (!strcmp(opcode, "and")) {
		return AND;
	} else if (!strcmp(opcode, "eor")) {
		return EOR;
	} else if (!strcmp(opcode, "sub")) {
		return SUB;
	} else if (!strcmp(opcode, "rsb")) {
		return RSB;
	} else if (!strcmp(opcode, "add")) {
		return ADD;
	} else if (!strcmp(opcode, "orr")) {
		return ORR;
	} else if (!strcmp(opcode, "mov")) {
		return MOV;
	} else if (!strcmp(opcode, "tst")) {
		return TST;
	} else if (!strcmp(opcode, "teq")) {
		return TEQ;
	} else if (!strcmp(opcode, "cmp")) {
		return CMP;
	}
	printf("Error: Invalid mnemonic.\n");
	return 0;
}

uint32_t getOp2(char *rm, char *shift) {
	if (isImmediate(rm)) {
		return I_BIT | getImmediate(rm, MAX_IMM);
	} else {
		return getShiftedReg(rm, shift);
    }
}

uint32_t ALCompute(char **instr) {
	char *rd = instr[0];
	char *rn = instr[1];
	uint32_t rdNum = atoi(&rd[1]);
	uint32_t rnNum = atoi(&rn[1]);
	return (rdNum << RD_SHIFT) | (rnNum << RN_SHIFT) | getOp2(instr[2], instr[3]);
}

uint32_t flagsCompute(char **instr) {
	char *rn = instr[0];
	uint32_t rnNum = atoi(&rn[1]);
	return S_BIT | (rnNum << RN_SHIFT) | getOp2(instr[1], instr[2]);
}

uint32_t movCompute(char **instr) {
	char *rd = instr[0];
	uint32_t rdNum = atoi(&rd[1]);
	return (rdNum << RD_SHIFT) | getOp2(instr[1], instr[2]);
}

void dataProc(char **instr) {
	uint32_t resultDP = 0;
	char *opcode = instr[0];
	resultDP |= getOpcodeDP(opcode);
	if (elemIn(opcode, ALInstr, ALInstrSize)) {
		resultDP |= ALCompute(&instr[1]);
	} else if (elemIn(opcode, flagsInstr, flagsInstrSize)) {
		resultDP |= flagsCompute(&instr[1]);
	} else {
		resultDP |= movCompute(&instr[1]);
	}
	writeBinFile(resultDP);
}

