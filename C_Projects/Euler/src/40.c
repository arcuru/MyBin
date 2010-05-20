#include "Euler.h"
#include "Utils.h"
#include <math.h>

int64 Euler_40()
{
    short array[1000010];
    int i;
    int count=1;
    for (i=1; count<=1000000; i++) {
        int check=Length_int(i);
        int g;
        for (g=check; g>0; g--) {
            int tmp=i/(pow(10,g-1));
            array[count]=tmp%10;
            count++;
        }
    }
    int product=1;
    for (i=1; i<=1000000; i*=10) {
        product*=array[i];
    }
    return (int64)product;
}
