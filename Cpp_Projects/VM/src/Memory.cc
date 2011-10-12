#include "Memory.h"

Memory::Memory()
{
	memArray = 0;
}

Memory::~Memory()
{
	delete[] memArray;
}

bool Memory::Init(int size)
{
	memArray = new uint8_t[size];
	memSize = size;
	return true;
}

uint8_t Memory::LoadByte(uint64_t address)
{
	if (address > memSize)
		return 0; //Exception needs to be here
	return memArray[address];
}

bool Memory::StoreByte(uint8_t byte, uint64_t address)
{
	if (address > memSize)
		return false; //Exception needs to be here
	memArray[address] = byte;
	return true;
}
