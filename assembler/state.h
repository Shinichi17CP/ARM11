#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stdint.h>

#define WORD_SIZE 4
#define MAX_CHARACTERS 511
#define MAX_LABELS 20

FILE *destFile;

uint32_t pc;

struct tablePair {
	char *label;
	uint32_t addr;
};

struct LATable {
	struct tablePair *labelAddr;
	size_t size;
};

struct LATable *labelTable;

struct expressionBuffer {
	uint32_t *expressions;
	size_t size;
	uint32_t maxPC;
};

struct expressionBuffer *expSDT;

#endif
