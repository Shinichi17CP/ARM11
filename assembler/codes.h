#ifndef MASKS_H
#define MASKS_H

// OPCODE codes
#define AND 0xE0000000
#define EOR 0xE0200000
#define SUB 0xE0400000
#define RSB 0xE0600000
#define ADD 0xE0800000
#define TST 0xE1000000
#define TEQ 0xE1200000
#define CMP 0xE1400000
#define ORR 0xE1800000
#define MOV 0xE1A00000

// Shift codes
#define LSL 0x00000000
#define LSR 0x00000020
#define ASR 0x00000040
#define ROR 0x00000060
#define SHIFT_BY 0x00000010

// Data Processing codes
#define I_BIT 1 << 25
#define RN_SHIFT 16
#define RD_SHIFT 12
#define INT_SHIFT 7
#define RS_SHIFT 8
#define MAX_IMM 1 << 8
#define S_BIT 1 << 20
#define ROTATE_SHIFT 8

// Branch codes
#define PC_OFFSET 8
#define OFFSET_SHIFT 2
#define OFFSET_BITS_BEFORE 26
#define OFFSET_BITS_AFTER 24
#define BEQ 0x0A000000
#define BNE 0x1A000000
#define BGE 0xAA000000
#define BLT 0xBA000000
#define BGT 0xCA000000
#define BLE 0xDA000000
#define BAL 0xEA000000

// Multiply codes
#define MULTIPLY_DEFAULT 0xE0000090
#define A_SET 0x00200000
#define M_RD_SHIFT 16
#define M_RN_SHIFT 12
#define M_RS_SHIFT 8

// SDT codes
#define MAX_FOR_MOV 0xFF
#define SDT_DEFAULT 0xE4000000
#define SDT_RD_SHIFT 12
#define SDT_RN_SHIFT 16
#define I_SET 0x02000000
#define P_SET 0x01000000
#define U_SET 0x00800000
#define L_SET 0x00100000
#define PC 0x000F0000
#define MAX_EXPRESSIONS 10

// Special Instruction codes
#define ANDEQ 0x00000000
#define MAX_INT 1 << 6

#endif
