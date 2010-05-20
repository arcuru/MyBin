#include <stdio.h>
#include <stdlib.h>
#include "Primes.h"


int main()
{
    int i;
    int N = 1000000;
    int max=0;
    int maxnum=0;
    unsigned char* list = SieveEratosthenes(N);
    int* primes = primeListE_inc(50000,list);
    int ind,j;
    for (i=6; i<N; i+=2) { //only even numbers
    	j=-1;
        for (ind=0; primes[ind]!=0; ++ind) {
            if (isPrimeE(i-primes[ind],list)) {
                j=primes[ind];
                break;
            }
        }
        if (j==-1) {
        	printf("%d\t%d\n",j,i);
        }
        if (max<j) {
            max=j;
            maxnum=i;
            printf("%d\t%d\n",max,maxnum);
        }
    }
    return 0;
}
