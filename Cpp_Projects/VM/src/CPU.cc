#include "CPU.h"
#include "Program.h"
#include <iostream>

using std::cout;
using std::endl;

CPU::CPU()
{
	currentAddr = 0;
	reg = new int32_t[32];
}

CPU::~CPU()
{
}

void CPU::Init(Program* exec, Memory* memInit)
{
	mem = memInit;
	prog = exec;
	currentAddr = 0;
}

Memory* CPU::getMemory()
{
	return mem;
}

Program* CPU::getProgram()
{
	return prog;
}

uint64_t CPU::getCurrentAddr()
{
	return currentAddr;
}

bool CPU::Run()
{
	while(currentAddr < 100) {
		Step(prog->GetInstr(currentAddr));
		currentAddr++;
//		std::cout << currentAddr << std::endl;
	}
	return true;
}

bool CPU::Step(instruction instr)
{
	int32_t* arg1 = instr.num ? &instr.arg1 : &reg[instr.arg1];
//	std::printf("%d\n", instr.opcode);
	switch(instr.opcode) {
/* nop   */	case 0x0:  break;
/* int   */	case 0x1:  break;
/* mov   */	case 0x2:  reg[instr.arg0] = *arg1; break;
/* push  */	//case 0x3:  stack_push(vm->pMemory, reg[instr.arg0]); break;
/* pop   */	//case 0x4:  stack_pop(vm->pMemory, reg[instr.arg0]); break;
/* pushf */	//case 0x5:  stack_push(vm->pMemory, &reg[32]); break;
/* popf  */	//case 0x6:  stack_pop(vm->pMemory, reg[instr.arg0]); break;
/* inc   */	case 0x7:  ++reg[instr.arg0]; break;
/* dec   */	case 0x8:  --reg[instr.arg0]; break;
/* add   */	case 0x9:  reg[instr.arg0] += *arg1; break;
/* sub   */	case 0xA:  reg[instr.arg0] -= *arg1; break;
/* mul   */	case 0xB:  reg[instr.arg0] *= *arg1; break;
/* div   */	case 0xC:  reg[instr.arg0] /= *arg1; break;
/* mod   */	//case 0xD:  vm->pMemory->remainder = reg[instr.arg0] % *arg1; break;
/* rem   */	//case 0xE:  reg[instr.arg0] = vm->pMemory->remainder; break;
/* not   */	case 0xF:  reg[instr.arg0] = ~(reg[instr.arg0]); break;
/* xor   */	case 0x10:  reg[instr.arg0] ^= *arg1;  break;
/* or    */	case 0x11: reg[instr.arg0] |= *arg1;   break;
/* and   */	case 0x12: reg[instr.arg0] &= *arg1;   break;
/* shl   */	case 0x13: reg[instr.arg0] <<= *arg1;  break;
/* shr   */	case 0x14: reg[instr.arg0] >>= *arg1;  break;
/* cmp   */	case 0x15: reg[32] = ((reg[instr.arg0] == *arg1) | (reg[instr.arg0] > *arg1) << 1); break;
/* jmp   */	//case 0x17: stack_push(vm->pMemory, instr_idx);
/* call  */	case 0x16: currentAddr = reg[instr.arg0] - 1; break;
/* ret   */	//case 0x18: stack_pop(vm->pMemory, instr_idx);
/* je    */	case 0x19: if(reg[32]   & 0x1)  currentAddr = instr.arg0 - 1; break;
/* jne   */	case 0x1A: if(!(reg[32] & 0x1)) currentAddr = instr.arg0 - 1; break;
/* jg    */	case 0x1B: if(reg[32]   & 0x2)  currentAddr = instr.arg0 - 1; break;
/* jge   */	case 0x1C: if(reg[32]   & 0x3)  currentAddr = instr.arg0 - 1; break;
/* jl    */	case 0x1D: if(!(reg[32] & 0x3)) currentAddr = instr.arg0 - 1; break;
/* jle   */	case 0x1E: if(!(reg[32] & 0x2)) currentAddr = instr.arg0 - 1; break;
/* prn   */	case 0x1F: std::cout << reg[instr.arg0] << std::endl;;
	}
	return true;
}

