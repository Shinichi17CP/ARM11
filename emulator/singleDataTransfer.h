#ifndef SINGLEDATATRANSFER_H
#define SINGLEDATATRANSFER_H

#include "utils.h"
#include "state.h"
#include "masks.h"

/*Finding offset:
 * if I == 1 then Offset is a shifted register
 * if I == 0 then Offset is an unsigned 12 bit immediate offset
 */
uint32_t getOffset(uint32_t instr);

void sdt(uint32_t instr);

#endif