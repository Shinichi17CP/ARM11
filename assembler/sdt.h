#ifndef SDT_H
#define SDT_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "codes.h"
#include "state.h"
#include "dataProc.h"

uint32_t caseDir(char ** instr);

uint32_t caseImme(char **instr);

void sdt(char **instr);

#endif