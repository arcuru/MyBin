#ifndef UTILS_CC_H
#define UTILS_CC_H

//#include <sys/time.h>

#ifndef uns64
#define uns64 unsigned long long
#endif

#ifndef int64
#define int64 long long
#endif

int Length(int);
int Length(uns64);
int Length(int64);
int LengthBin(int);
int LengthBin(uns64);
int* Clear(int*, int);
int GetMicrosecondClock();
float GetMillisecondClock();
float GetSecondClock();

#endif
