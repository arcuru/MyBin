#include "Program.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>

using std::cout;
using std::endl;
using std::isspace;
using std::ifstream;
using std::memcpy;
using std::memset;
using std::strcmp;

const char* tvm_opcode_map[] = {"nop", "int", "mov", "push", "pop", "pushf", "popf", "inc", "dec", "add", "sub", "mul", "div", "mod", "rem",
				"not", "xor", "or", "and", "shl", "shr", "cmp", "jmp", "call", "ret", "je", "jne", "jg", "jge", "jl", "jle", "prn", 0};

const char* tvm_register_map[] = {"eax", "ebx", "ecx", "edx", "esi", "edi", "esp", "ebp", "eip", "r08", "r09", "r10", "r11", "r12", "r13", "r14", "r15", 0};

int instr_to_opcode(const char* instr)
{
	for(int i = 0; tvm_opcode_map[i]; i++)
		if(strcmp(instr, tvm_opcode_map[i]) == 0)
			return i;

	return -1;
}

int arg_to_reg(const char* arg)
{
	for (int i = 0; tvm_register_map[i]; i++)
		if(strcmp(arg, tvm_register_map[i]) == 0)
			return i;
	return -1;
}

Program::Program()
{
	labels = new label_t[100];
	instr = new instr_t[100];
	labelPtr = 0;
	instrPtr = -1;
}

Program::~Program()
{
}

void Program::LoadFile(const char* filename)
{
	ifstream input(filename);
	if (!input)
		return; //Can't open file
	while (input) {
		char t[128];
		input.getline(t, 128, '\n');
		parseLine(t);
	}
	instrPtr++;
	instr_out = new instruction[instrPtr];
	for (int i = 0; i < instrPtr; i++) {
		instr_out[i].opcode = instr_to_opcode(instr[i].op);
		instr_out[i].arg0 = arg_to_reg(instr[i].arg1);
		instr_out[i].addr = false;
		if (arg_to_reg(instr[i].arg1) == -1) {
			instr_out[i].arg0 = LabelLookup(instr[i].arg1);
			instr_out[i].addr = true;
		}
		if (isalpha(instr[i].arg2[0])) {
			instr_out[i].arg1 = arg_to_reg(instr[i].arg2);
			instr_out[i].num = false;
		}
		else {
			instr_out[i].arg1 = std::atoi(instr[i].arg2);
			instr_out[i].num = true;
		}
	}
}

instruction Program::GetInstr(uint64_t addr)
{
	return instr_out[addr];
}

uint64_t Program::LabelLookup(const char* label)
{
	for (int i = 0 ; i < labelPtr; i++) {
		if (strcmp(label, labels[i].name) == 0)
			return labels[i].addr;
	}
	return -1;
}

void Program::parseLine(const char* line, int len)
{
	char* cpy = new char[len];
	int cpyPtr = 0;
	bool start = true;
	for (int i=0; i < len; i++) { //filter out coments
		if (start && isspace(line[i])) // Skip whitespace
			continue;
		start = false;
		if (line[i] == '#')
			break;
		if (line[i] == ':') {
			labels[labelPtr].name = new char[cpyPtr];
			memcpy(labels[labelPtr].name, cpy, cpyPtr);
			labels[labelPtr].addr = instrPtr+1;
			cout << labels[labelPtr].addr << endl;
			labelPtr++;
			memset(cpy, 0, cpyPtr);
			cpyPtr = 0;
			start = true;
			continue;
		}
		cpy[cpyPtr++] = line[i];
	}
	if (!isgraph(cpy[0]))
		return;

	// We now have an instruction
	//cout << cpy <<  cpyPtr << endl;
	instrPtr++;
	int i = 0;
	while (!isspace(cpy[i]))
		i++;
	instr[instrPtr].op = new char[i];
	memcpy(instr[instrPtr].op, cpy, i);
	while (isspace(cpy[i]))
		i++;
	if (i >= cpyPtr)
		return;
	int argStart = i;
	while (!isspace(cpy[i]) && cpy[i] != ',')
		i++;
	instr[instrPtr].arg1 = new char[i-argStart];
	memcpy(instr[instrPtr].arg1, &cpy[argStart], i-argStart);

	while (isspace(cpy[i]) || cpy[i] == ',')
		i++;
	if (i >= cpyPtr)
		return;
	argStart = i;
	while (!isspace(cpy[i]) && cpy[i] != ',')
		i++;
	instr[instrPtr].arg2 = new char[i-argStart];
	memcpy(instr[instrPtr].arg2, &cpy[argStart], i-argStart);
	return;

}
