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
void opcode_push_ds (struct emu_i386 *emu);
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
void opcode_cmp_rm8_r8 (struct emu_i386 *emu);
void opcode_cmp_rm1632_r1632 (struct emu_i386 *emu);
void opcode_cmp_r8_rm8 (struct emu_i386 *emu);
void opcode_cmp_r1632_rm1632 (struct emu_i386 *emu);
void opcode_cmp_al_imm8 (struct emu_i386 *emu);
void opcode_cmp_axeax_imm1632 (struct emu_i386 *emu);
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
void opcode_bound_r1632_m1632 (struct emu_i386 *emu);
void opcode_aprl_rm16_r16 (struct emu_i386 *emu);
void opcode_popa_popad (struct emu_i386 *emu);
void opcode_pusha_pushad (struct emu_i386 *emu);
void opcode_imul_r1632_rm1632_imm1632 (struct emu_i386 *emu);
void opcode_imul_r1632_rm1632_imm8 (struct emu_i386 *emu);
void opcode_insb (struct emu_i386 *emu);
void opcode_inswd (struct emu_i386 *emu);
void opcode_outsb (struct emu_i386 *emu);
void opcode_outswd (struct emu_i386 *emu);
void opcode_push_imm8 (struct emu_i386 *emu);
void opcode_push_imm1632 (struct emu_i386 *emu);
void group_sc (struct emu_i386 *emu);
void opcode_bsf_r1632_rm1632 (struct emu_i386 *emu);
void opcode_bsr_r1632_rm1632 (struct emu_i386 *emu);
void opcode_bt_rm1632_r1632 (struct emu_i386 *emu);
void opcode_group_test_bt_rm1632_imm8 (struct emu_i386 *emu);
void opcode_btc_rm1632_r1632 (struct emu_i386 *emu);
void opcode_btr_rm1632_r1632 (struct emu_i386 *emu);
void opcode_bts_rm1632_r1632 (struct emu_i386 *emu);
void opcode_clts (struct emu_i386 *emu);
void opcode_imul_r1632_rm1632 (struct emu_i386 *emu);
void opcode_ja_rel1632 (struct emu_i386 *emu);
void opcode_jae_rel1632 (struct emu_i386 *emu);
void opcode_jb_rel1632 (struct emu_i386 *emu);
void opcode_jbe_rel1632 (struct emu_i386 *emu);
void opcode_je_rel1632 (struct emu_i386 *emu);
void opcode_jg_rel1632 (struct emu_i386 *emu);
void opcode_jge_rel1632 (struct emu_i386 *emu);
void opcode_jl_rel1632 (struct emu_i386 *emu);
void opcode_jle_rel1632 (struct emu_i386 *emu);
void opcode_jne_rel1632 (struct emu_i386 *emu);
void opcode_jno_rel1632 (struct emu_i386 *emu);
void opcode_jnp_rel1632 (struct emu_i386 *emu);
void opcode_jns_rel1632 (struct emu_i386 *emu);
void opcode_jo_rel1632 (struct emu_i386 *emu);
void opcode_jpe_rel1632 (struct emu_i386 *emu);
void opcode_js_rel1632 (struct emu_i386 *emu);
void opcode_lar_r1632_rm1632 (struct emu_i386 *emu);
void opcode_lgdt_lidt_m1632 (struct emu_i386 *emu);
void opcode_lss_r1632_m1632 (struct emu_i386 *emu);
void opcode_lfs_r1632_m1632 (struct emu_i386 *emu);
void opcode_lgs_r1632_m1632 (struct emu_i386 *emu);
void opcode_lldt_rm16 (struct emu_i386 *emu);
void opcode_lsl_r1632_rm1632 (struct emu_i386 *emu);
void opcode_mov_r32_cr0_cr2_cr3 (struct emu_i386 *emu);
void opcode_mov_r32_dr0 (struct emu_i386 *emu);
void opcode_mov_dr0_r32 (struct emu_i386 *emu);
void opcode_mov_r32_tr67 (struct emu_i386 *emu);
void opcode_mov_tr67_r32 (struct emu_i386 *emu);
void opcode_mov_cr023_r32 (struct emu_i386 *emu);
void opcode_movsx_r1632_rm8 (struct emu_i386 *emu);
void opcode_movsx_r32_rm16 (struct emu_i386 *emu);
void opcode_movzx_r1632_rm8 (struct emu_i386 *emu);
void opcode_movzx_r32_rm16 (struct emu_i386 *emu);
void opcode_pop_fs (struct emu_i386 *emu);
void opcode_pop_gs (struct emu_i386 *emu);
void opcode_push_fs (struct emu_i386 *emu);
void opcode_push_gs (struct emu_i386 *emu);
void opcode_seta_rm8 (struct emu_i386 *emu);
void opcode_setae_rm8 (struct emu_i386 *emu);
void opcode_setb_rm8 (struct emu_i386 *emu);
void opcode_setbe_rm8 (struct emu_i386 *emu);
void opcode_sete_rm8 (struct emu_i386 *emu);
void opcode_setg_rm8 (struct emu_i386 *emu);
void opcode_setge_rm8 (struct emu_i386 *emu);
void opcode_setl_rm8 (struct emu_i386 *emu);
void opcode_setle_rm8 (struct emu_i386 *emu);
void opcode_setne_rm8 (struct emu_i386 *emu);
void opcode_seto_rm8 (struct emu_i386 *emu);
void opcode_setno_rm8 (struct emu_i386 *emu);
void opcode_setns_rm8 (struct emu_i386 *emu);
void opcode_setpe_rm8 (struct emu_i386 *emu);
void opcode_setpo_rm8 (struct emu_i386 *emu);
void opcode_sets_rm8 (struct emu_i386 *emu);
void opcode_shld_rm1632_r1632_imm8 (struct emu_i386 *emu);
void opcode_shld_rm1632_r1632_cl (struct emu_i386 *emu);
void opcode_shrd_rm1632_r1632_imm8 (struct emu_i386 *emu);
void opcode_shrd_rm1632_r1632_cl (struct emu_i386 *emu);

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
		opcode_pusha_pushad,             /* 0x60 */
		opcode_popa_popad,               /* 0x61 */
		opcode_bound_r1632_m1632,        /* 0x62 */
		opcode_aprl_rm16_r16,            /* 0x63 */
		opcode_none,                     /* 0x64 */
		opcode_none,                     /* 0x65 */
		opcode_none,                     /* 0x66 */
		opcode_none,                     /* 0x67 */
		opcode_push_imm1632,             /* 0x68 */
		opcode_imul_r1632_rm1632_imm1632,/* 0x69 */
		opcode_push_imm8,                /* 0x6a */
		opcode_imul_r1632_rm1632_imm8,   /* 0x6b */
		opcode_insb,                     /* 0x6c */
		opcode_inswd,                    /* 0x6d */
		opcode_outsb,                    /* 0x6e */
		opcode_outswd,                   /* 0x6f */
	};

	static _handler group_sc_handler[256] = {
		opcode_lldt_rm16,                /* 0x00 */
		opcode_lgdt_lidt_m1632,          /* 0x01 */
		opcode_lar_r1632_rm1632,         /* 0x02 */
		opcode_lsl_r1632_rm1632,         /* 0x03 */
		opcode_none,                     /* 0x04 */
		opcode_none,                     /* 0x05 */
		opcode_clts,                     /* 0x06 */
		opcode_none,                     /* 0x07 */
		opcode_none,                     /* 0x08 */
		opcode_none,                     /* 0x09 */
		opcode_none,                     /* 0x0a */
		opcode_none,                     /* 0x0b */
		opcode_none,                     /* 0x0c */
		opcode_none,                     /* 0x0d */
		opcode_none,                     /* 0x0e */
		opcode_none,                     /* 0x0f */
		opcode_none,                     /* 0x10 */
		opcode_none,                     /* 0x11 */
		opcode_none,                     /* 0x12 */
		opcode_none,                     /* 0x13 */
		opcode_none,                     /* 0x14 */
		opcode_none,                     /* 0x15 */
		opcode_none,                     /* 0x16 */
		opcode_none,                     /* 0x17 */
		opcode_none,                     /* 0x18 */
		opcode_none,                     /* 0x19 */
		opcode_none,                     /* 0x1a */
		opcode_none,                     /* 0x1b */
		opcode_none,                     /* 0x1c */
		opcode_none,                     /* 0x1d */
		opcode_none,                     /* 0x1e */
		opcode_none,                     /* 0x1f */
		opcode_mov_r32_cr0_cr2_cr3,      /* 0x20 */
		opcode_mov_r32_dr0,              /* 0x21 */
		opcode_mov_cr023_r32,            /* 0x22 */
		opcode_mov_dr0_r32,              /* 0x23 */
		opcode_mov_r32_tr67,             /* 0x24 */
		opcode_none,                     /* 0x25 */
		opcode_mov_tr67_r32,             /* 0x26 */
		opcode_none,                     /* 0x27 */
		opcode_none,                     /* 0x28 */
		opcode_none,                     /* 0x29 */
		opcode_none,                     /* 0x2a */
		opcode_none,                     /* 0x2b */
		opcode_none,                     /* 0x2c */
		opcode_none,                     /* 0x2d */
		opcode_none,                     /* 0x2e */
		opcode_none,                     /* 0x2f */
		opcode_none,                     /* 0x30 */
		opcode_none,                     /* 0x31 */
		opcode_none,                     /* 0x32 */
		opcode_none,                     /* 0x33 */
		opcode_none,                     /* 0x34 */
		opcode_none,                     /* 0x35 */
		opcode_none,                     /* 0x36 */
		opcode_none,                     /* 0x37 */
		opcode_none,                     /* 0x38 */
		opcode_none,                     /* 0x39 */
		opcode_none,                     /* 0x3a */
		opcode_none,                     /* 0x3b */
		opcode_none,                     /* 0x3c */
		opcode_none,                     /* 0x3d */
		opcode_none,                     /* 0x3e */
		opcode_none,                     /* 0x3f */
		opcode_none,                     /* 0x41 */
		opcode_none,                     /* 0x42 */
		opcode_none,                     /* 0x43 */
		opcode_none,                     /* 0x44 */
		opcode_none,                     /* 0x45 */
		opcode_none,                     /* 0x46 */
		opcode_none,                     /* 0x47 */
		opcode_none,                     /* 0x48 */
		opcode_none,                     /* 0x49 */
		opcode_none,                     /* 0x4a */
		opcode_none,                     /* 0x4b */
		opcode_none,                     /* 0x4c */
		opcode_none,                     /* 0x4d */
		opcode_none,                     /* 0x4e */
		opcode_none,                     /* 0x4f */
		opcode_none,                     /* 0x50 */
		opcode_none,                     /* 0x51 */
		opcode_none,                     /* 0x52 */
		opcode_none,                     /* 0x53 */
		opcode_none,                     /* 0x54 */
		opcode_none,                     /* 0x55 */
		opcode_none,                     /* 0x56 */
		opcode_none,                     /* 0x57 */
		opcode_none,                     /* 0x58 */
		opcode_none,                     /* 0x59 */
		opcode_none,                     /* 0x5a */
		opcode_none,                     /* 0x5b */
		opcode_none,                     /* 0x5c */
		opcode_none,                     /* 0x5d */
		opcode_none,                     /* 0x5e */
		opcode_none,                     /* 0x5f */
		opcode_none,                     /* 0x60 */
		opcode_none,                     /* 0x61 */
		opcode_none,                     /* 0x62 */
		opcode_none,                     /* 0x63 */
		opcode_none,                     /* 0x64 */
		opcode_none,                     /* 0x65 */
		opcode_none,                     /* 0x66 */
		opcode_none,                     /* 0x67 */
		opcode_none,                     /* 0x68 */
		opcode_none,                     /* 0x69 */
		opcode_none,                     /* 0x6a */
		opcode_none,                     /* 0x6b */
		opcode_none,                     /* 0x6c */
		opcode_none,                     /* 0x6d */
		opcode_none,                     /* 0x6e */
		opcode_none,                     /* 0x6f */
		opcode_none,                     /* 0x70 */
		opcode_none,                     /* 0x71 */
		opcode_none,                     /* 0x72 */
		opcode_none,                     /* 0x73 */
		opcode_none,                     /* 0x74 */
		opcode_none,                     /* 0x75 */
		opcode_none,                     /* 0x76 */
		opcode_none,                     /* 0x77 */
		opcode_none,                     /* 0x78 */
		opcode_none,                     /* 0x79 */
		opcode_none,                     /* 0x7a */
		opcode_none,                     /* 0x7b */
		opcode_none,                     /* 0x7c */
		opcode_none,                     /* 0x7d */
		opcode_none,                     /* 0x7e */
		opcode_none,                     /* 0x7f */
		opcode_jo_rel1632,               /* 0x80 */
		opcode_jno_rel1632,              /* 0x81 */
		opcode_jb_rel1632,               /* 0x82 */
		opcode_jae_rel1632,              /* 0x83 */
		opcode_je_rel1632,               /* 0x84 */
		opcode_jne_rel1632,              /* 0x85 */
		opcode_jbe_rel1632,              /* 0x86 */
		opcode_ja_rel1632,               /* 0x87 */
		opcode_js_rel1632,               /* 0x88 */
		opcode_jns_rel1632,              /* 0x89 */
		opcode_jpe_rel1632,              /* 0x8a */
		opcode_jnp_rel1632,              /* 0x8b */
		opcode_jl_rel1632,               /* 0x8c */
		opcode_jge_rel1632,              /* 0x8d */
		opcode_jle_rel1632,              /* 0x8e */
		opcode_jg_rel1632,               /* 0x8f */
		opcode_seto_rm8,                 /* 0x90 */
		opcode_setno_rm8,                /* 0x91 */
		opcode_setb_rm8,                 /* 0x92 */
		opcode_setae_rm8,                /* 0x93 */
		opcode_sete_rm8,                 /* 0x94 */
		opcode_setne_rm8,                /* 0x95 */
		opcode_setbe_rm8,                /* 0x96 */
		opcode_seta_rm8,                 /* 0x97 */
		opcode_sets_rm8,                 /* 0x98 */
		opcode_setns_rm8,                /* 0x99 */
		opcode_setpe_rm8,                /* 0x9a */
		opcode_setpo_rm8,                /* 0x9b */
		opcode_setl_rm8,                 /* 0x9c */
		opcode_setge_rm8,                /* 0x9d */
		opcode_setle_rm8,                /* 0x9e */
		opcode_setg_rm8,                 /* 0x9f */
		opcode_push_fs,                  /* 0xa0 */
		opcode_pop_fs,                   /* 0xa1 */
		opcode_none,                     /* 0xa2 */
		opcode_bt_rm1632_r1632,          /* 0xa3 */
		opcode_shld_rm1632_r1632_imm8,   /* 0xa4 */
		opcode_shld_rm1632_r1632_cl,     /* 0xa5 */
		opcode_none,                     /* 0xa6 */
		opcode_none,                     /* 0xa7 */
		opcode_push_gs,                  /* 0xa8 */
		opcode_pop_gs,                   /* 0xa9 */
		opcode_none,                     /* 0xaa */
		opcode_bts_rm1632_r1632,         /* 0xab */
		opcode_shrd_rm1632_r1632_imm8,   /* 0xac */
		opcode_shrd_rm1632_r1632_cl,     /* 0xad */
		opcode_none,                     /* 0xae */
		opcode_imul_r1632_rm1632,        /* 0xaf */
		opcode_none,                     /* 0xb0 */
		opcode_none,                     /* 0xb1 */
		opcode_lss_r1632_m1632,          /* 0xb2 */
		opcode_btr_rm1632_r1632,         /* 0xb3 */
		opcode_lfs_r1632_m1632,          /* 0xb4 */
		opcode_lgs_r1632_m1632,          /* 0xb5 */
		opcode_movzx_r1632_rm8,          /* 0xb6 */
		opcode_movzx_r32_rm16,           /* 0xb7 */
		opcode_none,                     /* 0xb8 */
		opcode_none,                     /* 0xb9 */
		opcode_group_test_bt_rm1632_imm8,/* 0xba */
		opcode_btc_rm1632_r1632,         /* 0xbb */
		opcode_bsf_r1632_rm1632,         /* 0xbc */
		opcode_bsr_r1632_rm1632,         /* 0xbd */
		opcode_movsx_r1632_rm8,          /* 0xbe */
		opcode_movsx_r32_rm16,           /* 0xbf */
		opcode_none,                     /* 0xc0 */
		opcode_none,                     /* 0xc1 */
		opcode_none,                     /* 0xc2 */
		opcode_none,                     /* 0xc3 */
		opcode_none,                     /* 0xc4 */
		opcode_none,                     /* 0xc5 */
		opcode_none,                     /* 0xc6 */
		opcode_none,                     /* 0xc7 */
		opcode_none,                     /* 0xc8 */
		opcode_none,                     /* 0xc9 */
		opcode_none,                     /* 0xca */
		opcode_none,                     /* 0xcb */
		opcode_none,                     /* 0xcc */
		opcode_none,                     /* 0xcd */
		opcode_none,                     /* 0xce */
		opcode_none,                     /* 0xcf */
		opcode_none,                     /* 0xd0 */
		opcode_none,                     /* 0xd1 */
		opcode_none,                     /* 0xd2 */
		opcode_none,                     /* 0xd3 */
		opcode_none,                     /* 0xd4 */
		opcode_none,                     /* 0xd5 */
		opcode_none,                     /* 0xd6 */
		opcode_none,                     /* 0xd7 */
		opcode_none,                     /* 0xd8 */
		opcode_none,                     /* 0xd9 */
		opcode_none,                     /* 0xda */
		opcode_none,                     /* 0xdb */
		opcode_none,                     /* 0xdc */
		opcode_none,                     /* 0xdd */
		opcode_none,                     /* 0xde */
		opcode_none,                     /* 0xdf */
		opcode_none,                     /* 0xe0 */
		opcode_none,                     /* 0xe1 */
		opcode_none,                     /* 0xe2 */
		opcode_none,                     /* 0xe3 */
		opcode_none,                     /* 0xe4 */
		opcode_none,                     /* 0xe5 */
		opcode_none,                     /* 0xe6 */
		opcode_none,                     /* 0xe7 */
		opcode_none,                     /* 0xe8 */
		opcode_none,                     /* 0xe9 */
		opcode_none,                     /* 0xea */
		opcode_none,                     /* 0xeb */
		opcode_none,                     /* 0xec */
		opcode_none,                     /* 0xed */
		opcode_none,                     /* 0xee */
		opcode_none,                     /* 0xef */
		opcode_none,                     /* 0xf0 */
		opcode_none,                     /* 0xf1 */
		opcode_none,                     /* 0xf2 */
		opcode_none,                     /* 0xf3 */
		opcode_none,                     /* 0xf4 */
		opcode_none,                     /* 0xf5 */
		opcode_none,                     /* 0xf6 */
		opcode_none,                     /* 0xf7 */
		opcode_none,                     /* 0xf8 */
		opcode_none,                     /* 0xf9 */
		opcode_none,                     /* 0xfa */
		opcode_none,                     /* 0xfb */
		opcode_none,                     /* 0xfc */
		opcode_none,                     /* 0xfd */
		opcode_none,                     /* 0xfe */
		opcode_none,                     /* 0xff */
	};
