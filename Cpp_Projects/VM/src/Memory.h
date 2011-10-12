#ifndef VM_MEMORY_H
#define VM_MEMORY_H

#include "Common.h"

class Memory
{
	public:
		Memory();
		~Memory();
		bool Init(int size);
		uint8_t LoadByte(uint64_t address);
		bool StoreByte(uint8_t byte, uint64_t address);
	
	private:
		uint8_t* memArray;
		uint64_t memSize;
};

#endif
