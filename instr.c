#include <stddef.h>
#include "instr.h"
#include "cpu.h"

void opcode_none (struct emu_i386 *emu){}

static void _get_modrm_registers (uint8_t modrm_byte, uint8_t *mod,
		uint8_t *r0,
		uint8_t *r1)
{
	*mod = modrm_byte >> 6;
	*r0  = modrm_byte & 0x7;
	*r1  = (modrm_byte >> 3) & 0x7;
}

uint8_t *_get_16_mod_0_reg (struct emu_i386 *emu, uint8_t r)
{
	switch (r) {
		case 0: return &emu->data[emu->CPU.BX + emu->CPU.SI];
		case 1: return &emu->data[emu->CPU.BX + emu->CPU.DI];
		case 2: return &emu->data[emu->CPU.BP + emu->CPU.SI];
		case 3: return &emu->data[emu->CPU.BP + emu->CPU.DI];
		case 4: return &emu->data[emu->CPU.SI];
		case 5: return &emu->data[emu->CPU.DI];
		case 6: return &emu->data[*(uint16_t *) &emu->data[emu->off + 1]];
		case 7: return &emu->data[emu->CPU.BX];
	}
}

uint8_t *_get_16_mod_1_reg (struct emu_i386 *emu, uint8_t r)
{
}

uint8_t *_get_16_mod_2_reg (struct emu_i386 *emu, uint8_t r)
{
}

uint8_t *_get_16_mod_3_reg (struct emu_i386 *emu, uint8_t r)
{
}

static uint8_t *_16_bit_address_rm8 (struct emu_i386 *emu, uint8_t mod, uint8_t r)
{
	switch (mod) {
		case _16_BIT_ADDRESS_FORM_REG_ADDR: return _get_16_mod_0_reg (emu, r);
		case _16_BIT_ADDRESS_FORM_REG_ADDR_DISP8: return _get_16_mod_1_reg (emu, r);
		case _16_BIT_ADDRESS_FORM_REG_ADDR_DISP16: return _get_16_mod_2_reg (emu, r);
		case _16_BIT_ADDRESS_FORM_REG: return _get_16_mod_2_reg (emu, r);
	}
}

static uint8_t *_32_bit_address_rm8 (struct emu_i386 *emu, uint8_t mod, uint8_t r)
{
	return NULL;
}

typedef uint8_t* (*level_rm8_handle) (struct emu_i386 *emu, uint8_t mod, uint8_t r);

static level_rm8_handle handle_rm8[2] = {
	_16_bit_address_rm8,
	_32_bit_address_rm8
};

uint8_t *_get_real_reg8_by_mod_and_reg (struct emu_i386 *emu, uint8_t mod, uint8_t r)
{
	return handle_rm8[emu->level] (emu, mod, r);
}

uint8_t *_get_real_reg8_by_reg (struct emu_i386 *emu, uint8_t r)
{
	switch (r) {
		case R8_AL: return &emu->CPU.AL;
		case R8_CL: return &emu->CPU.CL;
		case R8_DL: return &emu->CPU.DL;
		case R8_BL: return &emu->CPU.BL;
		case R8_AH: return &emu->CPU.AH;
		case R8_CH: return &emu->CPU.CH;
		case R8_DH: return &emu->CPU.DH;
		case R8_BH: return &emu->CPU.BH;
	}
}

static void impl_get_regs_rm8_r8 (struct emu_i386 *emu, uint8_t **rr0, uint8_t **rr1)
{
	uint8_t modrm_byte = emu->data[emu->off];
	uint8_t mod, r0, r1;
	_get_modrm_registers (modrm_byte, &mod, &r0, &r1);
	uint8_t *r0_real = _get_real_reg8_by_mod_and_reg (emu, mod, r0);
	uint8_t *r1_real = _get_real_reg8_by_reg (emu, r1);
	*rr0 = r0_real;
	*rr1 = r1_real;
}

static void eq8 (uint8_t *r0, uint8_t r1)
{
	*r0 = r1;
}

static void check_flags_r8 (struct emu_i386 *emu,
		uint8_t old_value,
		uint8_t result,
		uint32_t flags)
{
	emu->eflags &= ~(flags);

	if (flags & EFLAG_REGISTER_CF) {
		if (old_value > result) {
			emu->eflags |= EFLAG_REGISTER_CF;
		}
	}
	if (flags & EFLAG_REGISTER_ZF) {
		if (result == 0) {
			emu->eflags |= EFLAG_REGISTER_ZF;
		}
	}
	if (flags & EFLAG_REGISTER_SF) {
		if (result & 0x80) {
			emu->eflags |= EFLAG_REGISTER_SF;
		}
	}
}