#if 0
	static _handler group[256] = {
		opcode_none,                     /* 0x00 */
		opcode_none,                     /* 0x01 */
		opcode_none,                     /* 0x02 */
		opcode_none,                     /* 0x03 */
		opcode_none,                     /* 0x04 */
		opcode_none,                     /* 0x05 */
		opcode_none,                     /* 0x06 */
		opcode_none,                     /* 0x07 */
		opcode_none,                     /* 0x08 */
		opcode_none,                     /* 0x09 */
		opcode_none,                     /* 0x0a */
		opcode_none,                     /* 0x0b */
		opcode_none,                     /* 0x0c */
		opcode_none,                     /* 0x0d */
		opcode_none,                     /* 0x0e */
		opcode_none,                     /* 0x0f */
		opcode_none,                     /* 0x10 */
		opcode_none,                     /* 0x11 */
		opcode_none,                     /* 0x12 */
		opcode_none,                     /* 0x13 */
		opcode_none,                     /* 0x14 */
		opcode_none,                     /* 0x15 */
		opcode_none,                     /* 0x16 */
		opcode_none,                     /* 0x17 */
		opcode_none,                     /* 0x18 */
		opcode_none,                     /* 0x19 */
		opcode_none,                     /* 0x1a */
		opcode_none,                     /* 0x1b */
		opcode_none,                     /* 0x1c */
		opcode_none,                     /* 0x1d */
		opcode_none,                     /* 0x1e */
		opcode_none,                     /* 0x1f */
		opcode_none,                     /* 0x20 */
		opcode_none,                     /* 0x21 */
		opcode_none,                     /* 0x22 */
		opcode_none,                     /* 0x23 */
		opcode_none,                     /* 0x24 */
		opcode_none,                     /* 0x25 */
		opcode_none,                     /* 0x26 */
		opcode_none,                     /* 0x27 */
		opcode_none,                     /* 0x28 */
		opcode_none,                     /* 0x29 */
		opcode_none,                     /* 0x2a */
		opcode_none,                     /* 0x2b */
		opcode_none,                     /* 0x2c */
		opcode_none,                     /* 0x2d */
		opcode_none,                     /* 0x2e */
		opcode_none,                     /* 0x2f */
		opcode_none,                     /* 0x30 */
		opcode_none,                     /* 0x31 */
		opcode_none,                     /* 0x32 */
		opcode_none,                     /* 0x33 */
		opcode_none,                     /* 0x34 */
		opcode_none,                     /* 0x35 */
		opcode_none,                     /* 0x36 */
		opcode_none,                     /* 0x37 */
		opcode_none,                     /* 0x38 */
		opcode_none,                     /* 0x39 */
		opcode_none,                     /* 0x3a */
		opcode_none,                     /* 0x3b */
		opcode_none,                     /* 0x3c */
		opcode_none,                     /* 0x3d */
		opcode_none,                     /* 0x3e */
		opcode_none,                     /* 0x3f */
		opcode_none,                     /* 0x41 */
		opcode_none,                     /* 0x42 */
		opcode_none,                     /* 0x43 */
		opcode_none,                     /* 0x44 */
		opcode_none,                     /* 0x45 */
		opcode_none,                     /* 0x46 */
		opcode_none,                     /* 0x47 */
		opcode_none,                     /* 0x48 */
		opcode_none,                     /* 0x49 */
		opcode_none,                     /* 0x4a */
		opcode_none,                     /* 0x4b */
		opcode_none,                     /* 0x4c */
		opcode_none,                     /* 0x4d */
		opcode_none,                     /* 0x4e */
		opcode_none,                     /* 0x4f */
		opcode_none,                     /* 0x50 */
		opcode_none,                     /* 0x51 */
		opcode_none,                     /* 0x52 */
		opcode_none,                     /* 0x53 */
		opcode_none,                     /* 0x54 */
		opcode_none,                     /* 0x55 */
		opcode_none,                     /* 0x56 */
		opcode_none,                     /* 0x57 */
		opcode_none,                     /* 0x58 */
		opcode_none,                     /* 0x59 */
		opcode_none,                     /* 0x5a */
		opcode_none,                     /* 0x5b */
		opcode_none,                     /* 0x5c */
		opcode_none,                     /* 0x5d */
		opcode_none,                     /* 0x5e */
		opcode_none,                     /* 0x5f */
		opcode_none,                     /* 0x60 */
		opcode_none,                     /* 0x61 */
		opcode_none,                     /* 0x62 */
		opcode_none,                     /* 0x63 */
		opcode_none,                     /* 0x64 */
		opcode_none,                     /* 0x65 */
		opcode_none,                     /* 0x66 */
		opcode_none,                     /* 0x67 */
		opcode_none,                     /* 0x68 */
		opcode_none,                     /* 0x69 */
		opcode_none,                     /* 0x6a */
		opcode_none,                     /* 0x6b */
		opcode_none,                     /* 0x6c */
		opcode_none,                     /* 0x6d */
		opcode_none,                     /* 0x6e */
		opcode_none,                     /* 0x6f */
		opcode_none,                     /* 0x70 */
		opcode_none,                     /* 0x71 */
		opcode_none,                     /* 0x72 */
		opcode_none,                     /* 0x73 */
		opcode_none,                     /* 0x74 */
		opcode_none,                     /* 0x75 */
		opcode_none,                     /* 0x76 */
		opcode_none,                     /* 0x77 */
		opcode_none,                     /* 0x78 */
		opcode_none,                     /* 0x79 */
		opcode_none,                     /* 0x7a */
		opcode_none,                     /* 0x7b */
		opcode_none,                     /* 0x7c */
		opcode_none,                     /* 0x7d */
		opcode_none,                     /* 0x7e */
		opcode_none,                     /* 0x7f */
		opcode_none,                     /* 0x80 */
		opcode_none,                     /* 0x81 */
		opcode_none,                     /* 0x82 */
		opcode_none,                     /* 0x83 */
		opcode_none,                     /* 0x84 */
		opcode_none,                     /* 0x85 */
		opcode_none,                     /* 0x86 */
		opcode_none,                     /* 0x87 */
		opcode_none,                     /* 0x88 */
		opcode_none,                     /* 0x89 */
		opcode_none,                     /* 0x8a */
		opcode_none,                     /* 0x8b */
		opcode_none,                     /* 0x8c */
		opcode_none,                     /* 0x8d */
		opcode_none,                     /* 0x8e */
		opcode_none,                     /* 0x8f */
		opcode_none,                     /* 0x90 */
		opcode_none,                     /* 0x91 */
		opcode_none,                     /* 0x92 */
		opcode_none,                     /* 0x93 */
		opcode_none,                     /* 0x94 */
		opcode_none,                     /* 0x95 */
		opcode_none,                     /* 0x96 */
		opcode_none,                     /* 0x97 */
		opcode_none,                     /* 0x98 */
		opcode_none,                     /* 0x99 */
		opcode_none,                     /* 0x9a */
		opcode_none,                     /* 0x9b */
		opcode_none,                     /* 0x9c */
		opcode_none,                     /* 0x9d */
		opcode_none,                     /* 0x9e */
		opcode_none,                     /* 0x9f */
		opcode_none,                     /* 0xa0 */
		opcode_none,                     /* 0xa1 */
		opcode_none,                     /* 0xa2 */
		opcode_none,                     /* 0xa3 */
		opcode_none,                     /* 0xa4 */
		opcode_none,                     /* 0xa5 */
		opcode_none,                     /* 0xa6 */
		opcode_none,                     /* 0xa7 */
		opcode_none,                     /* 0xa8 */
		opcode_none,                     /* 0xa9 */
		opcode_none,                     /* 0xaa */
		opcode_none,                     /* 0xab */
		opcode_none,                     /* 0xac */
		opcode_none,                     /* 0xad */
		opcode_none,                     /* 0xae */
		opcode_none,                     /* 0xaf */
		opcode_none,                     /* 0xb0 */
		opcode_none,                     /* 0xb1 */
		opcode_none,                     /* 0xb2 */
		opcode_none,                     /* 0xb3 */
		opcode_none,                     /* 0xb4 */
		opcode_none,                     /* 0xb5 */
		opcode_none,                     /* 0xb6 */
		opcode_none,                     /* 0xb7 */
		opcode_none,                     /* 0xb8 */
		opcode_none,                     /* 0xb9 */
		opcode_none,                     /* 0xba */
		opcode_none,                     /* 0xbb */
		opcode_none,                     /* 0xbc */
		opcode_none,                     /* 0xbd */
		opcode_none,                     /* 0xbe */
		opcode_none,                     /* 0xbf */
		opcode_none,                     /* 0xc0 */
		opcode_none,                     /* 0xc1 */
		opcode_none,                     /* 0xc2 */
		opcode_none,                     /* 0xc3 */
		opcode_none,                     /* 0xc4 */
		opcode_none,                     /* 0xc5 */
		opcode_none,                     /* 0xc6 */
		opcode_none,                     /* 0xc7 */
		opcode_none,                     /* 0xc8 */
		opcode_none,                     /* 0xc9 */
		opcode_none,                     /* 0xca */
		opcode_none,                     /* 0xcb */
		opcode_none,                     /* 0xcc */
		opcode_none,                     /* 0xcd */
		opcode_none,                     /* 0xce */
		opcode_none,                     /* 0xcf */
		opcode_none,                     /* 0xd0 */
		opcode_none,                     /* 0xd1 */
		opcode_none,                     /* 0xd2 */
		opcode_none,                     /* 0xd3 */
		opcode_none,                     /* 0xd4 */
		opcode_none,                     /* 0xd5 */
		opcode_none,                     /* 0xd6 */
		opcode_none,                     /* 0xd7 */
		opcode_none,                     /* 0xd8 */
		opcode_none,                     /* 0xd9 */
		opcode_none,                     /* 0xda */
		opcode_none,                     /* 0xdb */
		opcode_none,                     /* 0xdc */
		opcode_none,                     /* 0xdd */
		opcode_none,                     /* 0xde */
		opcode_none,                     /* 0xdf */
		opcode_none,                     /* 0xe0 */
		opcode_none,                     /* 0xe1 */
		opcode_none,                     /* 0xe2 */
		opcode_none,                     /* 0xe3 */
		opcode_none,                     /* 0xe4 */
		opcode_none,                     /* 0xe5 */
		opcode_none,                     /* 0xe6 */
		opcode_none,                     /* 0xe7 */
		opcode_none,                     /* 0xe8 */
		opcode_none,                     /* 0xe9 */
		opcode_none,                     /* 0xea */
		opcode_none,                     /* 0xeb */
		opcode_none,                     /* 0xec */
		opcode_none,                     /* 0xed */
		opcode_none,                     /* 0xee */
		opcode_none,                     /* 0xef */
		opcode_none,                     /* 0xf0 */
		opcode_none,                     /* 0xf1 */
		opcode_none,                     /* 0xf2 */
		opcode_none,                     /* 0xf3 */
		opcode_none,                     /* 0xf4 */
		opcode_none,                     /* 0xf5 */
		opcode_none,                     /* 0xf6 */
		opcode_none,                     /* 0xf7 */
		opcode_none,                     /* 0xf8 */
		opcode_none,                     /* 0xf9 */
		opcode_none,                     /* 0xfa */
		opcode_none,                     /* 0xfb */
		opcode_none,                     /* 0xfc */
		opcode_none,                     /* 0xfd */
		opcode_none,                     /* 0xfe */
		opcode_none,                     /* 0xff */
	};
#endif
}

static void parse (struct emu_i386 *emu, uint8_t *data, uint64_t sz)
{
}

int main (int argc, char **argv)
{
	uint8_t data[] = {0x00, 0x04};
	uint64_t sz = sizeof (data);

	struct emu_i386 emu;
	init (&emu);

	parse (&emu, data, sz);
}
