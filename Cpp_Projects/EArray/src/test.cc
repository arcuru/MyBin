#include "EArray.h"
#include <iostream>
using namespace std;

int main()
{
	int* list = p.getList();
	int count = 0;
	for (int i = 0; list[i] != 0; i++) {
		count++;
	}
	cout << count << endl;
	return 0;
}

