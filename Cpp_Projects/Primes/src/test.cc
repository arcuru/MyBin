#include "Primes.h"
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	Primes p(atoi(argv[1]));
	return 0;
	int* list = p.getList();
	int count = 0;
	int max = 0;
	for (int i = 0; list[i] != 0; i++) {
		count++;
		max = list[i];
	}
	cout << max << endl;
	cout << count << endl;
	return 0;
}

