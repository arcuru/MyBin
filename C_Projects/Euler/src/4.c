#include "Euler.h"
#include "NumberTheory.h"

static int Palindrome(int num)
{
    int size = 0;
    int tmp = num;
    while (tmp > 0) {
        tmp = tmp / 10;
        size++;
    }
    int count = 0;
    while (count <= size - 1 - count) {
        if ((num / (Power(10, count))) % 10 != (num / (Power(10, (size - 1 - count)))) % 10) {
			return 0;
        }
        count++;
    }
    return 1;
}

int64 Euler_4()
{
	int a, b, ans=0;
	for (a=999; a; a--) {
		for (b=999; b>=a; b--) {
            if (Palindrome(a * b) == 1) {
                if (a * b > ans) {
                    ans = a * b;
                }
            }
        }
    }
    return (int64) ans;
}
