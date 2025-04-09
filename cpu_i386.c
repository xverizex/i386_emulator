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
void opcode_aaa (struct emu_i386 *emu);
void opcode_aas (struct emu_i386 *emu);
void opcode_inc_axeax (struct emu_i386 *emu);
void opcode_inc_cxecx (struct emu_i386 *emu);
void opcode_inc_dxedx (struct emu_i386 *emu);
void opcode_inc_bxebx (struct emu_i386 *emu);
void opcode_inc_spesp (struct emu_i386 *emu);
void opcode_inc_bpebp (struct emu_i386 *emu);
void opcode_inc_siesi (struct emu_i386 *emu);
void opcode_inc_diedi (struct emu_i386 *emu);
void opcode_dec_axeax (struct emu_i386 *emu);
void opcode_dec_cxecx (struct emu_i386 *emu);
void opcode_dec_dxedx (struct emu_i386 *emu);
void opcode_dec_bxebx (struct emu_i386 *emu);
void opcode_dec_spesp (struct emu_i386 *emu);
void opcode_dec_bpebp (struct emu_i386 *emu);
void opcode_dec_siesi (struct emu_i386 *emu);
void opcode_dec_diedi (struct emu_i386 *emu);
void opcode_push_axeax (struct emu_i386 *emu);
void opcode_push_cxecx (struct emu_i386 *emu);
void opcode_push_dxedx (struct emu_i386 *emu);
void opcode_push_bxebx (struct emu_i386 *emu);
void opcode_push_spesp (struct emu_i386 *emu);
void opcode_push_bpebp (struct emu_i386 *emu);
void opcode_push_siesi (struct emu_i386 *emu);
void opcode_push_diedi (struct emu_i386 *emu);
void opcode_pop_axeax (struct emu_i386 *emu);
void opcode_pop_cxecx (struct emu_i386 *emu);
void opcode_pop_dxedx (struct emu_i386 *emu);
void opcode_pop_bxebx (struct emu_i386 *emu);
void opcode_pop_spesp (struct emu_i386 *emu);
void opcode_pop_bpebp (struct emu_i386 *emu);
void opcode_pop_siesi (struct emu_i386 *emu);
void opcode_pop_diedi (struct emu_i386 *emu);

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
		opcode_none,                     /* 0x36 */
		opcode_aaa,                      /* 0x37 */
		opcode_cmp_rm8_r8,               /* 0x38 */
		opcode_cmp_rm1632_r1632,         /* 0x39 */
		opcode_cmp_r8_rm8,               /* 0x3a */
		opcode_cmp_r1632_rm1632,         /* 0x3b */
		opcode_cmp_al_imm8,              /* 0x3c */
		opcode_cmp_axeax_imm1632,        /* 0x3d */
		opcode_none,                     /* 0x3e */
		opcode_aas,                      /* 0x3f */
		opcode_inc_axeax,                /* 0x40 */
		opcode_inc_cxecx,                /* 0x41 */
		opcode_inc_dxedx,                /* 0x42 */
		opcode_inc_bxebx,                /* 0x43 */
		opcode_inc_spesp,                /* 0x44 */
		opcode_inc_bpebp,                /* 0x45 */
		opcode_inc_siesi,                /* 0x46 */
		opcode_inc_diedi,                /* 0x47 */
		opcode_dec_axeax,                /* 0x48 */
		opcode_dec_cxecx,                /* 0x49 */
		opcode_dec_dxedx,                /* 0x4a */
		opcode_dec_bxebx,                /* 0x4b */
		opcode_dec_spesp,                /* 0x4c */
		opcode_dec_bpebp,                /* 0x4d */
		opcode_dec_siesi,                /* 0x4e */
		opcode_dec_diedi,                /* 0x4f */
		opcode_push_axeax,               /* 0x50 */
		opcode_push_cxecx,               /* 0x51 */
		opcode_push_dxedx,               /* 0x52 */
		opcode_push_bxebx,               /* 0x53 */
		opcode_push_spesp,               /* 0x54 */
		opcode_push_bpebp,               /* 0x55 */
		opcode_push_siesi,               /* 0x56 */
		opcode_push_diedi,               /* 0x57 */
		opcode_pop_axeax,                /* 0x58 */
		opcode_pop_cxecx,                /* 0x59 */
		opcode_pop_dxedx,                /* 0x5a */
		opcode_pop_bxebx,                /* 0x5b */
		opcode_pop_spesp,                /* 0x5c */
		opcode_pop_bpebp,                /* 0x5d */
		opcode_pop_siesi,                /* 0x5e */
		opcode_pop_diedi,                /* 0x5f */
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
