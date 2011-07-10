#include "Euler.h"

static char Late = 0;
static int List = 0;
static int64_t count = 0;

//Absent = 1
//On Time = 0


static void rec(int index)
{
    if (index == 30) {
        count++;
        return;
    }
    rec(index + 1);
    if (Late == 0) {
        Late++;
        rec(index + 1);
        Late--;
    }
    if (index > 1) {
        if (((3 << (index - 2)) & List) != (3 << (index - 2))) {
            List |= 1 << index;
            rec(index + 1);
            List ^= 1 << index;
        }
    } else {
        List |= 1 << index;
        rec(index + 1);
        List ^= 1 << index;
    }
    return;
}

int64_t Euler_191()
{
    rec(0);
    return count;
}
