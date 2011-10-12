#ifndef VM_CPU_H
#define VM_CPU_H

#include "Common.h"

class Memory;
class Program;

class CPU
{
	public:
		CPU();
		~CPU();
		void Init(Program* exec, Memory* memInit);
		Memory* getMemory();
		Program* getProgram();
		uint64_t getCurrentAddr();
		bool Run();
		bool Step(instruction instr);

	protected:
		Memory* mem;
		Program* prog;
		uint64_t currentAddr;
		int32_t* reg;
};

#endif
