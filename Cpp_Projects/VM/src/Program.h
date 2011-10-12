#ifndef VM_PROGRAM_H
#define VM_PROGRAM_H

#include "Common.h"

typedef struct {
	char* name;
	uint64_t addr;
} label_t;

typedef struct {
	char* op;
	char* arg1;
	char* arg2;
} instr_t;

class Program
{
	public:
		Program();
		~Program();
		void LoadFile(const char* filename);
		instruction GetInstr(uint64_t addr);
		uint64_t LabelLookup(const char* label);

	private:
		void parseLine(const char* line, int len = 128);
		label_t* labels;
		int labelPtr;
		instr_t* instr;
		int instrPtr;
		instruction* instr_out;

};

#endif
