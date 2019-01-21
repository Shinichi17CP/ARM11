#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "tables.h"
#include "state.h"
#include "dataProc.h"
#include "branch.h"
#include "sdt.h"
#include "multiply.h"
#include "special.h"

void createLabelTable() {
    labelTable = malloc(sizeof(struct LATable));
    if (labelTable == NULL) {
        printf("Error: Label table memory allocation failed.");
    }
    labelTable->labelAddr = calloc(MAX_LABELS, sizeof(struct tablePair));
    if (labelTable->labelAddr == NULL) {
        printf("Error: Label address pairs array memory allocation failed.");
    }
    labelTable->size = 0;
}

void allocateEB() {
    expSDT = malloc(sizeof(struct expressionBuffer));
    if (expSDT == NULL) {
        printf("Error: Expression Buffer memory allocation failed.");
    }
    expSDT->expressions = calloc(MAX_EXPRESSIONS, sizeof(uint32_t));
    if (expSDT->expressions == NULL) {
        printf("Error: Expression Buffer array memory allocation failed.");
    }
    expSDT->size = 0;
}

void findLabels(FILE *fp) {
    createLabelTable();
    char currentInstr[MAX_CHARACTERS];
	while (!feof(fp)) {
        if (fgets(currentInstr, MAX_CHARACTERS, fp) != NULL) {
            if (!checkWhiteSpaceOnly(currentInstr)) {
                char *lastChar = &currentInstr[strlen(currentInstr) - 1];
                *lastChar = isspace(*lastChar)? 0: *lastChar;
                if (isLabel(currentInstr)) {
                    addPair(currentInstr, pc);
                } else {
                    pc += WORD_SIZE;
                }
            }
        }
	}
	rewind(fp);
    allocateEB();
    expSDT->maxPC = pc;
	pc = 0;
}

void execution(char **instr) {
    char *opcode = instr[0];
    if (elemIn(opcode, dataInstr, dataInstrSize)) {
        dataProc(instr);
    } else if (elemIn(opcode, branchInstr, branchInstrSize)) {
        branch(instr);
    } else if (elemIn(opcode, multInstr, multInstrSize)) {
        multiply(instr);
    } else if (elemIn(opcode, sdtInstr, sdtInstrSize)) {
        sdt(instr);
    } else if (elemIn(opcode, specialInstr, specialInstrSize)) {
        special(instr);
    }
}

void freeMemory() {
    for (size_t i = 0; i < labelTable->size; i++) {
        free(labelTable->labelAddr[i].label);
    }
    free(labelTable->labelAddr);
    free(labelTable);
    free(expSDT->expressions);
    free(expSDT);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Error: Incorrect number of arguments.\n");
        return EXIT_FAILURE;
    }

    FILE *fp;
    char *path = argv[1];
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error: Assembly file cannot be opened.\n");
        return EXIT_FAILURE;
    }

	pc = 0;
    char *dest = argv[2];
	destFile = fopen(dest, "wb");
	if (destFile == NULL) {
		printf("Error: Binary file cannot be opened.\n");
		return EXIT_FAILURE;
	}

	char currentInstr[MAX_CHARACTERS];
	findLabels(fp);

    while (!feof(fp)) {
        if (fgets(currentInstr, MAX_CHARACTERS, fp) != NULL) {
            if (!checkWhiteSpaceOnly(currentInstr)) {
                char *lastChar = &currentInstr[strlen(currentInstr) - 1];
                *lastChar = isspace(*lastChar)? 0: *lastChar;
                if (!isLabel(currentInstr)) {
                    execution(tokenizer(currentInstr));
                    pc += WORD_SIZE;
                }
            }
        }
    }
    writeSDTExpressions();
	fclose(fp);
	fclose(destFile);
    freeMemory();
	return EXIT_SUCCESS;
}

