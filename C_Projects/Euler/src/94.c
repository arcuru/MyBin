#include "Euler.h"
#include <pthread.h>
#include <math.h>

static void *Thread(void *in)
{
    int64 total = 0;
    int spec = (int) in;
    int a;
    for (a = 3; 1; a += 2) {
        int c = a + spec;
        int64 p = ((a * 2) + c) / 2;
        if (p * 2 > 1000000000) {
            pthread_exit((void*) total);
        }
        int64 t = sqrt(p) * sqrt(p - c);
        if (t * t == p * (p - c))
            total += (p * 2);
    }
}

int64 Euler_94()
{
    pthread_t thread1, thread2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if (pthread_create(&thread1, &attr, Thread, (void*) - 1))
        return 0;
    if (pthread_create(&thread2, &attr, Thread, (void*) 1))
        return 0;
    pthread_attr_destroy(&attr);
    void *tmptotal;
    if (pthread_join(thread1, &tmptotal))
        return 0;
    int64 total = (int64) tmptotal;
    if (pthread_join(thread2, &tmptotal))
        return 0;
    total += (int64) tmptotal;
    return (int64) total;
}
