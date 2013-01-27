#include "Primes.h"
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	int tmp = 1000000;
	if ( argc > 1 )
		tmp = atoi(argv[1]);
	Primes p( tmp );
	int* list = p.getList();
	uint64_t max = 0;
	for (int i = 0; list[i] != 0; i++) {
		max += list[i];
	}
	cout << max << endl;
	return 0;
}

