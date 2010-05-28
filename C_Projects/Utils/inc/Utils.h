#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#ifndef uns64
#define uns64 uint64_t
#endif

#ifndef int64
#define int64 int64_t
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

int Length_int(int);
int Length_uns64(uint64_t);
int Length_int64(int64_t);
int LengthBin_int(int);
int LengthBin_uns64(uint64_t);
void Clear(int*, int);
void RandomizeArray(int*, int);
int GetMicrosecondClock();
float GetMillisecondClock();
float GetSecondClock();

#endif
