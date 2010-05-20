#include "Euler.h"
#include "NumberTheory.h"

int64 Euler_24()
{
    int digits = 10;
    int place = 1000000;
    int list[digits];
    int array[digits];
    int count = 0;
    uns64 out = 0;
    int i;
    for (i = 0; i < digits; i++) {
        int dex = 0;
        while (count + ((dex + 1) * Factorial(digits - 1 - i)) < place)
            dex++;
        count += dex * Factorial(digits - 1 - i);
        array[i] = dex;
    }
    for (i = 0; i < digits; i++)
        list[i] = i;
    for (i = 0; i < digits; i++) {
        out *= 10;
        out += list[array[i]];
        int q;
        for (q = array[i]; q < digits - i - 1; q++) {
            list[q] = list[q + 1];
        }
    }
    return (int64) out;
}
