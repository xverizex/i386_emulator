#ifndef I386_EMU_H
#define I386_EMU_H

#include <stdint.h>

enum Mode {
	REAL_MODE,
	PROTECTED_MODE,
	N_MODE
};

#define EFLAG_REGISTER_CF                        0x000001
#define EFLAG_REGISTER_PF                        0x000004
#define EFLAG_REGISTER_AF                        0x000010
#define EFLAG_REGISTER_ZF                        0x000040
#define EFLAG_REGISTER_SF                        0x000080
#define EFLAG_REGISTER_TF                        0x000100
#define EFLAG_REGISTER_IF                        0x000200
#define EFLAG_REGISTER_DF                        0x000400
#define EFLAG_REGISTER_OF                        0x000800
#define EFLAG_REGISTER_IOPL                      0x001000
#define EFLAG_REGISTER_NT                        0x002000
#define EFLAG_REGISTER_RF                        0x008000
#define EFLAG_REGISTER_VM                        0x010000

struct cpu_i386 {
	union {
		struct {
			uint8_t AL;
			uint8_t AH;
		};
		uint16_t AX;
		uint32_t EAX;
	};
	union {
		struct {
			uint8_t CL;
			uint8_t CH;
		};
		uint16_t CX;
		uint32_t ECX;
	};
	union {
		struct {
			uint8_t DL;
			uint8_t DH;
		};
		uint16_t DX;
		uint32_t EDX;
	};
	union {
		struct {
			uint8_t BL;
			uint8_t BH;
		};
		uint16_t BX;
		uint32_t EBX;
	};
	union {
		uint16_t SP;
		uint32_t ESP;
	};
	union {
		uint16_t BP;
		uint32_t EBP;
	};
	union {
		uint16_t SI;
		uint32_t ESI;
	};
	union {
		uint16_t DI;
		uint32_t EDI;
	};

	enum Mode mode;
};

struct emu_i386;

typedef void (*_instr_group) (struct emu_i386 *);

struct emu_i386 {
	struct cpu_i386 CPU;

	/* opcodes array and extensions */
	_instr_group *base;
	_instr_group *ext_0F;
	_instr_group *ext_D5;
	_instr_group *ext_D4;
	_instr_group *ext_F3;
	_instr_group *ext_F2;

	/* offset in data */
	uint32_t start_off;
	uint32_t off;

	/* data of hda ssd or any media */
	uint8_t *data;
	uint64_t sz_data;

};

#endif