static void impl_rm8_r8 (struct emu_i386 *emu,
		uint8_t *r,
		uint8_t result,
		void (*eq) (uint8_t *r0, uint8_t r1),
		uint32_t flags
		)
{
	check_flags_r8 (emu, *r, result, flags);
	eq (r, result);
}

void opcode_add_rm8_r8 (struct emu_i386 *emu)
{
	emu->off++;
	uint8_t *r0, *r1;
	impl_get_regs_rm8_r8 (emu, &r0, &r1);
	impl_rm8_r8 (emu, r0, *r0 + *r1, eq8,
			(EFLAG_REGISTER_OF|EFLAG_REGISTER_SF|EFLAG_REGISTER_ZF|
			 EFLGA_REGISTER_AF|EFLAG_REGISTER_CF|EFLAG_REGISTER_CF)
			);
}

void opcode_add_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_add_r8_rm8 (struct emu_i386 *emu){}
void opcode_add_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_add_al_imm8 (struct emu_i386 *emu){}
void opcode_add_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_push_es (struct emu_i386 *emu){}
void opcode_pop_es (struct emu_i386 *emu){}
void opcode_or_rm8_r8 (struct emu_i386 *emu){}
void opcode_or_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_or_r8_rm8 (struct emu_i386 *emu){}
void opcode_or_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_or_al_imm8 (struct emu_i386 *emu){}
void opcode_or_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_adc_rm8_r8 (struct emu_i386 *emu){}
void opcode_adc_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_adc_r8_rm8 (struct emu_i386 *emu){}
void opcode_adc_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_adc_al_imm8 (struct emu_i386 *emu){}
void opcode_adc_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_push_ss (struct emu_i386 *emu){}
void opcode_push_ds (struct emu_i386 *emu){}
void opcode_pop_ss (struct emu_i386 *emu){}
void opcode_pop_ds (struct emu_i386 *emu){}
void opcode_and_rm8_r8 (struct emu_i386 *emu){}
void opcode_and_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_and_r8_rm8 (struct emu_i386 *emu){}
void opcode_and_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_and_al_imm8 (struct emu_i386 *emu){}
void opcode_and_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_daa (struct emu_i386 *emu){}
void opcode_sbb_rm8_r8 (struct emu_i386 *emu){}
void opcode_sbb_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_sbb_r8_rm8 (struct emu_i386 *emu){}
void opcode_sbb_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_sbb_al_imm8 (struct emu_i386 *emu){}
void opcode_sbb_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_cmp_rm8_r8 (struct emu_i386 *emu){}
void opcode_cmp_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_cmp_r8_rm8 (struct emu_i386 *emu){}
void opcode_cmp_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_cmp_al_imm8 (struct emu_i386 *emu){}
void opcode_cmp_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_sub_rm8_r8 (struct emu_i386 *emu){}
void opcode_sub_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_sub_r8_rm8 (struct emu_i386 *emu){}
void opcode_sub_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_sub_al_imm8 (struct emu_i386 *emu){}
void opcode_sub_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_das (struct emu_i386 *emu){}
void opcode_xor_rm8_r8 (struct emu_i386 *emu){}
void opcode_xor_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_xor_r8_rm8 (struct emu_i386 *emu){}
void opcode_xor_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_xor_al_imm8 (struct emu_i386 *emu){}
void opcode_xor_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_aaa (struct emu_i386 *emu){}
void opcode_aas (struct emu_i386 *emu){}
void opcode_inc_axeax (struct emu_i386 *emu){}
void opcode_inc_cxecx (struct emu_i386 *emu){}
void opcode_inc_dxedx (struct emu_i386 *emu){}
void opcode_inc_bxebx (struct emu_i386 *emu){}
void opcode_inc_spesp (struct emu_i386 *emu){}
void opcode_inc_bpebp (struct emu_i386 *emu){}
void opcode_inc_siesi (struct emu_i386 *emu){}
void opcode_inc_diedi (struct emu_i386 *emu){}
void opcode_dec_axeax (struct emu_i386 *emu){}
void opcode_dec_cxecx (struct emu_i386 *emu){}
void opcode_dec_dxedx (struct emu_i386 *emu){}
void opcode_dec_bxebx (struct emu_i386 *emu){}
void opcode_dec_spesp (struct emu_i386 *emu){}
void opcode_dec_bpebp (struct emu_i386 *emu){}
void opcode_dec_siesi (struct emu_i386 *emu){}
void opcode_dec_diedi (struct emu_i386 *emu){}
void opcode_push_axeax (struct emu_i386 *emu){}
void opcode_push_cxecx (struct emu_i386 *emu){}
void opcode_push_dxedx (struct emu_i386 *emu){}
void opcode_push_bxebx (struct emu_i386 *emu){}
void opcode_push_spesp (struct emu_i386 *emu){}
void opcode_push_bpebp (struct emu_i386 *emu){}
void opcode_push_siesi (struct emu_i386 *emu){}
void opcode_push_diedi (struct emu_i386 *emu){}
void opcode_pop_axeax (struct emu_i386 *emu){}
void opcode_pop_cxecx (struct emu_i386 *emu){}
void opcode_pop_dxedx (struct emu_i386 *emu){}
void opcode_pop_bxebx (struct emu_i386 *emu){}
void opcode_pop_spesp (struct emu_i386 *emu){}
void opcode_pop_bpebp (struct emu_i386 *emu){}
void opcode_pop_siesi (struct emu_i386 *emu){}
void opcode_pop_diedi (struct emu_i386 *emu){}
void opcode_bound_r1632_m1632 (struct emu_i386 *emu){}
void opcode_aprl_rm16_r16 (struct emu_i386 *emu){}
void opcode_popa_popad (struct emu_i386 *emu){}
void opcode_pusha_pushad (struct emu_i386 *emu){}
void opcode_imul_r1632_rm1632_imm1632 (struct emu_i386 *emu){}
void opcode_imul_r1632_rm1632_imm8 (struct emu_i386 *emu){}
void opcode_insb (struct emu_i386 *emu){}
void opcode_inswd (struct emu_i386 *emu){}
void opcode_outsb (struct emu_i386 *emu){}
void opcode_outswd (struct emu_i386 *emu){}
void opcode_push_imm8 (struct emu_i386 *emu){}
void opcode_push_imm1632 (struct emu_i386 *emu){}
void group_ext_0F (struct emu_i386 *emu){}
void group_ext_D5 (struct emu_i386 *emu){}
void group_ext_D4 (struct emu_i386 *emu){}
void opcode_bsf_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_bsr_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_bt_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_group_test_bt_rm1632_imm8 (struct emu_i386 *emu){}
void opcode_btc_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_btr_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_bts_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_clts (struct emu_i386 *emu){}
void opcode_imul_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_ja_rel1632 (struct emu_i386 *emu){}
void opcode_jae_rel1632 (struct emu_i386 *emu){}
void opcode_jb_rel1632 (struct emu_i386 *emu){}
void opcode_jbe_rel1632 (struct emu_i386 *emu){}
void opcode_je_rel1632 (struct emu_i386 *emu){}
void opcode_jg_rel1632 (struct emu_i386 *emu){}
void opcode_jge_rel1632 (struct emu_i386 *emu){}
void opcode_jl_rel1632 (struct emu_i386 *emu){}
void opcode_jle_rel1632 (struct emu_i386 *emu){}
void opcode_jne_rel1632 (struct emu_i386 *emu){}
void opcode_jno_rel1632 (struct emu_i386 *emu){}
void opcode_jnp_rel1632 (struct emu_i386 *emu){}
void opcode_jns_rel1632 (struct emu_i386 *emu){}
void opcode_jo_rel1632 (struct emu_i386 *emu){}
void opcode_jpe_rel1632 (struct emu_i386 *emu){}
void opcode_js_rel1632 (struct emu_i386 *emu){}
void opcode_lar_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_lgdt_lidt_m1632 (struct emu_i386 *emu){}
void opcode_lss_r1632_m1632 (struct emu_i386 *emu){}
void opcode_lfs_r1632_m1632 (struct emu_i386 *emu){}
void opcode_lgs_r1632_m1632 (struct emu_i386 *emu){}
void opcode_lldt_rm16 (struct emu_i386 *emu){}
void opcode_lsl_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_mov_r32_cr0_cr2_cr3 (struct emu_i386 *emu){}
void opcode_mov_r32_dr0 (struct emu_i386 *emu){}
void opcode_mov_dr0_r32 (struct emu_i386 *emu){}
void opcode_mov_r32_tr67 (struct emu_i386 *emu){}
void opcode_mov_tr67_r32 (struct emu_i386 *emu){}
void opcode_mov_cr023_r32 (struct emu_i386 *emu){}
void opcode_movsx_r1632_rm8 (struct emu_i386 *emu){}
void opcode_movsx_r32_rm16 (struct emu_i386 *emu){}
void opcode_movzx_r1632_rm8 (struct emu_i386 *emu){}
void opcode_movzx_r32_rm16 (struct emu_i386 *emu){}
void opcode_pop_fs (struct emu_i386 *emu){}
void opcode_pop_gs (struct emu_i386 *emu){}
void opcode_push_fs (struct emu_i386 *emu){}
void opcode_push_gs (struct emu_i386 *emu){}
void opcode_seta_rm8 (struct emu_i386 *emu){}
void opcode_setae_rm8 (struct emu_i386 *emu){}
void opcode_setb_rm8 (struct emu_i386 *emu){}
void opcode_setbe_rm8 (struct emu_i386 *emu){}
void opcode_sete_rm8 (struct emu_i386 *emu){}
void opcode_setg_rm8 (struct emu_i386 *emu){}
void opcode_setge_rm8 (struct emu_i386 *emu){}
void opcode_setl_rm8 (struct emu_i386 *emu){}
void opcode_setle_rm8 (struct emu_i386 *emu){}
void opcode_setne_rm8 (struct emu_i386 *emu){}
void opcode_seto_rm8 (struct emu_i386 *emu){}
void opcode_setno_rm8 (struct emu_i386 *emu){}
void opcode_setns_rm8 (struct emu_i386 *emu){}
void opcode_setpe_rm8 (struct emu_i386 *emu){}
void opcode_setpo_rm8 (struct emu_i386 *emu){}
void opcode_sets_rm8 (struct emu_i386 *emu){}
void opcode_shld_rm1632_r1632_imm8 (struct emu_i386 *emu){}
void opcode_shld_rm1632_r1632_cl (struct emu_i386 *emu){}
void opcode_shrd_rm1632_r1632_imm8 (struct emu_i386 *emu){}
void opcode_shrd_rm1632_r1632_cl (struct emu_i386 *emu){}
void opcode_aad (struct emu_i386 *emu){}
void opcode_aam (struct emu_i386 *emu){}
void opcode_base_rm8_imm8 (struct emu_i386 *emu){}
void opcode_base_rm1632_imm1632 (struct emu_i386 *emu){}
void opcode_base_rm1632_imm8 (struct emu_i386 *emu){}
void opcode_call_rel1632 (struct emu_i386 *emu){}
void opcode_ext_0_m1632 (struct emu_i386 *emu){}
void opcode_call_ptr1632 (struct emu_i386 *emu){}
void opcode_cbw_cwde (struct emu_i386 *emu){}
void opcode_clc (struct emu_i386 *emu){}
void opcode_cld (struct emu_i386 *emu){}
void opcode_cli (struct emu_i386 *emu){}
void opcode_cmc (struct emu_i386 *emu){}
void opcode_cmpsb (struct emu_i386 *emu){}
void opcode_cmpswd (struct emu_i386 *emu){}
void opcode_cwd_cdq (struct emu_i386 *emu){}
void opcode_ext_1_rm8 (struct emu_i386 *emu){}
void opcode_calc_al_rm8 (struct emu_i386 *emu){}
void opcode_calc_axeax_rm1632 (struct emu_i386 *emu){}
void opcode_enter_imm16_imm8 (struct emu_i386 *emu){}
void opcode_hlt (struct emu_i386 *emu){}
void opcode_in_al_imm8 (struct emu_i386 *emu){}
void opcode_in_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_in_al_dx (struct emu_i386 *emu){}
void opcode_in_axeax_dx (struct emu_i386 *emu){}
void opcode_int_3 (struct emu_i386 *emu){}
void opcode_int_imm8 (struct emu_i386 *emu){}
void opcode_into (struct emu_i386 *emu){}
void opcode_iret_iretd (struct emu_i386 *emu){}
void opcode_ja_rel8 (struct emu_i386 *emu){}
void opcode_jae_rel8 (struct emu_i386 *emu){}
void opcode_jb_rel8 (struct emu_i386 *emu){}
void opcode_jbe_rel8 (struct emu_i386 *emu){}
void opcode_je_rel8 (struct emu_i386 *emu){}
void opcode_jg_rel8 (struct emu_i386 *emu){}
void opcode_jge_rel8 (struct emu_i386 *emu){}
void opcode_jl_rel8 (struct emu_i386 *emu){}
void opcode_jle_rel8 (struct emu_i386 *emu){}
void opcode_jne_rel8 (struct emu_i386 *emu){}
void opcode_jno_rel8 (struct emu_i386 *emu){}
void opcode_jo_rel8 (struct emu_i386 *emu){}
void opcode_jp_rel8 (struct emu_i386 *emu){}
void opcode_jpo_rel8 (struct emu_i386 *emu){}
void opcode_js_rel8 (struct emu_i386 *emu){}
void opcode_jns_rel8 (struct emu_i386 *emu){}
void opcode_jecxz_rel8 (struct emu_i386 *emu){}
void opcode_jmp_rel8 (struct emu_i386 *emu){}
void opcode_jmp_rel1632 (struct emu_i386 *emu){}
void opcode_jmp_ptr16_1632 (struct emu_i386 *emu){}
void opcode_lahf (struct emu_i386 *emu){}
void opcode_lea_r1632_m_mov_sreg_rm16 (struct emu_i386 *emu){}
void opcode_leave (struct emu_i386 *emu){}
void opcode_les_r1632_m16_1632 (struct emu_i386 *emu){}
void opcode_lds_r1632_m16_1632 (struct emu_i386 *emu){}
void opcode_lock (struct emu_i386 *emu){}
void opcode_lodsb (struct emu_i386 *emu){}
void opcode_lodswd (struct emu_i386 *emu){}
void opcode_loopne_rel8 (struct emu_i386 *emu){}
void opcode_loope_rel8 (struct emu_i386 *emu){}
void opcode_loop_rel8 (struct emu_i386 *emu){}
void opcode_mov_rm8_r8 (struct emu_i386 *emu){}
void opcode_mov_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_mov_r8_rm8 (struct emu_i386 *emu){}
void opcode_mov_r1632_rm1632 (struct emu_i386 *emu){}
void opcode_mov_rm16_sreg (struct emu_i386 *emu){}
void opcode_mov_sreg_rm16 (struct emu_i386 *emu){}
void opcode_mov_al_moffs8 (struct emu_i386 *emu){}
void opcode_mov_axeax_ax_eax (struct emu_i386 *emu){}
void opcode_mov_moffs8_al (struct emu_i386 *emu){}
void opcode_mov_moffs1632_axeax (struct emu_i386 *emu){}
void opcode_mov_al_imm8 (struct emu_i386 *emu){}
void opcode_mov_cl_imm8 (struct emu_i386 *emu){}
void opcode_mov_dl_imm8 (struct emu_i386 *emu){}
void opcode_mov_bl_imm8 (struct emu_i386 *emu){}
void opcode_mov_ah_imm8 (struct emu_i386 *emu){}
void opcode_mov_ch_imm8 (struct emu_i386 *emu){}
void opcode_mov_dh_imm8 (struct emu_i386 *emu){}
void opcode_mov_bh_imm8 (struct emu_i386 *emu){}
void opcode_mov_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_mov_cxecx_imm1632 (struct emu_i386 *emu){}
void opcode_mov_dxedx_imm1632 (struct emu_i386 *emu){}
void opcode_mov_bxebx_imm1632 (struct emu_i386 *emu){}
void opcode_mov_spesp_imm1632 (struct emu_i386 *emu){}
void opcode_mov_bpebp_imm1632 (struct emu_i386 *emu){}
void opcode_mov_siesi_imm1632 (struct emu_i386 *emu){}
void opcode_mov_diedi_imm1632 (struct emu_i386 *emu){}
void opcode_mov_rm8_imm8 (struct emu_i386 *emu){} //TODO: check that is 0xc6
void opcode_mov_rm1632_imm1632 (struct emu_i386 *emu){}
void opcode_movsb (struct emu_i386 *emu){}
void opcode_movswd (struct emu_i386 *emu){}
void opcode_nop (struct emu_i386 *emu){}
void opcode_out_imm8_al (struct emu_i386 *emu){}
void opcode_out_imm1632_axeax (struct emu_i386 *emu){}
void opcode_out_dx_al (struct emu_i386 *emu){}
void opcode_out_dx_axeax (struct emu_i386 *emu){}
void opcode_calc_m1632 (struct emu_i386 *emu){}
void opcode_popf_popfd (struct emu_i386 *emu){}
void opcode_push_cs (struct emu_i386 *emu){}
void opcode_pushf_pushfd (struct emu_i386 *emu){}
void opcode_ext_rotate_rm8_1 (struct emu_i386 *emu){}
void opcode_ext_rotate_rm1632_1 (struct emu_i386 *emu){}
void opcode_ext_rotate_rm8_cl (struct emu_i386 *emu){}
void opcode_ext_rotate_rm1632_cl (struct emu_i386 *emu){}
void opcode_ext_rotate_rm8_imm8 (struct emu_i386 *emu){}
void opcode_ext_rotate_rm1632_imm8 (struct emu_i386 *emu){}
void group_ext_F3 (struct emu_i386 *emu){}
void opcode_rep_ins_rm8_dx (struct emu_i386 *emu){}
void opcode_rep_ins_rm1632_dx (struct emu_i386 *emu){}
void opcode_rep_outs_dx_rm8 (struct emu_i386 *emu){}
void opcode_rep_outs_dx_rm1632 (struct emu_i386 *emu){}
void opcode_rep_movs_m8_m8 (struct emu_i386 *emu){}
void opcode_rep_movs_m1632_m1632 (struct emu_i386 *emu){}
void opcode_repe_cmps_m8_m8 (struct emu_i386 *emu){}
void opcode_repe_cmps_m1632_m1632 (struct emu_i386 *emu){}
void opcode_rep_stos_m8 (struct emu_i386 *emu){}
void opcode_rep_stos_m1632 (struct emu_i386 *emu){}
void opcode_rep_scas_m8 (struct emu_i386 *emu){}
void opcode_rep_scas_m1632 (struct emu_i386 *emu){}
void group_ext_F2 (struct emu_i386 *emu){}
void opcode_repne_cmps_m8_m8 (struct emu_i386 *emu){}
void opcode_repne_cmps_m1632_m1632 (struct emu_i386 *emu){}
void opcode_repne_scas_m8 (struct emu_i386 *emu){}
void opcode_repne_scas_m1632 (struct emu_i386 *emu){}
void opcode_ret_near (struct emu_i386 *emu){}
void opcode_ret_near_imm16 (struct emu_i386 *emu){}
void opcode_ret_far_imm16 (struct emu_i386 *emu){}
void opcode_ret_far (struct emu_i386 *emu){}
void opcode_sahf (struct emu_i386 *emu){}
void opcode_scasb (struct emu_i386 *emu){}
void opcode_scaswd (struct emu_i386 *emu){}
void opcode_stc (struct emu_i386 *emu){}
void opcode_std (struct emu_i386 *emu){}
void opcode_sti (struct emu_i386 *emu){}
void opcode_stosb (struct emu_i386 *emu){}
void opcode_stoswd (struct emu_i386 *emu){}
void opcode_test_rm8_r8 (struct emu_i386 *emu){}
void opcode_test_rm1632_r1632 (struct emu_i386 *emu){}
void opcode_test_al_imm8 (struct emu_i386 *emu){}
void opcode_test_axeax_imm1632 (struct emu_i386 *emu){}
void opcode_wait (struct emu_i386 *emu){}
void opcode_xchg_rm8_rm8 (struct emu_i386 *emu){}
void opcode_xchg_rm1632_rm1632 (struct emu_i386 *emu){}
void opcode_xchg_axeax_cxecx (struct emu_i386 *emu){}
void opcode_xchg_axeax_dxedx (struct emu_i386 *emu){}
void opcode_xchg_axeax_bxebx (struct emu_i386 *emu){}
void opcode_xchg_axeax_spesp (struct emu_i386 *emu){}
void opcode_xchg_axeax_bpebp (struct emu_i386 *emu){}
void opcode_xchg_axeax_siesi (struct emu_i386 *emu){}
void opcode_xchg_axeax_diedi (struct emu_i386 *emu){}
void opcode_xlatb (struct emu_i386 *emu){}
