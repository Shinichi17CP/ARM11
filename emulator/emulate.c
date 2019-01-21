#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "state.h"
#include "utils.h"
#include "emulate_fde.h"


void startup() {
	mem.mp = malloc(MEMORY_SIZE * sizeof(uint32_t));
	if (mem.mp != NULL) {
		memset(mem.mp, 0, sizeof(MEMORY_SIZE * sizeof(uint32_t)));
		memset(&regs, 0, sizeof(registers));
	} else {
		printf("Error: Cannot initialise memory");
	}
}

void readBinFile(FILE *fp) {
	size_t numElem, numElemRead;
	size_t count = 0;
	numElem = WORD_SIZE;
	while (numElem) {
		if (count > MEMORY_SIZE) {
			printf("Number of instructions exceeds memory size");
			exit(1);
		}
		numElemRead = fread(mem.mp + count, 1, numElem, fp);
		count += WORD_SIZE;
		if (numElem != numElemRead) {
			if (!feof(fp)) {
				printf("Something went wrong while reading the "
					"binary file");
			}
			numElem = 0;
		}
	}

}

uint32_t flip(uint32_t instr) {
	return ((instr & TWO_BYTES) >> OUTER_SHIFT) |
		   ((instr & FOUR_BYTES) >> INNER_SHIFT) |
		   ((instr & SIX_BYTES) << INNER_SHIFT) |
		   ((instr & EIGHT_BYTES) << OUTER_SHIFT);
}

void display() {
	printf("Registers:\n");
	for (size_t i = 0; i < NUM_GENREG; i++) {
		printf("$%-3zu: %10d (0x%08x)\n", i, regs.reg[i], regs.reg[i]);
	}
	printf("PC  : %10d (0x%08x)\n", regs.pc, regs.pc);
	int32_t cpsr = convertCPSR();
	printf("CPSR: %10d (0x%08x)\n", cpsr, cpsr);

	printf("Non-zero memory:\n");
	for (size_t j = 0; j <= MEMORY_SIZE; j+=WORD_SIZE) {
		uint32_t value = *(mem.mp + j);
		if (value != 0) {
			printf("0x%08lx: 0x%08"PRIx32"\n", (unsigned long int) j, flip
					(value));
		}
	}

}

int main(int argc, char **argv) {
	startup();
	if (argc != 2) {
		printf("Incorrect number of arguments.");
		return EXIT_FAILURE;
	}
	FILE *fp;
	char *path = argv[1];
	fp = fopen(path, "rb");
	if (fp == NULL) {
		printf("File cannot be opened.");
		return EXIT_FAILURE;
	}
	readBinFile(fp);
	fclose(fp);

	fetched = fetch();
	while (true) {
		if (!decode(fetched)) {
			break;
		}
	}
	
	display();
	free(mem.mp);
	return EXIT_SUCCESS;
}
