#include "multiply.h"


void multiply(char **instr) {
    uint32_t res = MULTIPLY_DEFAULT;
    char *opcode = instr[0];
    
    uint32_t rd = atoi(&instr[1][1]) << M_RD_SHIFT;
    uint32_t rm = atoi(&instr[2][1]);
    uint32_t rs = atoi(&instr[3][1]) << M_RS_SHIFT;
    res |= rd | rm | rs;
    
    if (!strcmp(opcode, "mla")) {
        uint32_t rn = (atoi(&instr[4][1])) << M_RN_SHIFT;
        res |= A_SET | rn;
    } else if (strcmp(opcode, "mul")) {
        printf("Error: Not a multiply function!");
    }

    writeBinFile(res);
}



