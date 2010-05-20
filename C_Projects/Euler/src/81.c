#include "Euler.h"
#include <stdio.h>

int64 Euler_81()
{
    int array[80][80];
    char filepath[100];
    snprintf(filepath,sizeof(filepath),"%s81.txt",EULER_DATA_PATH);
    FILE* in = fopen(filepath, "r");
    if (in == NULL)
        return 0;
    int c = 0;
    int n, r;
    for (n = 0; n < 80* 80 ; n++) {
        r = fscanf(in, "%d", &c);
        array[n / 80][n % 80] = c;
        c = fgetc(in);
    }
    r = 0;
    for (n = 1; n <= 160; n++) {
        r = n;
        c = 0;
        while (r + 1) {
            if (c < 80 && r < 80) {
                if (r == 0) {
                    array[r][c] += array[r][c - 1];
                } else if (c == 0) {
                    array[r][c] += array[r - 1][c];
                } else {
                    if (array[r - 1][c] < array[r][c - 1]) {
                        array[r][c] += array[r - 1][c];
                    } else {
                        array[r][c] += array[r][c - 1];
                    }
                }
            }
            c++;
            r--;
        }
    }
    fclose(in);
    return (int64) array[79][79];
}
