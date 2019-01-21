#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stdint.h>

#define WORD_SIZE 4
#define WORD_SIZE_BITS 32
#define BYTE 8
#define MEMORY_SIZE 65536

// Register definitions
#define NUM_GENREG 13
#define PC_REG 15
#define CPSR_REG 16
#define N_POS 31
#define Z_POS 30
#define C_POS 29
#define V_POS 28

uint32_t fetched;

typedef struct {
	bool N;
	bool Z;
	bool C;
	bool V;
} cpsrBits;

typedef struct {
	uint32_t reg[NUM_GENREG];
	uint32_t pc;
	cpsrBits cpsr;
} registers;

registers regs;

typedef struct {
	uint32_t *mp;
} memory;

memory mem;

#endif
