#include "EArray.h"
#include <iostream>
using namespace std;

#include <sys/time.h>
#include <stdlib.h>
#include <cstdint>
void RandomizeArray(int d[], int arraySize)
{
    // Populate with random values
    static int seeded = 0;
    static uint32_t heuristic_sequence = 0;
    if (!seeded) {
        // Seed the random number generator with time of day
        struct timeval tv;
        gettimeofday(&tv, 0);
        heuristic_sequence++;   // Always make sure different than last time.
        int seed = (tv.tv_sec^tv.tv_usec^(heuristic_sequence << 8)) & 0x7fffffff;
        srand48(seed);
        seeded = 1;
    }
    int i;
    for (i = 0; i < arraySize; ++i) {
        d[i] = (int)(drand48() * 1000.0);
    }
}

int main()
{
	int N = 10000;
	EArray<int> p(N);
	RandomizeArray(p.get_array(), N);
	int count = 0;
	for (int i = 0; i < N-1; i++) {
		if (p.get_index(i) > p.get_index(i+1))
			count++;
	}
	cout << count << endl;
	p.bubbleSort();
	count = 0;
	for (int i = 0; i < N-1; i++) {
		if (p.get_index(i) > p.get_index(i+1))
			count++;
	}
	
	cout << count << endl;
	return 0;
}

