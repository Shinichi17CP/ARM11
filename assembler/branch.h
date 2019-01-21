#ifndef BRANCH_H
#define BRANCH_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "utils.h"
#include "state.h"
#include "codes.h"

uint32_t getOpcodeB(char *opcode);

uint32_t getOffsetB(char *label);

void branch(char **instr);

#endif
