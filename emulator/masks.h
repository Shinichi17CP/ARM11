#ifndef MASKS_H
#define MASKS_H


// Condition mask & codes
#define COND_MASK 0xF0000000
#define EQ 0x00000000
#define NE 0x10000000
#define GE 0xA0000000
#define LT 0xB0000000
#define GT 0xC0000000
#define LE 0xD0000000
#define AL 0xE0000000

// OPCODE mask & codes
#define OPCODE_MASK 0x01E00000
#define AND 0x00000000
#define EOR 0x00200000
#define SUB 0x00400000
#define RSB 0x00600000
#define ADD 0x00800000
#define TST 0x01000000
#define TEQ 0x01200000
#define CMP 0x01400000
#define ORR 0x01800000
#define MOV 0x01A00000

// CPSR mask
#define N_MASK 0x80000000
#define S_MASK 0x00100000

// Shift type codes & mask
#define SHIFT_TYPE_MASK 0x00000060
#define LSL 0x00000000
#define LSR 0x00000020
#define ASR 0x00000040
#define ROR 0x00000060

// Data Processing: Operand2 & SDT: Offset
#define I_MASK 0x02000000
#define RM_MASK 0x0000000F
#define RN_MASK 0x000F0000
#define RD_MASK 0x0000F000
#define RN_SHIFT 16
#define RD_SHIFT 12
#define INT_MASK 0x00000F80
#define INT_SHIFT 7
#define RS_MASK 0x00000F00
#define RS_SHIFT 8
#define ROTATE_MASK 0x00000F00
#define ROTATE_SHIFT 7
#define IMMEDIATE_MASK 0x000000FF
#define SHIFT_BY 0x00000010

// Instruction type masks & codes
#define TERMINATE 0x00000000
#define BRANCH_MASK 0x0F000000
#define BRANCH 0x0A000000
#define SDT_MASK 0x0C600000
#define SDT 0x04000000
#define MULT_MASK 0x0FC000F0
#define MULT 0x00000090
#define DATA_MASK  0x0C000000
#define DATA 0x00000000

// Branch masks
#define OFFSET_MASK 0x00FFFFFF
#define MSB_MASK 0x02000000

// Multiply Masks
#define MUL_COND_MASK 0x00200000
#define MUL_RD_MASK 0x000F0000
#define MUL_RN_MASK 0x0000F000
#define MUL_RS_MASK 0x00000F00
#define MUL_RM_MASK 0x0000000F

// SDT masks
#define SDT_OFFSET_MASK 0x00000FFF
#define P_MASK 0x01000000
#define U_MASK 0x00800000
#define L_MASK 0x00100000

// Endian flipping masks
#define TWO_BYTES 0xFF000000
#define FOUR_BYTES 0x00FF0000
#define SIX_BYTES 0x0000FF00
#define EIGHT_BYTES 0x000000FF
#define OUTER_SHIFT 24
#define INNER_SHIFT 8

//masks for the gpio pins
#define PIN_0_9 0x20200000
#define PIN_10_19 0x20200004
#define PIN_20_29 0x20200008
#define PIN_ON 0x2020001c
#define PIN_OFF 0x20200028
#endif
