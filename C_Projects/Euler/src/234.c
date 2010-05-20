#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>
#include <math.h>

int64 Euler_234()
{
    uns64 N = 999966663333ll;
    int primetop = (int)(sqrt(N)+500);
    int* primeList=primeListE(primetop);
    uns64 total=0;
    int index=0;
    uns64 lps=0;
    uns64 ups=primeList[index++];
    uns64 lps2=0;
    uns64 ups2=ups*ups;
    uns64 tmp1=lps2;
    uns64 tmp2=ups2;
    while ( lps2 <= N ) {
        lps=ups;
        ups=primeList[index++];
        lps2=ups2;
        ups2=ups*ups;
        tmp1=lps2+lps;
        tmp2=ups2-ups;
        while ( tmp1<ups2 ) {
            if ( tmp1%ups )
                if ( tmp1<=N )
                    total+=tmp1;
            tmp1+=lps;
        }
        while ( tmp2>lps2 ) {
            if ( tmp2%lps )
                if ( tmp2<=N )
                    total+=tmp2;
            tmp2-=ups;
        }
    }

    return (int64)total;
}
