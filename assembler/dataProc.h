#ifndef DATAPROC_H
#define DATAPROC_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "tables.h"
#include "codes.h"
#include "state.h"

uint32_t getOpcodeDP(char *opcode);

uint32_t getOp2(char *rm, char *shift);

uint32_t ALCompute(char **instr);

uint32_t flagsCompute(char **instr);

uint32_t movCompute(char **instr);

void dataProc(char **instr);

#endif