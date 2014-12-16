/*
 Copyright 2013 Michael Pavone
 This file is part of BlastEm.
 BlastEm is free software distributed under the terms of the GNU General Public License version 3 or greater. See COPYING for full license text.
*/
#include "z80inst.h"
#include <string.h>
#include <stdio.h>

#define NOP {Z80_NOP, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 1}
#define NOP2 {Z80_NOP, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 2}

z80inst z80_tbl_a[256] = {
	//0
	NOP,
	{Z80_LD, Z80_BC, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT | Z80_DIR, Z80_BC, 0},
	{Z80_INC, Z80_BC, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_B, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_B, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_B, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RLC, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_EX, Z80_AF, Z80_REG, Z80_AF, 0},
	{Z80_ADD, Z80_HL, Z80_REG, Z80_BC, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT, Z80_BC, 0},
	{Z80_DEC, Z80_BC, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_C, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_C, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_C, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RRC, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	//1
	{Z80_DJNZ, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_DE, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT | Z80_DIR, Z80_DE, 0},
	{Z80_INC, Z80_DE, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_D, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_D, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_D, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RL, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JR, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_ADD, Z80_HL, Z80_REG, Z80_DE, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT, Z80_DE, 0},
	{Z80_DEC, Z80_DE, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_E, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_E, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_E, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RR, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	//2
	{Z80_JRCC, Z80_CC_NZ, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_HL, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_HL, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_INC, Z80_HL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_H, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_H, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_H, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_DAA, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JRCC, Z80_CC_Z, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_ADD, Z80_HL, Z80_REG, Z80_HL, 0},
	{Z80_LD, Z80_HL, Z80_IMMED_INDIRECT, Z80_IMMED, 0},
	{Z80_DEC, Z80_HL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_L, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_L, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_L, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_CPL, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	//3
	{Z80_JRCC, Z80_CC_NC, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_SP, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_A, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_INC, Z80_SP, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_UNUSED, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_DEC, Z80_UNUSED, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_USE_IMMED, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_SCF, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JRCC, Z80_CC_C, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_ADD, Z80_HL, Z80_REG, Z80_SP, 0},
	{Z80_LD, Z80_A, Z80_IMMED_INDIRECT, Z80_IMMED, 0},
	{Z80_DEC, Z80_SP, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_CCF, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	//4
	{Z80_LD, Z80_B, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_B, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_A, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_C, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_A, 0},
	//5
	{Z80_LD, Z80_D, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_D, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_A, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_E, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_A, 0},
	//6
	{Z80_LD, Z80_H, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_H, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_H, Z80_REG, Z80_A, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_L, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_L, Z80_REG, Z80_A, 0},
	//7
	{Z80_LD, Z80_B, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_C, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_D, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_E, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_H, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_L, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_HALT, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT | Z80_DIR, Z80_HL, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_LD, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_A, 0},
	//8
	{Z80_ADD, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_ADD, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_A, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_ADC, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_A, 0},
	//9
	{Z80_SUB, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_SUB, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_A, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_SBC, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_A, 0},
	//A
	{Z80_AND, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_AND, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_A, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_XOR, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_A, 0},
	//B
	{Z80_OR, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_OR, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_A, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_B, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_C, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_D, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_E, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_H, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_L, 0},
	{Z80_CP, Z80_A, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_A, 0},
	//C
	{Z80_RETCC, Z80_CC_NZ, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_POP, Z80_BC, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_NZ, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_JP, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_CALLCC, Z80_CC_NZ, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_PUSH, Z80_BC, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_ADD, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x0},
	{Z80_RETCC, Z80_CC_Z, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RET, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_Z, Z80_IMMED, Z80_UNUSED, 0},
	{0, 0, 0, 0, 0},//BITS Prefix
	{Z80_CALLCC, Z80_CC_Z, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_CALL, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_ADC, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x8},
	//D
	{Z80_RETCC, Z80_CC_NC, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_POP, Z80_DE, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_NC, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_OUT, Z80_A, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_CALLCC, Z80_CC_NC, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_PUSH, Z80_DE, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_SUB, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x10},
	{Z80_RETCC, Z80_CC_C, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_EXX, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_C, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_IN, Z80_A, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_CALLCC, Z80_CC_C, Z80_IMMED, Z80_UNUSED, 0},
	{0, 0, 0, 0, 0},//IX Prefix
	{Z80_SBC, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x18},
	//E
	{Z80_RETCC, Z80_CC_PO, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_POP, Z80_HL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_PO, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_EX, Z80_HL, Z80_REG_INDIRECT | Z80_DIR, Z80_SP, 0},
	{Z80_CALLCC, Z80_CC_PO, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_PUSH, Z80_HL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_AND, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x20},
	{Z80_RETCC, Z80_CC_PE, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JP, Z80_UNUSED, Z80_REG_INDIRECT, Z80_HL, 0},
	{Z80_JPCC, Z80_CC_PE, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_EX, Z80_DE, Z80_REG, Z80_HL, 0},
	{Z80_CALLCC, Z80_CC_PE, Z80_IMMED, Z80_UNUSED, 0},
	{0, 0, 0, 0, 0},//EXTD Prefix
	{Z80_XOR, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x28},
	//F
	{Z80_RETCC, Z80_CC_P, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_POP, Z80_AF, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_JPCC, Z80_CC_P, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_DI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CALLCC, Z80_CC_P, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_PUSH, Z80_AF, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_OR, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x30},
	{Z80_RETCC, Z80_CC_M, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_SP, Z80_REG, Z80_HL, 0},
	{Z80_JPCC, Z80_CC_M, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_EI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CALLCC, Z80_CC_M, Z80_IMMED, Z80_UNUSED, 0},
	{0, 0, 0, 0, 0},//IY Prefix
	{Z80_CP, Z80_A, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RST, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0x38}
};

z80inst z80_tbl_extd[0xC0-0x40] = {
	//4
	{Z80_IN, Z80_B, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_B, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_SBC, Z80_HL, Z80_REG, Z80_BC, 0},
	{Z80_LD, Z80_BC, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_I, Z80_REG, Z80_A, 0},
	{Z80_IN, Z80_C, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_C, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_ADC, Z80_HL, Z80_REG, Z80_BC, 0},
	{Z80_LD, Z80_BC, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 3},//Set undocumented mode 0/1
	{Z80_LD, Z80_R, Z80_REG, Z80_A, 0},
	//5
	{Z80_IN, Z80_D, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_D, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_SBC, Z80_HL, Z80_REG, Z80_DE, 0},
	{Z80_LD, Z80_DE, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 1},
	{Z80_LD, Z80_A, Z80_REG, Z80_I, 0},
	{Z80_IN, Z80_E, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_E, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_ADC, Z80_HL, Z80_REG, Z80_DE, 0},
	{Z80_LD, Z80_DE, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 2},
	{Z80_LD, Z80_A, Z80_REG, Z80_R, 0},
	//6
	{Z80_IN, Z80_H, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_H, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_SBC, Z80_HL, Z80_REG, Z80_HL, 0},
	{Z80_LD, Z80_HL, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_RRD, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IN, Z80_L, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_L, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_ADC, Z80_HL, Z80_REG, Z80_HL, 0},
	{Z80_LD, Z80_HL, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 3},//Set undocumented mode 0/1
	{Z80_RLD, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	//7
	{Z80_IN, Z80_UNUSED, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_USE_IMMED, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_SBC, Z80_HL, Z80_REG, Z80_SP, 0},
	{Z80_LD, Z80_SP, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 1},
	NOP2,
	{Z80_IN, Z80_A, Z80_REG_INDIRECT, Z80_C, 0},
	{Z80_OUT, Z80_A, Z80_REG_INDIRECT | Z80_DIR, Z80_C, 0},
	{Z80_ADC, Z80_HL, Z80_REG, Z80_SP, 0},
	{Z80_LD, Z80_SP, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_NEG, Z80_A, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_RETN, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IM, Z80_UNUSED, Z80_IMMED, Z80_UNUSED, 2},
	NOP2,
	//8
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//9
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//A
	{Z80_LDI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CPI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_OUTI, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LDD, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CPD, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_IND, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_OUTD, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//B
	{Z80_LDIR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CPIR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INIR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_OTIR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LDDR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_CPDR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INDR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_OTDR, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2
};

#define SHIFT_BLOCK(op) \
	{op, Z80_B, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_C, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_D, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_E, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_H, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_L, Z80_UNUSED, Z80_UNUSED, 1},\
	{op, Z80_UNUSED, Z80_REG_INDIRECT, Z80_HL, 1},\
	{op, Z80_A, Z80_UNUSED, Z80_UNUSED, 1}

#define BIT_BLOCK(op, bit) \
	{op, Z80_USE_IMMED, Z80_REG, Z80_B, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_C, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_D, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_E, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_H, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_L, bit},\
	{op, Z80_USE_IMMED, Z80_REG_INDIRECT, Z80_HL, bit},\
	{op, Z80_USE_IMMED, Z80_REG, Z80_A, bit}

z80inst z80_tbl_bit[256] = {
	//0
	SHIFT_BLOCK(Z80_RLC),
	SHIFT_BLOCK(Z80_RRC),
	//1
	SHIFT_BLOCK(Z80_RL),
	SHIFT_BLOCK(Z80_RR),
	//2
	SHIFT_BLOCK(Z80_SLA),
	SHIFT_BLOCK(Z80_SRA),
	//3
	SHIFT_BLOCK(Z80_SLL),
	SHIFT_BLOCK(Z80_SRL),
	//4
	BIT_BLOCK(Z80_BIT, 0),
	BIT_BLOCK(Z80_BIT, 1),
	//5
	BIT_BLOCK(Z80_BIT, 2),
	BIT_BLOCK(Z80_BIT, 3),
	//6
	BIT_BLOCK(Z80_BIT, 4),
	BIT_BLOCK(Z80_BIT, 5),
	//7
	BIT_BLOCK(Z80_BIT, 6),
	BIT_BLOCK(Z80_BIT, 7),
	//8
	BIT_BLOCK(Z80_RES, 0),
	BIT_BLOCK(Z80_RES, 1),
	//9
	BIT_BLOCK(Z80_RES, 2),
	BIT_BLOCK(Z80_RES, 3),
	//A
	BIT_BLOCK(Z80_RES, 4),
	BIT_BLOCK(Z80_RES, 5),
	//B
	BIT_BLOCK(Z80_RES, 6),
	BIT_BLOCK(Z80_RES, 7),
	//C
	BIT_BLOCK(Z80_SET, 0),
	BIT_BLOCK(Z80_SET, 1),
	//D
	BIT_BLOCK(Z80_SET, 2),
	BIT_BLOCK(Z80_SET, 3),
	//E
	BIT_BLOCK(Z80_SET, 4),
	BIT_BLOCK(Z80_SET, 5),
	//F
	BIT_BLOCK(Z80_SET, 6),
	BIT_BLOCK(Z80_SET, 7)
};

z80inst z80_tbl_ix[256] = {
	//0
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IX, Z80_REG, Z80_BC, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//1
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IX, Z80_REG, Z80_DE, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//2
	NOP2,
	{Z80_LD, Z80_IX, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IX, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_INC, Z80_IX, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_IXH, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IXH, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IXH, Z80_IMMED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IX, Z80_REG, Z80_IX, 0},
	{Z80_LD, Z80_IX, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IX, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_IXL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IXL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IXL, Z80_IMMED, Z80_UNUSED, 0},
	NOP2,
	//3
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_INC, Z80_UNUSED, Z80_IX_DISPLACE, 0, 0},
	{Z80_DEC, Z80_UNUSED, Z80_IX_DISPLACE, 0, 0},
	{Z80_LD, Z80_USE_IMMED, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IX, Z80_REG, Z80_SP, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//4
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_B, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_B, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_C, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_C, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//5
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_D, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_D, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_E, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_E, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//6
	{Z80_LD, Z80_IXH, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_H, Z80_IX_DISPLACE, 0, 0},
	{Z80_LD, Z80_IXH, Z80_REG, Z80_A, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_L, Z80_IX_DISPLACE, 0, 0},
	{Z80_LD, Z80_IXL, Z80_REG, Z80_A, 0},
	//7
	{Z80_LD, Z80_B, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_C, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_D, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_E, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_H, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_L, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	{Z80_LD, Z80_A, Z80_IX_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_LD, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//8
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_ADD, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADC, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_ADC, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//9
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_SUB, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_SUB, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_SBC, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_SBC, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//A
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_AND, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_AND, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_XOR, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_XOR, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//B
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_OR, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_OR, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_CP, Z80_A, Z80_REG, Z80_IXH, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_IXL, 0},
	{Z80_CP, Z80_A, Z80_IX_DISPLACE, 0, 0},
	NOP2,
	//C
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//D
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//E
	NOP2,
	{Z80_POP, Z80_IX, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	{Z80_EX, Z80_IX, Z80_REG_INDIRECT | Z80_DIR, Z80_SP, 0},
	NOP2,
	{Z80_PUSH, Z80_IX, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	{Z80_JP, Z80_UNUSED, Z80_REG_INDIRECT, Z80_IX, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//F
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_SP, Z80_REG, Z80_IX, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2
};

#define SHIFT_BLOCK_IX(op) \
	{op, Z80_B, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_C, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_D, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_E, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_H, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_L, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_UNUSED, Z80_IX_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_A, Z80_IX_DISPLACE | Z80_DIR, 0, 1}

#define BIT_BLOCK_IX(bit) \
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit}

#define BIT_BLOCK_IX_REG(op, bit) \
	{op, Z80_B, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_C, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_D, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_E, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_H, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_L, Z80_IX_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_USE_IMMED, Z80_IX_DISPLACE, 0, bit},\
	{op, Z80_A, Z80_IX_DISPLACE | Z80_DIR, 0, bit}

z80inst z80_tbl_ix_bit[256] = {
	//0
	SHIFT_BLOCK_IX(Z80_RLC),
	SHIFT_BLOCK_IX(Z80_RRC),
	//1
	SHIFT_BLOCK_IX(Z80_RL),
	SHIFT_BLOCK_IX(Z80_RR),
	//2
	SHIFT_BLOCK_IX(Z80_SLA),
	SHIFT_BLOCK_IX(Z80_SRA),
	//3
	SHIFT_BLOCK_IX(Z80_SLL),
	SHIFT_BLOCK_IX(Z80_SRL),
	//4
	BIT_BLOCK_IX(0),
	BIT_BLOCK_IX(1),
	//5
	BIT_BLOCK_IX(2),
	BIT_BLOCK_IX(3),
	//6
	BIT_BLOCK_IX(4),
	BIT_BLOCK_IX(5),
	//7
	BIT_BLOCK_IX(6),
	BIT_BLOCK_IX(7),
	//8
	BIT_BLOCK_IX_REG(Z80_RES, 0),
	BIT_BLOCK_IX_REG(Z80_RES, 1),
	//9
	BIT_BLOCK_IX_REG(Z80_RES, 2),
	BIT_BLOCK_IX_REG(Z80_RES, 3),
	//A
	BIT_BLOCK_IX_REG(Z80_RES, 4),
	BIT_BLOCK_IX_REG(Z80_RES, 5),
	//B
	BIT_BLOCK_IX_REG(Z80_RES, 6),
	BIT_BLOCK_IX_REG(Z80_RES, 7),
	//C
	BIT_BLOCK_IX_REG(Z80_SET, 0),
	BIT_BLOCK_IX_REG(Z80_SET, 1),
	//D
	BIT_BLOCK_IX_REG(Z80_SET, 2),
	BIT_BLOCK_IX_REG(Z80_SET, 3),
	//E
	BIT_BLOCK_IX_REG(Z80_SET, 4),
	BIT_BLOCK_IX_REG(Z80_SET, 5),
	//F
	BIT_BLOCK_IX_REG(Z80_SET, 6),
	BIT_BLOCK_IX_REG(Z80_SET, 7),
};

z80inst z80_tbl_iy[256] = {
	//0
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IY, Z80_REG, Z80_BC, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//1
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IY, Z80_REG, Z80_DE, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//2
	NOP2,
	{Z80_LD, Z80_IY, Z80_IMMED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IY, Z80_IMMED_INDIRECT | Z80_DIR, Z80_UNUSED, 0},
	{Z80_INC, Z80_IY, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_IYH, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IYH, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IYH, Z80_IMMED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IY, Z80_REG, Z80_IY, 0},
	{Z80_LD, Z80_IY, Z80_IMMED_INDIRECT, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IY, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_INC, Z80_IYL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_DEC, Z80_IYL, Z80_UNUSED, Z80_UNUSED, 0},
	{Z80_LD, Z80_IYL, Z80_IMMED, Z80_UNUSED, 0},
	NOP2,
	//3
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_INC, Z80_UNUSED, Z80_IY_DISPLACE, 0, 0},
	{Z80_DEC, Z80_UNUSED, Z80_IY_DISPLACE, 0, 0},
	{Z80_LD, Z80_USE_IMMED, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	NOP2,
	{Z80_ADD, Z80_IY, Z80_REG, Z80_SP, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//4
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_B, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_B, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_B, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_C, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_C, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_C, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//5
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_D, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_D, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_D, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_E, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_E, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_E, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//6
	{Z80_LD, Z80_IYH, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_H, Z80_IY_DISPLACE, 0, 0},
	{Z80_LD, Z80_IYH, Z80_REG, Z80_A, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_B, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_C, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_D, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_E, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_L, Z80_IY_DISPLACE, 0, 0},
	{Z80_LD, Z80_IYL, Z80_REG, Z80_A, 0},
	//7
	{Z80_LD, Z80_B, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_C, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_D, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_E, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_H, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	{Z80_LD, Z80_L, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	{Z80_LD, Z80_A, Z80_IY_DISPLACE | Z80_DIR, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_LD, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_LD, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//8
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADD, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_ADD, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_ADD, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_ADC, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_ADC, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_ADC, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//9
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_SUB, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_SUB, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_SUB, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_SBC, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_SBC, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_SBC, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//A
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_AND, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_AND, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_AND, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_XOR, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_XOR, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_XOR, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//B
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_OR, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_OR, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_OR, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_CP, Z80_A, Z80_REG, Z80_IYH, 0},
	{Z80_CP, Z80_A, Z80_REG, Z80_IYL, 0},
	{Z80_CP, Z80_A, Z80_IY_DISPLACE, 0, 0},
	NOP2,
	//C
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//D
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//E
	NOP2,
	{Z80_POP, Z80_IY, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	{Z80_EX, Z80_IY, Z80_REG_INDIRECT | Z80_DIR, Z80_SP, 0},
	NOP2,
	{Z80_PUSH, Z80_IY, Z80_UNUSED, Z80_UNUSED, 0},
	NOP2,
	NOP2,
	NOP2,
	{Z80_JP, Z80_UNUSED, Z80_REG_INDIRECT, Z80_IY, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//F
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	{Z80_LD, Z80_SP, Z80_REG, Z80_IY, 0},
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	NOP2,
	//TODO: Enable this based on a define
	{Z80_NOP, Z80_UNUSED, Z80_UNUSED, Z80_UNUSED, 42}
	//NOP2
};

#define SHIFT_BLOCK_IY(op) \
	{op, Z80_B, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_C, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_D, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_E, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_H, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_L, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_UNUSED, Z80_IY_DISPLACE | Z80_DIR, 0, 1},\
	{op, Z80_A, Z80_IY_DISPLACE | Z80_DIR, 0, 1}

#define BIT_BLOCK_IY(bit) \
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{Z80_BIT, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit}

#define BIT_BLOCK_IY_REG(op, bit) \
	{op, Z80_B, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_C, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_D, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_E, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_H, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_L, Z80_IY_DISPLACE | Z80_DIR, 0, bit},\
	{op, Z80_USE_IMMED, Z80_IY_DISPLACE, 0, bit},\
	{op, Z80_A, Z80_IY_DISPLACE | Z80_DIR, 0, bit}

z80inst z80_tbl_iy_bit[256] = {
	//0
	SHIFT_BLOCK_IY(Z80_RLC),
	SHIFT_BLOCK_IY(Z80_RRC),
	//1
	SHIFT_BLOCK_IY(Z80_RL),
	SHIFT_BLOCK_IY(Z80_RR),
	//2
	SHIFT_BLOCK_IY(Z80_SLA),
	SHIFT_BLOCK_IY(Z80_SRA),
	//3
	SHIFT_BLOCK_IY(Z80_SLL),
	SHIFT_BLOCK_IY(Z80_SRL),
	//4
	BIT_BLOCK_IY(0),
	BIT_BLOCK_IY(1),
	//5
	BIT_BLOCK_IY(2),
	BIT_BLOCK_IY(3),
	//6
	BIT_BLOCK_IY(4),
	BIT_BLOCK_IY(5),
	//7
	BIT_BLOCK_IY(6),
	BIT_BLOCK_IY(7),
	//8
	BIT_BLOCK_IY_REG(Z80_RES, 0),
	BIT_BLOCK_IY_REG(Z80_RES, 1),
	//9
	BIT_BLOCK_IY_REG(Z80_RES, 2),
	BIT_BLOCK_IY_REG(Z80_RES, 3),
	//A
	BIT_BLOCK_IY_REG(Z80_RES, 4),
	BIT_BLOCK_IY_REG(Z80_RES, 5),
	//B
	BIT_BLOCK_IY_REG(Z80_RES, 6),
	BIT_BLOCK_IY_REG(Z80_RES, 7),
	//C
	BIT_BLOCK_IY_REG(Z80_SET, 0),
	BIT_BLOCK_IY_REG(Z80_SET, 1),
	//D
	BIT_BLOCK_IY_REG(Z80_SET, 2),
	BIT_BLOCK_IY_REG(Z80_SET, 3),
	//E
	BIT_BLOCK_IY_REG(Z80_SET, 4),
	BIT_BLOCK_IY_REG(Z80_SET, 5),
	//F
	BIT_BLOCK_IY_REG(Z80_SET, 6),
	BIT_BLOCK_IY_REG(Z80_SET, 7),
};

uint8_t * z80_decode(uint8_t * istream, z80inst * decoded)
{
	uint8_t tmp;
	if (*istream == 0xCB) {
		istream++;
		memcpy(decoded, z80_tbl_bit + *istream, sizeof(z80inst));
	} else if (*istream == 0xDD) {
		istream++;
		if (*istream == 0xCB) {
			tmp = *(++istream);
			istream++;
			memcpy(decoded, z80_tbl_ix_bit + *istream, sizeof(z80inst));
			decoded->ea_reg = tmp;
		} else {
			memcpy(decoded, z80_tbl_ix + *istream, sizeof(z80inst));
			if ((decoded->addr_mode & 0x1F) == Z80_IX_DISPLACE) {
				decoded->ea_reg = *(++istream);
			}
		}
	} else if (*istream == 0xED) {
		istream++;
		if (*istream < 0x40 || *istream >= 0xC0) {
			memcpy(decoded, z80_tbl_extd + 0xBF, sizeof(z80inst));
		} else {
			memcpy(decoded, z80_tbl_extd + *istream-0x40, sizeof(z80inst));
		}
	} else if (*istream == 0xFD) {
		istream++;
		if (*istream == 0xCB) {
			tmp = *(++istream);
			istream++;
			memcpy(decoded, z80_tbl_iy_bit + *istream, sizeof(z80inst));
			decoded->ea_reg = tmp;
		} else {
			memcpy(decoded, z80_tbl_iy + *istream, sizeof(z80inst));
			if ((decoded->addr_mode & 0x1F) == Z80_IY_DISPLACE) {
				decoded->ea_reg = *(++istream);
			}
		}
	} else {
		memcpy(decoded, z80_tbl_a + *istream, sizeof(z80inst));

	}
	if ((decoded->addr_mode & 0x1F) == Z80_IMMED && decoded->op != Z80_RST && decoded->op != Z80_IM) {
		decoded->immed = *(++istream);
		if ((decoded->reg >= Z80_BC && decoded->reg < Z80_UNUSED) || decoded->op == Z80_CALL || decoded->op == Z80_CALLCC || decoded->op == Z80_JP || decoded->op == Z80_JPCC) {
			decoded->immed |= *(++istream) << 8;
		} else if (decoded->immed & 0x80) {
			decoded->immed |= 0xFF00;
		}
	} else if ((decoded->addr_mode & 0x1F) == Z80_IMMED_INDIRECT) {
		decoded->immed = *(++istream);
		if (decoded->op != Z80_OUT && decoded->op != Z80_IN) {
			decoded->immed |= *(++istream) << 8;
		}
	}
	if (decoded->reg == Z80_USE_IMMED && decoded->op != Z80_BIT && decoded->op != Z80_RES && decoded->op != Z80_SET) {
		decoded->immed = *(++istream);
	}
	return istream+1;
}

char *z80_mnemonics[Z80_OTDR+1] = {
	"ld",
	"push",
	"pop",
	"ex",
	"exx",
	"ldi",
	"ldir",
	"ldd",
	"lddr",
	"cpi",
	"cpir",
	"cpd",
	"cpdr",
	"add",
	"adc",
	"sub",
	"sbc",
	"and",
	"or",
	"xor",
	"cp",
	"inc",
	"dec",
	"daa",
	"cpl",
	"neg",
	"ccf",
	"scf",
	"nop",
	"halt",
	"di",
	"ei",
	"im",
	"rlc",
	"rl",
	"rrc",
	"rr",
	"sla",
	"sra",
	"sll",
	"srl",
	"rld",
	"rrd",
	"bit",
	"set",
	"res",
	"jp",
	"jp",
	"jr",
	"jr",
	"djnz",
	"call",
	"call",
	"ret",
	"ret",
	"reti",
	"retn",
	"rst",
	"in",
	"ini",
	"inir",
	"ind",
	"indr",
	"out",
	"outi",
	"otir",
	"outd",
	"otdr"
};

char * z80_regs[Z80_USE_IMMED] = {
	"c",
	"b",
	"e",
	"d",
	"l",
	"h",
	"ixl",
	"ixh",
	"iyl",
	"iyh",
	"i",
	"r",
	"a",
	"bc",
	"de",
	"hl",
	"sp",
	"af",
	"ix",
	"iy",
};

char * z80_conditions[Z80_CC_M+1] = {
	"nz",
	"z",
	"nc",
	"c",
	"po",
	"pe",
	"p",
	"m"
};

int z80_disasm(z80inst * decoded, char * dst, uint16_t address)
{
	int len = sprintf(dst, "%s", z80_mnemonics[decoded->op]);
	uint8_t needcomma;
	if (decoded->addr_mode & Z80_DIR) {
		needcomma = 1;
		switch (decoded->addr_mode & 0x1F)
		{
		case Z80_REG:
			len += sprintf(dst+len,  " %s", z80_regs[decoded->ea_reg]);
			break;
		case Z80_REG_INDIRECT:
			len += sprintf(dst+len,  " (%s)", z80_regs[decoded->ea_reg]);
			break;
		case Z80_IMMED:
			if (decoded->immed >= 63 || decoded->op == Z80_JP || decoded->op == Z80_JPCC || decoded->op == Z80_CALL || decoded->op == Z80_CALLCC || decoded->op == Z80_RST)
			{
				len += sprintf(dst+len, " $%X", decoded->immed);
			} else {
				len += sprintf(dst+len, " %d", decoded->immed);
			}
			break;
		case Z80_IMMED_INDIRECT:
			len += sprintf(dst+len, " ($%X)", decoded->immed);
			break;
		case Z80_IX_DISPLACE:
			len += sprintf(dst+len, " (ix+%d)", decoded->ea_reg & 0x80 ? decoded->ea_reg - 256 : decoded->ea_reg);
			break;
		case Z80_IY_DISPLACE:
			len += sprintf(dst+len, " (iy+%d)", decoded->ea_reg & 0x80 ? decoded->ea_reg - 256 : decoded->ea_reg);
			break;
		default:
			needcomma = 0;
		}
		if (decoded->reg & Z80_IMMED_FLAG) {
			len += sprintf(dst+len, "%s %d", needcomma ? "," : "", decoded->immed);
		}
		if ((decoded->reg & 0x1F) != Z80_UNUSED) {
			if (decoded->op == Z80_JRCC || decoded->op == Z80_JPCC || decoded->op == Z80_CALLCC || decoded->op == Z80_RETCC) {
				len += sprintf(dst+len,  "%s %s", needcomma ? "," : "", z80_conditions[decoded->reg & 0x1F]);
			} else {
				len += sprintf(dst+len,  "%s %s", needcomma ? "," : "", z80_regs[decoded->reg & 0x1F]);
			}
		}
	} else {
		needcomma = 0;
		if (decoded->reg & Z80_IMMED_FLAG) {
			len += sprintf(dst+len, " %d", decoded->immed);
			needcomma = 1;
		}
		if ((decoded->reg & 0x1F) != Z80_UNUSED) {
			if (decoded->op == Z80_JRCC || decoded->op == Z80_JPCC || decoded->op == Z80_CALLCC || decoded->op == Z80_RETCC) {
				len += sprintf(dst+len,  " %s", z80_conditions[decoded->reg & 0x1F]);
			} else {
				len += sprintf(dst+len,  " %s", z80_regs[decoded->reg & 0x1F]);
			}
			needcomma = 1;
		}
		switch (decoded->addr_mode)
		{
		case Z80_REG:
			len += sprintf(dst+len,  "%s %s", needcomma ? "," : "" , z80_regs[decoded->ea_reg]);
			break;
		case Z80_REG_INDIRECT:
			len += sprintf(dst+len,  "%s (%s)", needcomma ? "," : "" , z80_regs[decoded->ea_reg]);
			break;
		case Z80_IMMED:
			if (decoded->op == Z80_JR || decoded->op == Z80_JRCC || decoded->op == Z80_DJNZ) {
					address += 2 + decoded->immed;
					len += sprintf(dst+len, "%s %X", needcomma ? "," : "" , address);
			} else if (decoded->immed >= 63 || decoded->op == Z80_JP || decoded->op == Z80_JPCC || decoded->op == Z80_CALL || decoded->op == Z80_CALLCC || decoded->op == Z80_RST)
			{
				len += sprintf(dst+len, "%s $%X", needcomma ? "," : "" , decoded->immed);
			} else {
				len += sprintf(dst+len, "%s %d", needcomma ? "," : "" , decoded->immed);
			}
			break;
		case Z80_IMMED_INDIRECT:
			len += sprintf(dst+len, "%s ($%X)", needcomma ? "," : "" , decoded->immed);
			break;
		case Z80_IX_DISPLACE:
			len += sprintf(dst+len, "%s (ix+%d)", needcomma ? "," : "" , decoded->ea_reg & 0x80 ? decoded->ea_reg - 256 : decoded->ea_reg);
			break;
		case Z80_IY_DISPLACE:
			len += sprintf(dst+len, "%s (iy+%d)", needcomma ? "," : "" , decoded->ea_reg & 0x80 ? decoded->ea_reg - 256 : decoded->ea_reg);
			break;
		}
	}
	return len;
}

uint8_t z80_high_reg(uint8_t reg)
{
	switch(reg)
	{
	case Z80_C:
	case Z80_BC:
		return Z80_B;
	case Z80_E:
	case Z80_DE:
		return Z80_D;
	case Z80_L:
	case Z80_HL:
		return Z80_H;
	case Z80_IXL:
	case Z80_IX:
		return Z80_IXH;
	case Z80_IYL:
	case Z80_IY:
		return Z80_IYH;
	default:
		return Z80_UNUSED;
	}
}

uint8_t z80_low_reg(uint8_t reg)
{
	switch(reg)
	{
	case Z80_B:
	case Z80_BC:
		return Z80_C;
	case Z80_D:
	case Z80_DE:
		return Z80_E;
	case Z80_H:
	case Z80_HL:
		return Z80_L;
	case Z80_IXH:
	case Z80_IX:
		return Z80_IXL;
	case Z80_IYH:
	case Z80_IY:
		return Z80_IYL;
	default:
		return Z80_UNUSED;
	}
}

uint8_t z80_word_reg(uint8_t reg)
{
	switch(reg)
	{
	case Z80_B:
	case Z80_C:
		return Z80_BC;
	case Z80_D:
	case Z80_E:
		return Z80_DE;
	case Z80_H:
	case Z80_L:
		return Z80_HL;
	case Z80_IXH:
	case Z80_IXL:
		return Z80_IX;
	case Z80_IYH:
	case Z80_IYL:
		return Z80_IY;
	default:
		return Z80_UNUSED;
	}
}

uint8_t z80_is_terminal(z80inst * inst)
{
	return inst->op == Z80_RET || inst->op == Z80_RETI || inst->op == Z80_RETN || inst->op == Z80_JP
		|| inst->op == Z80_JR || inst->op == Z80_HALT || (inst->op == Z80_NOP && inst->immed == 42);
}



