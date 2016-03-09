#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

int Length_int(int);
int Length_u64(uint64_t);
int Length_s64(int64_t);
int LengthBin_int(int);
int LengthBin_u64(uint64_t);
void Clear(int*, int);
void RandomizeArray(int*, int);
int GetMicrosecondClock();
float GetMillisecondClock();
float GetSecondClock();

#endif
