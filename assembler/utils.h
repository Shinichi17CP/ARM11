#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include "codes.h"
#define WORD_SIZE_BITS 32

size_t writeBinFile(uint32_t instr);

size_t writeSDTExpressions();

bool elemIn(char *str, char **list, size_t size);

uint32_t createLeftMask(size_t n);

uint32_t createRightMask(size_t n);

bool isLabel(char* str);

void addPair(char *label, uint32_t addr);

uint32_t getAddr(char *label);

bool checkWhiteSpaceOnly(char *str);

char **tokenizer(char *instr);

bool isImmediate(char *instr);

bool isHex(char *expr);

uint32_t getImmediate(char *op, uint32_t max);

uint32_t getShiftedReg(char *rm, char *shift);

#endif
