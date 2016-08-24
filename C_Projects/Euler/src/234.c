#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>
#include <math.h>

int64_t Euler_234()
{
    uint64_t N = 999966663333ll;
    int primetop = (int)(sqrt(N)+500);
    uint32_t* primeList = primeListE(primetop);
    uint64_t total=0;
    int index=0;
    uint64_t ups=primeList[index++];
    uint64_t lps2=0;
    uint64_t ups2=ups*ups;
    uint64_t tmp1=lps2;
    uint64_t tmp2=ups2;
    while ( lps2 <= N ) {
        uint64_t lps=0;
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
    free(primeList);
    return (int64_t)total;
}
