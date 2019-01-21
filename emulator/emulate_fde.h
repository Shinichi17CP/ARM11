#ifndef EMULATE_FDE
#define EMULATE_FDE

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "state.h"
#include "masks.h"
#include "branch.h"
#include "dataproc.h"
#include "multiply.h"
#include "singleDataTransfer.h"

uint32_t fetch();

bool checkCond(uint32_t cond);

size_t decode(uint32_t instr);

#endif