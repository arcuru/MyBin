#include "CC_NumberTheory.h"
#include "CC_Primes.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//Creates array of totient values
//Each value at Index is the totient of Index

int* EulersTotient(int N) {
	int* list = (int*) (malloc)(sizeof(int) * (N + 1));
	if (!list) {
		printf("Not enough memory\n");
		return NULL;
	}
	int n, s;
	for (n = 1; n <= N; n += 2)
		list[n] = n - 1;
	for (n = 2; n <= N; n += 2)
		list[n] = (n >> 1);
	for (n = 3; n <= N; n += 2)
		if (list[n] == n - 1)
			for (s = 2 * n; s <= N; s += n)
				list[s] = list[s] - list[s] / n;

	return list;
}
/*	Elizabeth's, it's a little slower
 int* EulersTotient(int N) {
 unsigned char* primes = primeIndexListE(N);
 int* tot = (int*)malloc(sizeof(int)*(N+1));
 for (int i = 0; i < N; i++)
 tot[i] = i;

 for (int i = 2; i < N; i++) {
 if (primes[i]) {
 tot[i] = i - 1;
 for (int j = 2* i ; j < N; j = j + i)
 tot[j] = (tot[j] - tot[j] / i);
 }
 }

 return tot;
 }

 *boolean[] primes = primes(n);
 int[] tot = new int[primes.length];
 for (int i = 0; i < tot.length; i++)
 tot[i] = i;

 for(int i = 2; i < primes.length; i++)
 {
 if (!primes[i])
 {
 tot[i] = i-1;
 for(int j = 2*i; j < tot.length; j = j + i)
 tot[j] = (int) (tot[j]*(1-1.0/i));
 }
 }

 return tot;
 */
//Euclid's formula for GCD
int GCD(int m, int n) {
	int ans;
	while (1) {
		int r = m % n;
		if (!r) {
			ans = n;
			break;
		}
		m = n;
		n = r;
	}
	return ans;
}

//Written in Wordpad, needs testing
//Returns a^b
int Power(int a, int b) {
	if (b < 0)
		return -1;
	if (!b)
		return 1;
	if (!a)
		return 0;
	if (!(b & 1))
		return Power(a * a, b >> 1);
	else
		return a * Power(a * a, b >> 1);
	return 0;
}

double intpow(double a, int b) {
	if (b < 0) {
		a = 1.0 / a;
		b = -b;
	}
	double result = 1.0;
	while (b) {
		if (b & 1)
			result *= a;
		a *= a;
		b >>= 1;
	}
	return result;
}

int Factorial(int n) {
	int out = 1;
	int i;
	for (i = n; i > 1; i--)
		out *= i;
	return out;
}
