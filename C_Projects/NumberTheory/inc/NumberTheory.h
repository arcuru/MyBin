#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H
#include <stdint.h>
/*
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
*/
#ifndef uns64
#define uns64 unsigned long long
#endif

int* EulersTotient(int);
int GCD(int, int);
int64_t Power(int64_t,int64_t);
double intpow(double,int);
int Factorial(int);

#endif
