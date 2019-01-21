#include "sdt.h"

static bool checkIndexing(char **instr) {
    return !((strlen(instr[2]) == 4) && (instr[3] != NULL));
}

uint32_t caseDir(char **instr) {
    if (instr[3] == NULL) {
        return P_SET | U_SET;
    }
    uint32_t p = (checkIndexing(instr))? P_SET: 0;

    if (strstr(instr[3], "#") != NULL) {
        uint32_t offset;
        char *negative = strstr(instr[3], "-");
        if (negative != NULL) {
            *negative = '#';
            offset = getImmediate(&instr[3][1], MAX_IMM);
        } else {
            p |= U_SET;
            offset = getImmediate(instr[3], MAX_IMM);
    
        }
        return p | offset;
    } else {
        p |= getShiftedReg(instr[3], instr[4]);
        return p | I_SET |U_SET;
    }
}

static void addExpression(uint32_t exp) {
    expSDT->expressions[expSDT->size] = exp;
    expSDT->size++;
}

uint32_t caseImme(char **instr) {

    char *expression = instr[2];
    char *endptr;
    int32_t value;
    if (strstr(expression, "-") == NULL) {
        value = strtod(&expression[1], &endptr);
    } else {
        value = - strtod(&expression[2], &endptr);
    }

    if (value <= MAX_FOR_MOV) {
        char *rd = instr[1];
        uint32_t rdNum = atoi(&rd[1]);
        return MOV | I_BIT | (rdNum << RD_SHIFT) | getImmediate(expression, MAX_IMM);
        
    } else {
        uint32_t addr = expSDT->maxPC + expSDT->size * WORD_SIZE;
        addExpression(value);
        int32_t difference = addr - (pc + PC_OFFSET);
        uint32_t offset;
        if (difference < 0) {
            offset = -difference;
        } else {
            offset = difference | U_SET;
        }
        return SDT_DEFAULT | L_SET | PC | offset;
        
    }
}

void sdt(char **instr) {

    uint32_t res = SDT_DEFAULT;
    uint32_t rd = atoi(&instr[1][1]) << SDT_RD_SHIFT;

    if (strstr(instr[2], "=") != NULL) {
        res = P_SET | rd | caseImme(instr);
    } else if (!strncmp(instr[2], "[", 1)) {
        uint32_t rn = atoi(&instr[2][2]) << SDT_RN_SHIFT;
        if (!strcmp(instr[0], "ldr")) {
            res |= L_SET;
        }
        res |= caseDir(instr) | rn | rd;
    }
    writeBinFile(res);
}