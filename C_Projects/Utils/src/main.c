#include "Utils.h"
#include <sys/time.h>
#include <stdlib.h>

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

int Length_u64(uint64_t n)
{
    int digits = 0;
    while (n) {
        n /= 10;
        digits++;
    }
    return digits;
}

int Length_s64(int64_t n)
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

int LengthBin_u64(uint64_t n)
{
    int digits = 0;
    while (n) {
        n >>= 1;
        digits++;
    }
    return digits;
}

//Sets a list of given length to 0's

void Clear(int* list, int length)
{
    while (length--)
        *list++=0;
    return;
}

void RandomizeArray(int d[], int arraySize)
{
    // Populate with random values
    static int seeded = 0;
    static uint32_t heuristic_sequence = 0;
    if (!seeded) {
        // Seed the random number generator with time of day
        struct timeval tv;
        gettimeofday(&tv, 0);
        heuristic_sequence++;   // Always make sure different than last time.
        int seed = (tv.tv_sec^tv.tv_usec^(heuristic_sequence << 8)) & 0x7fffffff;
        srand48(seed);
        seeded = 1;
    }
    int i;
    for (i = 0; i < arraySize; ++i) {
        d[i] = (int)(drand48() * 1000.0);
    }
}

//Returns current time in microseconds

int GetMicrosecondClock()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    static int startsec = 0;
    static char first = true;
    if (first && 0 == startsec) {
        startsec = tv.tv_sec;
        first = false;
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

