#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "state.h"
#include "masks.h"

uint32_t convertCPSR();

uint32_t printGpio(uint32_t addr);

uint32_t fetchReg(size_t r);

void storeReg(size_t n, uint32_t data);

uint32_t fetchMem(uint32_t addr);

void storeMem(uint32_t addr, uint32_t data);

uint32_t createRightMask(size_t n);

uint32_t createLeftMask(size_t n);

uint32_t barrelShift(uint32_t code, uint32_t data, size_t n);

#endif
