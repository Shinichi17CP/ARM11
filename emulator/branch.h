#ifndef BRANCH_H
#define BRANCH_H

#include <stdint.h>
#include "masks.h"
#include "state.h"

#define SIGN_EXTEND 0xFC000000
#define B_SHIFT 2

uint32_t branch(uint32_t instr);

#endif