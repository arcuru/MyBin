#include "C_Euler.h"
#include "C_NumberTheory.h"

static int Palindrome(int num)
{
    int size = 0;
    int tmp = num;
    while (tmp > 0) {
        tmp = tmp / 10;
        size++;
    }
    int count = 0;
    int test = 1;
    while (count <= size - 1 - count) {
        if ((num / (Power(10, count))) % 10 != (num / (Power(10, (size - 1
                                                - count)))) % 10) {
            test = 0;
        }
        count++;
    }
    return test;
}

int64 Euler_4()
{
    int a = 999;
    int b = 999;
    int ans = 0;
    int test = 1;
    while (test == 1) {
        while (b >= a) {
            if (Palindrome(a * b) == 1) {
                if (a * b > ans) {
                    ans = a * b;
                }
            }
            b--;
        }
        a--;
        if (a < 900) {
            break;
        }
        b = 999;
    }
    return (int64) ans;
}
