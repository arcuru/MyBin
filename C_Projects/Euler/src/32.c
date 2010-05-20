#include "Euler.h"

//a 1 or 2 digits, b 3 or 4 digits, c 4 digits, sum must be 9 digits
static int isPandigital(int a, int b, int c)
{
    int list[10], count;
    for (count = 1; count < 10; count++) {
        list[count] = 0;
    }
    list[a % 10]++;
    list[b % 10]++;
    list[(b / 10) % 10]++;
    list[(b / 100) % 10]++;
    if (a > 10) {
        list[(a / 10) % 10]++;
    } else {
        list[(b / 1000) % 10]++;
    }
    list[c % 10]++;
    list[(c / 10) % 10]++;
    list[(c / 100) % 10]++;
    list[(c / 1000) % 10]++;
    for (count = 1; count < 10; count++) {
        if (list[count] != 1) {
            return 0;
        }
    }
    return 1;
}

int64 Euler_32()
{

    int a, b, c, alist[50], dex, sum;
    int counter = 1;
    for (c = 1000; c < 10000; c++) {
        for (a = 2; a < 100; a++) {
            if (c % a != 0) {
                continue;
            } else {
                b = c / a;
            }
            if ((a < 10) && (b < 1000)) {
                continue;
            } else {
                if (isPandigital(a, b, c) != 0) {
                    alist[counter] = c;
                    counter++;
                }
            }

        }
    }
    sum = 0;
    for (dex = 1; dex < counter; dex++) {
        if (alist[dex] != alist[dex - 1]) {
            sum += alist[dex];
        }
    }
    return (int64) sum;
}
