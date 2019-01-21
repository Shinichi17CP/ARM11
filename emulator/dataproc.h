#ifndef DATAPROC_H
#define DATAPROC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "masks.h"
#include "utils.h"
#include "state.h"


uint32_t getOp2(uint32_t instr);

void setCPSR(uint32_t result, bool bitC) ;

bool getAddCarry(uint32_t op1, uint32_t op2, uint32_t result);

bool getSubCarry(uint32_t op1, uint32_t op2, uint32_t result);

uint32_t compute(uint32_t instr) ;

#endif
