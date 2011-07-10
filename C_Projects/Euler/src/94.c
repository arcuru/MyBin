#include "Euler.h"
#include <math.h>

//static void *Thread(void *in)
//{
//    int64_t total = 0;
//    int *spec = (int *)in;
//    int a;
//    for (a = 3 ;; a += 2) {
//        int c = a+*spec;
//        int64_t p = ((a * 2) + c) / 2;
//        if (p * 2 > 1000000000) {
//            pthread_exit((void*) total);
//        }
//        int64_t t = sqrt(p) * sqrt(p - c);
//        if (t * t == p * (p - c))
//            total += (p * 2);
//    }
//}
//
//int64_t Euler_94()
//{
//    pthread_t thread1, thread2;
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//    int a=1,b=-1;
//    if (pthread_create(&thread1, &attr, Thread, (void*) &b))
//        return 0;
//    if (pthread_create(&thread2, &attr, Thread, (void*) &a))
//        return 0;
//    pthread_attr_destroy(&attr);
//    void *tmptotal;
//    if (pthread_join(thread1, &tmptotal))
//        return 0;
//    int64_t total = (int64_t) tmptotal;
//    if (pthread_join(thread2, &tmptotal))
//        return 0;
//    total += (int64_t) tmptotal;
//    return (int64_t) total;
//}

int64_t Euler_94()
{
    int i;
    int64_t answer=0;
#pragma omp parallel for
    for (i=-1; i<=1; i+=2) {
        int64_t t,p;
        int a,c;
        for (a = 3 ;(a*3)+i<=1000000000; a += 2) {
            c = a+i;
            p = ((a * 3) + i) / 2; //p is half the perimeters
            t = sqrt(p) * sqrt(p-c);
            if (t * t == p * (p-c))
                answer += (p * 2);
        }
    }
    return answer;
}
