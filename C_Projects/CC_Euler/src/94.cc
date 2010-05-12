#include "CC_Euler.h"
#include <pthread.h>
#include <math.h>

static void *Thread(void *in) {
	uns64 total = 0;
	int64 spec = (int64) in;
	int a;
	for (a = 3; 1; a += 2) {
		int c = a + spec;
		uns64 p = ((a << 1) + c) >> 1;
		if (p << 1 > 1000000000) {
			pthread_exit((void*) total);
		}
		uns64 t = sqrt(p) * sqrt(p - c);
		if (t * t == p * (p - c))
			total += (p << 1);
	}
}

int64 Euler_94() {
	pthread_t thread1, thread2;
	pthread_attr_t attr;
	int rc;
	int in = -1;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	rc = pthread_create(&thread1, &attr, Thread, (void*) in);
	if (rc)
		return 0;
	in = 1;
	rc = pthread_create(&thread2, &attr, Thread, (void*) in);
	if (rc)
		return 0;
	pthread_attr_destroy(&attr);
	void *tmptotal;
	rc = pthread_join(thread1, &tmptotal);
	if (rc)
		return 0;
	uns64 total = (uns64) tmptotal;
	rc = pthread_join(thread2, &tmptotal);
	if (rc)
		return 0;
	total += (uns64) tmptotal;
	return (int64) total;
}
