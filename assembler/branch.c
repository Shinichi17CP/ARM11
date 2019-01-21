#include "branch.h"

uint32_t getOpcodeB(char *opcode) {
	if (!strcmp(opcode, "beq")) {
		return BEQ;
	} else if (!strcmp(opcode, "bne")) {
		return BNE;
	} else if (!strcmp(opcode, "bge")) {
		return BGE;
	} else if (!strcmp(opcode, "blt")) {
		return BLT;
	} else if (!strcmp(opcode, "bgt")) {
		return BGT;
	} else if (!strcmp(opcode, "ble")) {
		return BLE;
	} else {
		return BAL;
	}
}

uint32_t getOffsetB(char *label) {
	int32_t offset = getAddr(label) - (pc + PC_OFFSET);
    offset &= createRightMask(OFFSET_BITS_BEFORE);
    offset >>= OFFSET_SHIFT;
    return offset & createRightMask(OFFSET_BITS_AFTER);
}

void branch(char **instr) {
    uint32_t resultB = 0;
	char *opcode = instr[0];
	resultB |= getOpcodeB(opcode);
	resultB |= getOffsetB(instr[1]);

	writeBinFile(resultB);
}