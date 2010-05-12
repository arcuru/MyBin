// Implementation of the bubble sort algorithm
// Patrick Jackson
#include <stdlib.h>
#include "cs1372.h"
#include <pthread.h>
//#include "gthread.h"

using namespace std;

struct BSortStruct {
	int* Array;
	int length;
	int threadid;
};

void CheckSortedArray(int* e, int n);

void *BubbleSort_P(void* input) {
	BSortStruct* BStruct = (BSortStruct*) input;
	int* d = (*BStruct).Array;
	int size = (*BStruct).length;
	int k, tmp;
	int i = 1;
	while (i < size) {
		k = i;
		while ((k > 0) && (d[k] < d[k - 1])) {
			tmp = d[k];
			d[k] = d[k - 1];
			d[k - 1] = tmp;
			k--;
		}
		i++;
	}
	pthread_exit(NULL);
}

// Here is the main sorting function.
// Array d is the input array to be sorted,
// n is the size of both d and e.
// Array e is where the sorted values are copied.
void ParallelBubbleSort(int* d, int n, int* e) {
	int nthreads = 8;
	int length = n / nthreads;

	pthread_t thread[nthreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	BSortStruct BSort[nthreads];

	for (int i = 0; i < nthreads; ++i) {
		BSort[i].Array = &d[i * length];
		if (i == nthreads - 1)
			BSort[i].length = n - (i * length);
		else
			BSort[i].length = length;
		BSort[i].threadid = i;
		pthread_create(&thread[i], &attr, BubbleSort_P, (void*) &BSort[i]);
	}
	void* status;
	for (int i = 0; i < nthreads; i++) {
		pthread_join(thread[i], &status);
	}

	int dex[nthreads];
	for (int i = 0; i < nthreads; i++) {
		dex[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		int min = 1 << 30;
		int smallestthread;
		for (int index = 0; index < nthreads; index++) {
			if (dex[index] == length) {
				continue;
			}
			if (d[index * length + dex[index]] < min) {
				min = d[index * length + dex[index]];
				smallestthread = index;
			}
		}
		e[i] = min;
		dex[smallestthread]++;
	}
	return;
}

void CheckSortedArray(int* e, int n) { // Verify that array e is (of length n) is properly sorted.
	// Print an error message and call "exit(0)" if not
	for (int k = 1; k < n; k++) {
		if (e[k] < e[k - 1]) {
			PrintLn("Array of size ", n, " is not sorted at ", k);
			exit(0);
		}
	}

}

int main() {
	const int maxSize = 512000; // Largest size array needed

	// Array d is the array to be randomized
	int d[maxSize]; // Largest size array for this assignment
	// Array e is the output array (where the sorted array is stored).
	int e[maxSize]; // Largest size array for this assignment
	for (int n = 0; n < 1; n++) {
		for (int size = 1000; size <= maxSize; size *= 2) {
			RandomizeArray(d, size);
			int start = GetMillisecondClock();
			ParallelBubbleSort(d, size, e);
			int end = GetMillisecondClock();
			CheckSortedArray(e, size);
			PrintLn("Parallel Bubble Sort of size ", size, " took ", end
					- start, " milliseconds");
		}
	}
}

