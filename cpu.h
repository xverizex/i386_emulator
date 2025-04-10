#ifndef I386_EMU_H
#define I386_EMU_H

#include <stdint.h>

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
};

struct emu_i386;

typedef void (*_instr_group) (struct emu_i386 *);

struct emu_i386 {
	struct cpu_i386 CPU;
	_instr_group *base;
	_instr_group *ext_0F;
	_instr_group *ext_D5;
	_instr_group *ext_D4;
	_instr_group *ext_F3;
	_instr_group *ext_F2;
};

#endif
