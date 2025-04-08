#include <stdio.h>
#include "cpu.h"

typedef void (*_handler) (struct emu_i386 *emu);

void opcode_none (struct emu_i386 *emu);
void opcode_add_rm8_r8 (struct emu_i386 *emu);
void opcode_add_rm1632_r1632 (struct emu_i386 *emu);
void opcode_add_r8_rm8 (struct emu_i386 *emu);
void opcode_add_r1632_rm1632 (struct emu_i386 *emu);
void opcode_add_al_imm8 (struct emu_i386 *emu);
void opcode_add_axeax_imm1632 (struct emu_i386 *emu);
void opcode_push_es (struct emu_i386 *emu);
void opcode_pop_es (struct emu_i386 *emu);
void opcode_or_rm8_r8 (struct emu_i386 *emu);
void opcode_or_rm1632_r1632 (struct emu_i386 *emu);
void opcode_or_r8_rm8 (struct emu_i386 *emu);
void opcode_or_r1632_rm1632 (struct emu_i386 *emu);
void opcode_or_al_imm8 (struct emu_i386 *emu);
void opcode_or_axeax_imm1632 (struct emu_i386 *emu);
void opcode_adc_rm8_r8 (struct emu_i386 *emu);
void opcode_adc_rm1632_r1632 (struct emu_i386 *emu);
void opcode_adc_r8_rm8 (struct emu_i386 *emu);
void opcode_adc_r1632_rm1632 (struct emu_i386 *emu);
void opcode_adc_al_imm8 (struct emu_i386 *emu);
void opcode_adc_axeax_imm1632 (struct emu_i386 *emu);
void opcode_push_ss (struct emu_i386 *emu);
void opcode_pop_ss (struct emu_i386 *emu);

static void init (struct emu_i386 *emu)
{
	static _handler handler[256] = {
		opcode_add_rm8_r8,               /* 0x00 */
		opcode_add_rm1632_r1632,         /* 0x01 */
		opcode_add_r8_rm8,               /* 0x02 */
		opcode_add_r1632_rm1632,         /* 0x03 */
		opcode_add_al_imm8,              /* 0x04 */
		opcode_add_axeax_imm1632,        /* 0x05 */
		opcode_push_es,                  /* 0x06 */
		opcode_pop_es,                   /* 0x07 */
		opcode_or_rm8_r8,                /* 0x08 */
		opcode_or_rm1632_r1632,          /* 0x09 */
		opcode_or_r8_rm8,                /* 0x0a */
		opcode_or_r1632_rm1632,          /* 0x0b */
		opcode_or_al_imm8,               /* 0x0c */
		opcode_or_axeax_imm1632,         /* 0x0d */
		opcode_none,                     /* 0x0e */
		opcode_none,                     /* 0x0f */
		opcode_adc_rm8_r8,               /* 0x10 */
		opcode_adc_rm1632_r1632,         /* 0x11 */
		opcode_adc_r8_rm8,               /* 0x12 */
		opcode_adc_r1632_rm1632,         /* 0x13 */
		opcode_adc_al_imm8,              /* 0x14 */
		opcode_adc_axeax_imm1632,        /* 0x15 */
		opcode_push_ss,                  /* 0x16 */
		opcode_pop_ss,                   /* 0x17 */
	};
}

int main (int argc, char **argv)
{
	uint8_t data[] = {0x00, 0x04};
	uint64_t sz = sizeof (data);

	struct emu_i386 emu;
	init (&emu);

	parse (&emu, data, sz);
}
