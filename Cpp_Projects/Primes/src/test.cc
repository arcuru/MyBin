#include "Primes.h"
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	Primes p(atoi(argv[1]));
	int* list = p.getList();
	int count = 0;
	for (int i = 0; list[i] != 0; i++) {
		count++;
	}
	cout << count << endl;
	return 0;
}

