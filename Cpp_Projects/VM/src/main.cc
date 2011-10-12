#include "Program.h"
#include "Memory.h"
#include "CPU.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 1)
		return 1;
	Program g;
	g.LoadFile(argv[1]);
	Memory mem;
	CPU foo;
	foo.Init(&g, &mem);
	foo.Run();
	return 0;
}

