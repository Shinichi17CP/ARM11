#include "special.h"

uint32_t computeLSL(char **instr) {
	uint32_t integer = getImmediate(instr[1], MAX_INT);
	char *rd = instr[0];
	uint32_t rdNum = atoi(&rd[1]);
	return (integer << INT_SHIFT) | (rdNum << RD_SHIFT) | rdNum ;

}

void special(char **instr) {
	uint32_t resultS = 0;
	char *opcode = instr[0];

	if (!strcmp(opcode, "andeq")) {
		resultS = ANDEQ;
	} else if (!strcmp(opcode, "lsl")) {
		resultS = MOV | computeLSL(&instr[1]);
	} else {
		printf("Error: Invalid opcode.\n");
	}

	writeBinFile(resultS);
}



