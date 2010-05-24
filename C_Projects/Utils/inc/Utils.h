#ifndef UTILS_H
#define UTILS_H

#ifndef uns64
#define uns64 unsigned long long
#endif

#ifndef int64
#define int64 long long
#endif

typedef enum {FALSE, TRUE} bool;
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

int Length_int(int);
int Length_uns64(uns64);
int Length_int64(int64);
int LengthBin_int(int);
int LengthBin_uns64(uns64);
int* Clear(int*, int);
void RandomizeArray(int*, int);
int GetMicrosecondClock();
float GetMillisecondClock();
float GetSecondClock();

#endif
