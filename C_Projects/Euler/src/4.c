#include "Euler.h"
#include <stdbool.h>

// Checks if a number is a Palindrome
static bool Palindrome(int num)
{
	int rev = 0;
	int tmpnum = num;
	while ( tmpnum > 0 ) {
		rev *= 10;
		rev += tmpnum % 10;
		tmpnum /= 10;
	}
	if ( rev == num )
		return true;
	return false;
}

int64_t Euler_4()
{
	int a, b, ans=0;
	for (a=999; a; a--) {
		for (b=999; b>=a; b--) {
            if (a * b > ans) {
				if (Palindrome(a * b) == 1) {
                    ans = a * b;
                }
            }
        }
    }
    return (int64_t) ans;
}
