#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <ctype.h>
#include "tables.h"
#include "state.h"
#include "utils.h"

char *dataInstr[dataInstrSize] = {"add", "sub", "rsb", "and", "eor", "orr", "mov", "tst", "teq", "cmp"};
char *branchInstr[branchInstrSize] = {"beq", "bne", "bge", "blt", "bgt", "ble", "b"};
char *multInstr[multInstrSize] = {"mul", "mla"};
char *sdtInstr[sdtInstrSize] = {"ldr", "str"};
char *specialInstr[specialInstrSize] = {"lsl", "andeq"};

size_t writeBinFile(uint32_t instr) {
    size_t numElemWritten;
    numElemWritten = fwrite(&instr, 1, WORD_SIZE, destFile);
    if (numElemWritten != WORD_SIZE) {
        printf("Error: Something went wrong when writing instructions to destination file.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

size_t writeSDTExpressions() {
    size_t numElemWritten;
    for (size_t i = 0; i < expSDT->size; i++) {
        numElemWritten = fwrite(&expSDT->expressions[i], 1, WORD_SIZE, destFile);
        if (numElemWritten != WORD_SIZE) {
            printf("Error: Something went wrong when writing expressions to destination file.");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

bool elemIn(char *str, char **list, size_t size) {
    assert(str != NULL && list != NULL);
    for (size_t i = 0; i < size; i++) {
        if (!strcmp(str, list[i])) {
            return true;
        }
    }
    return false;
}

// Creates mask such that the first n bits are 1
uint32_t createLeftMask(size_t n) {
    uint32_t mask = 0;
    for (size_t i = 0; i < n; i++) {
        mask |= (1 << (WORD_SIZE_BITS - i - 1));
    }
    return mask;
}

// Creates mask such that the last n bits are 1
uint32_t createRightMask(size_t n) {
    uint32_t mask = 0;
    for (size_t i = 0; i < n; i++) {
        mask |= (1 << i);
    }
    return mask;
}

bool isLabel(char *str) {
    return str[strlen(str) - 1] == ':';
}

void addPair(char *label, uint32_t addr) {
    static size_t index = 0;
    label[strlen(label) - 1] = 0;
    labelTable->labelAddr[index].label = malloc(strlen(label) + 1);
    if (labelTable->labelAddr[index].label == NULL) {
        printf("Error: Label pair memory allocation failed.");
    }
    
    strcpy(labelTable->labelAddr[index].label, label);
    labelTable->labelAddr[index].addr = addr;
    index++;
    labelTable->size = index;
    
}

uint32_t getAddr(char *label) {
    assert(label != NULL && labelTable->labelAddr != NULL);
    for (size_t i = 0; i < labelTable->size; i++) {
        if (!strcmp(label, labelTable->labelAddr[i].label)) {
            return labelTable->labelAddr[i].addr;
        }
    }
    return 0;
}

bool checkWhiteSpaceOnly(char *str) {
    size_t size = strlen(str);
    for (size_t i = 0; i < size; i++) {
        if (!isspace(str[i])) {
            return false;
        }
    }
    return true;
}

static char *removeWhiteSpace(char *str) {
    assert(str != NULL);
    size_t first = 0;
    size_t second = 0;
    while (second < strlen(str) + 1) {
        while (isspace(str[second])) {
            second++;
        }
        str[first] = str[second];
        first++;
        second++;
    }
    return str;
}

char **tokenizer(char *instr) {
    char **res = malloc(MAX_CHARACTERS);

    if (!res) {
        printf("Error: Tokenizer memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    char *rest = instr;
    size_t i = 1;

    if (!isLabel(instr)) {
        //the first token before a space is always the opcode
        res[0] = strtok_r(rest, " ", &rest);
        rest = removeWhiteSpace(rest);
        //split the operands using commas
        while (*rest != '\0') {
            res[i] = strtok_r(rest, ",", &rest);
            i++;
        }
    }
    return res;
}

bool isImmediate(char *instr) {
    return (instr[0] == '#');
}

bool isHex(char *expr) {
    return (expr[1] == 'x');
}

uint32_t getImmediate(char *op, uint32_t max) {
    uint32_t imm;
    if (isHex(&op[1])) {
        imm = (uint32_t) strtol(&op[1], NULL, 0);
    } else {
        char *endptr;
        imm = (uint32_t) strtod(&op[1], &endptr);
    }

    if (imm < max) {
        return imm;
    } else {
        size_t rotations = 0;
        while (imm >= max) {
            for (size_t i = 0; i < 2; i++) {
                uint32_t rotated = ((imm & createLeftMask(1)) >> (WORD_SIZE_BITS - 1)) ;
                imm <<= 1;
                imm |= rotated;
            }
            rotations++;
        }
        return (rotations << ROTATE_SHIFT) | imm;
    }

}

uint32_t getShiftedReg(char *rm, char *shift) {
    uint32_t shiftedReg = atoi(&rm[1]);
    if (shift != NULL) {
        if (!strncmp(shift, "lsl", 3)) {
            shiftedReg |= LSL;
        } else if (!strncmp(shift, "lsr", 3)) {
            shiftedReg |= LSR;
        } else if (!strncmp(shift, "asr", 3)) {
            shiftedReg |= ASR;
        } else if (!strncmp(shift, "ror", 3)) {
            shiftedReg |= ROR;
        } else {
            printf("Error: Invalid shift name.");
        }
        if (!strncmp(&shift[3], "r", 1)) {
            shiftedReg |= SHIFT_BY | (atoi(&shift[4]) << RS_SHIFT);
        } else if (!strncmp(&shift[3], "#", 1)) {
            shiftedReg |= (atoi(&shift[4]) << INT_SHIFT);
        }
    }
    return shiftedReg;
}
