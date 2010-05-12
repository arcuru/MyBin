#include "C_Euler.h"

/*
 #a 100
 #b 50
 #c 20
 #d 10
 #e 5
 #f 2
 #g 1*/

static int total(int a, int b, int c, int d, int e, int f)
{
    return (100 * a) + (50 * b) + (20 * c) + (10 * d) + (5 * e) + (2 * f);
}

int64 Euler_31()
{
    int num, a, b, c, d, e, f;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    num = 1;
    for (a = 0; a <= 2; a++) {
        if (total(a, b, c, d, e, f) == 200) {
            num++;
            continue;
        }
        for (b = 0; b <= 4; b++) {
            if (total(a, b, c, d, e, f) == 200) {
                num++;
                continue;
            }
            for (c = 0; c <= 10; c++) {
                if (total(a, b, c, d, e, f) == 200) {
                    num++;
                    continue;
                }
                for (d = 0; d <= 20; d++) {
                    if (total(a, b, c, d, e, f) == 200) {
                        num++;
                        continue;
                    }
                    for (e = 0; e <= 40; e++) {
                        if (total(a, b, c, d, e, f) == 200) {
                            num++;
                            continue;
                        }
                        for (f = 0; f <= 100; f++) {
                            if (total(a, b, c, d, e, f) == 200) {
                                num++;
                                continue;
                            }
                            if (total(a, b, c, d, e, f) < 200) {
                                num++;
                                continue;
                            }
                        }
                        f = 0;
                    }
                    e = 0;
                }
                d = 0;
            }
            c = 0;
        }
        b = 0;
    }
    return (int64) num;
}
