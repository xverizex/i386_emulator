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
void opcode_pop_ds (struct emu_i386 *emu);
void opcode_and_rm8_r8 (struct emu_i386 *emu);
void opcode_and_rm1632_r1632 (struct emu_i386 *emu);
void opcode_and_r8_rm8 (struct emu_i386 *emu);
void opcode_and_r1632_rm1632 (struct emu_i386 *emu);
void opcode_and_al_imm8 (struct emu_i386 *emu);
void opcode_and_axeax_imm1632 (struct emu_i386 *emu);
void opcode_daa (struct emu_i386 *emu);
void opcode_sbb_rm8_r8 (struct emu_i386 *emu);
void opcode_sbb_rm1632_r1632 (struct emu_i386 *emu);
void opcode_sbb_r8_rm8 (struct emu_i386 *emu);
void opcode_sbb_r1632_rm1632 (struct emu_i386 *emu);
void opcode_sbb_al_imm8 (struct emu_i386 *emu);
void opcode_sbb_axeax_imm1632 (struct emu_i386 *emu);
void opcode_sub_rm8_r8 (struct emu_i386 *emu);
void opcode_sub_rm1632_r1632 (struct emu_i386 *emu);
void opcode_sub_r8_rm8 (struct emu_i386 *emu);
void opcode_sub_r1632_rm1632 (struct emu_i386 *emu);
void opcode_sub_al_imm8 (struct emu_i386 *emu);
void opcode_sub_axeax_imm1632 (struct emu_i386 *emu);
void opcode_das (struct emu_i386 *emu);
void opcode_xor_rm8_r8 (struct emu_i386 *emu);
void opcode_xor_rm1632_r1632 (struct emu_i386 *emu);
void opcode_xor_r8_rm8 (struct emu_i386 *emu);
void opcode_xor_r1632_rm1632 (struct emu_i386 *emu);
void opcode_xor_al_imm8 (struct emu_i386 *emu);
void opcode_xor_axeax_imm1632 (struct emu_i386 *emu);

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
		opcode_sbb_rm8_r8,               /* 0x18 */
		opcode_sbb_rm1632_r1632,         /* 0x19 */
		opcode_sbb_r8_rm8,               /* 0x1a */
		opcode_sbb_r1632_rm1632,         /* 0x1b */
		opcode_sbb_al_imm8,              /* 0x1c */
		opcode_sbb_axeax_imm1632,        /* 0x1d */
		opcode_push_ds,                  /* 0x1e */
		opcode_pop_ds,                   /* 0x1f */
		opcode_and_rm8_r8,               /* 0x20 */
		opcode_and_rm1632_r1632,         /* 0x21 */
		opcode_and_r8_rm8,               /* 0x22 */
		opcode_and_r1632_rm1632,         /* 0x23 */
		opcode_and_al_imm8,              /* 0x24 */
		opcode_and_axeax_imm1632,        /* 0x25 */
		opcode_none,                     /* 0x26 */
		opcode_daa,                      /* 0x27 */
		opcode_sub_rm8_r8,               /* 0x28 */
		opcode_sub_rm1632_r1632,         /* 0x29 */
		opcode_sub_r8_rm8,               /* 0x2a */
		opcode_sub_r1632_rm1632,         /* 0x2b */
		opcode_sub_al_imm8,              /* 0x2c */
		opcode_sub_axeax_imm1632,        /* 0x2d */
		opcode_none,                     /* 0x2e */
		opcode_das,                      /* 0x2f */
		opcode_xor_rm8_r8,               /* 0x30 */
		opcode_xor_rm1632_r1632,         /* 0x31 */
		opcode_xor_r8_rm8,               /* 0x32 */
		opcode_xor_r1632_rm1632,         /* 0x33 */
		opcode_xor_al_imm8,              /* 0x34 */
		opcode_xor_axeax_imm1632,        /* 0x35 */
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
