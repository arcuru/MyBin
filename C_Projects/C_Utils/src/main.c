#include "C_Utils.h"
#include <sys/time.h>

//Returns number of digits of inputted number in base 10

int Length_int(int n)
{
    int digits = 0;
    while (n) {
        n /= 10;
        digits++;
    }
    return digits;
}

int Length_uns64(uns64 n)
{
    int digits = 0;
    while (n) {
        n /= 10;
        digits++;
    }
    return digits;
}

int Length_int64(int64 n)
{
    int digits = 0;
    while (n) {
        n /= 10;
        digits++;
    }
    return digits;
}

//Returns number of digits of inputed number in base 2

int LengthBin_int(int n)
{
    int digits = 0;
    while (n) {
        n >>= 1;
        digits++;
    }
    return digits;
}

int LengthBin_uns64(uns64 n)
{
    int digits = 0;
    while (n) {
        n >>= 1;
        digits++;
    }
    return digits;
}

//Sets a list of given length to 0's

int* Clear(int* list, int length)
{
    int i;
    for (i = 0; i < length; i++) {
        list[i] = 0;
    }
    return list;
}

//Returns current time in microseconds

int GetMicrosecondClock()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    static int startsec = 0;
    static char first = TRUE;
    if (first) {
        startsec = tv.tv_sec;
        first = FALSE;
    }
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

//Returns current time in milliseconds

float GetMillisecondClock()
{
    return (float) GetMicrosecondClock() / 1000;
}

//Returns current time in seconds

float GetSecondClock()
{
    return GetMillisecondClock() / 1000;
}

