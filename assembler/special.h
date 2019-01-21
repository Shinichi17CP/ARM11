#ifndef SPECIAL_H
#define SPECIAL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "codes.h"
#include "state.h"
#include "utils.h"

uint32_t computeLSL(char **instr);

void special(char **instr);

#endif