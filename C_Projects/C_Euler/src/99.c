#include "C_Euler.h"
#include <stdio.h>
#include <math.h>
typedef long double ld;

int64 Euler_99()
{
    char array[20];
    char filepath[100];
    snprintf(filepath,sizeof(filepath),"%s99.txt",C_EULER_DATA_PATH);
    FILE* data = fopen(filepath, "r");
    if (data == NULL)
        return 0;
    int ans = 0;
    int line = 1;
    ld max = 0;
    while (fgets(array, 20, data) != NULL) {
        ld a = 0;
        int i, dex = 0;
        for (i = 0; array[i] != ','; i++) {
            a *= 10;
            a += (int) array[i] - (int) '0';
            dex = i;
        }
        ld b = 0;
        for (i = dex + 2; array[i] >= '0' && array[i] <= '9'; i++) {
            b *= 10;
            b += (int) array[i] - (int) '0';
        }
        //printf("%d\t%d\n",a,b);
        ld test = b * logl(a);
        if (test > max) {
            max = test;
            ans = line;
        }
        line++;
    }
    fclose(data);
    return (int64) ans;
}
