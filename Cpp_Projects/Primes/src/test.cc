#include "Primes.h"
#include <iostream>
using namespace std;

int main()
{
	Primes p(100000000);
	int* list = p.getList();
	int count = 0;
	for (int i = 0; list[i] != 0; i++) {
		count++;
	}
	cout << count << endl;
	return 0;
}

