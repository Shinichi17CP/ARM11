#ifndef MULTIPLY_H
#define MULTIPLY_H


#include "state.h"
#include "utils.h"
#include "masks.h"

#define RS_MUL_SHIFT 8
#define RN_MUL_SHIFT 12
#define RD_MUL_SHIFT 16

uint32_t multiply(uint32_t instr);

#endif