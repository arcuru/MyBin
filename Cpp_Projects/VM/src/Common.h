#ifndef VM_COMMON_H
#define VM_COMMON_H

#include <cstdint>

typedef struct {
	uint8_t opcode;
	uint8_t arg0;
	int32_t arg1;
	bool addr;
	bool num;
} instruction;

#endif
