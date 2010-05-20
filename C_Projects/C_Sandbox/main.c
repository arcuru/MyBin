#include <stdio.h>
//#include <stdlib.h>
#include <math.h>
#include "C_NumberTheory.h"
#include "C_Utils.h"
#include "C_Sort.h"
#include "C_Primes.h"
#include "C_Primes_Threaded.h"

//void CheckSortedArray(int* e, int n) { // Verify that array e is (of length n) is properly sorted.
//	// Print an error message and call "exit(0)" if not
//	int k;
//	for (k = 1; k < n; k++) {
//		if (e[k] < e[k - 1]) {
//			printf("Array of size %d is not sorted at %d\n",n,k);
//			//exit(0);
//			return;
//		}
//	}
//}
//
//int main()
//{
//    const int maxSize = 512000/4; // Largest size array needed
//
//	// Array d is the array to be randomized
//	int d[maxSize]; // Largest size array for this assignment
//	// Array e is the output array (where the sorted array is stored).
//	int e[maxSize]; // Largest size array for this assignment
//	int n,size;
//	for (n = 0; n < 1; n++) {
//		for (size = 1000; size <= maxSize; size *= 2) {
////		    int i;
////		    for (i=0;i<size;i++)
////                d[i]=0;
//			RandomizeArray(d, size);
////            for (i=0;i<size;i++)
////                printf("%d\n",d[i]);
////            return;
//			int start = GetMillisecondClock();
//			ParallelBubbleSort(d, size,e);
////            BubbleSort(d,size);
////            InsertionSortBinary(d,size);
//			int end = GetMillisecondClock();
////			for (i=0;i<size;i++)
////                printf("%d\n",d[i]);
////            return;
//			CheckSortedArray(e, size);
//            printf("Parallel Bubble Sort of size %d took %d milliseconds\n",size,end-start);
//		}
//	}
//    return 0;
//}

#define MAXNUM  1000000
int main()
{
    unsigned char* primes = SieveEratosthenesThreaded(MAXNUM);
    int i,count=0;
    for (i=0;i<MAXNUM;i++) {
        if (isPrimeE(i,primes))
            count++;
    }
    printf("%d\n",count);
    return 0;
}
