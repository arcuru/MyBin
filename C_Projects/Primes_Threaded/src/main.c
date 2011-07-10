#include "Primes_Threaded.h"
#include "Primes.h"
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define	mark(mod,n)	while(mod>30) {							\
						mod-=30;							\
						n+=1;								\
					}										\
					kk=0;									\
					switch(mod) {							\
						case 1:	kk=1;	break;				\
						case 7:	kk=2;	break;				\
						case 11:	kk=4;	break;			\
						case 13:	kk=8;	break;			\
						case 17:	kk=16;	break;			\
						case 19:	kk=32;	break;			\
						case 23:	kk=64;	break;			\
						case 29:	kk=128;	break;			\
					}										\
					/*pthread_mutex_lock(marky_mutex);*/		\
					prime[n] |= kk;							\
					/*pthread_mutex_unlock(marky_mutex);*/
					//If these locks weren't necessary it'd be viable

typedef struct SieveEratosthenesStruct {
	int sqrtEnd;
	unsigned char* primes;
	int threadid;
	int N;
	pthread_mutex_t *grabby_mutex;
	pthread_mutex_t *marky_mutex;
	int* currentPos;
} SieveEratosthenesStruct;

static void *SieveEratosthenesThread(void* input) {
	SieveEratosthenesStruct* SEStruct = (SieveEratosthenesStruct*) input;
	unsigned char* prime = (*SEStruct).primes;
	int sqrtEnd = (*SEStruct).sqrtEnd;
	//int threadid = (*SEStruct).threadid;
	int N = (*SEStruct).N;
	int* currentPos = (*SEStruct).currentPos;
	pthread_mutex_t *grabby_mutex = (*SEStruct).grabby_mutex;
	//pthread_mutex_t *marky_mutex = (*SEStruct).marky_mutex;

	int n, s, j, num, num1, num2, num4, num6;
	int mod = 0, mod2 = 0, mod22 = 0, mod23 = 0;
	int incr2, incr4, incr6, s30;
	unsigned char k, kk;
	for (n = 0, num1 = 0; n <= sqrtEnd; num1 += 30, n++) {
		if (n < (*currentPos))
			continue;
		pthread_mutex_lock(grabby_mutex);
		if (n >= (*currentPos))
			(*currentPos)++;
		else {
			pthread_mutex_unlock(grabby_mutex);
			continue;
		}
		pthread_mutex_unlock(grabby_mutex);
		for (j = 0, k = 1; k; j++, k += k) {
			if (!(prime[n] & k)) {
				num = num1;
				switch (j) {//mod=(num^2)%30; mod2=(num*2)%30;
				case 0:
					mod = 1;
					mod2 = 2;
					mod22 = 4;
					mod23 = 6;
					num += 1;
					break;
				case 1:
					mod = 19;
					mod2 = 14;
					mod22 = 28;
					mod23 = 12;
					num += 7;
					break;
				case 2:
					mod = 1;
					mod2 = 22;
					mod22 = 14;
					mod23 = 6;
					num += 11;
					break;
				case 3:
					mod = 19;
					mod2 = 26;
					mod22 = 22;
					mod23 = 18;
					num += 13;
					break;
				case 4:
					mod = 19;
					mod2 = 4;
					mod22 = 8;
					mod23 = 12;
					num += 17;
					break;
				case 5:
					mod = 1;
					mod2 = 8;
					mod22 = 16;
					mod23 = 24;
					num += 19;
					break;
				case 6:
					mod = 19;
					mod2 = 16;
					mod22 = 2;
					mod23 = 18;
					num += 23;
					break;
				case 7:
					mod = 1;
					mod2 = 28;
					mod22 = 26;
					mod23 = 24;
					num += 29;
					break;
				}
				s = num * num;
				if (s >= N)
					break;
				num2 = num << 1;
				num4 = num2 << 1;
				num6 = num4 + num2;
				incr2 = num2 / 30;
				incr4 = num4 / 30;
				incr6 = num6 / 30;
				s30 = s / 30;
				switch (j)do {
					case 0: mark(mod,s30); s+=num6;
					if (s>=N) break;
					s30+=incr6; mod+=mod23;
					case 1: mark(mod,s30); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 2: mark(mod,s30); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
					case 3: mark(mod,s30); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 4: mark(mod,s30); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
					case 5: mark(mod,s30); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 6: mark(mod,s30); s+=num6;
					if (s>=N) break;
					s30+=incr6; mod+=mod23;
					case 7: mark(mod,s30); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
				}while(1);
			}
		}
	}
	pthread_exit(NULL);
}

unsigned char* SieveEratosthenesThreaded(int N) {
	int SQRTN = (int) sqrt(N);
	int sqrtEnd = SQRTN / 30;
	int primeEnd = N / 30;
	unsigned char* prime = (unsigned char*) calloc(primeEnd + 1, sizeof(char));
	if (!prime) {
		printf("Memory Fail\n");
		return NULL;
	}
	prime[0] |= 1;

	pthread_t thread[PRIMES_NTHREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	SieveEratosthenesStruct inputs[PRIMES_NTHREADS];
	pthread_mutex_t grabby_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&grabby_mutex, NULL);
	pthread_mutex_t marky_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&marky_mutex, NULL);
	int t, rc;
	int currentPos = 0;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		inputs[t].primes = prime;
		inputs[t].sqrtEnd = sqrtEnd;
		inputs[t].threadid = t;
		inputs[t].N = N;
		inputs[t].grabby_mutex = &grabby_mutex;
		inputs[t].marky_mutex = &marky_mutex;
		inputs[t].currentPos = &currentPos;
		rc = pthread_create(&thread[t], &attr, SieveEratosthenesThread,
				(void*) &inputs[t]);
		if (rc) {
			printf("pthread_create failed\n%d\n", rc);
			exit(1);
		}
	}
	void* status;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		pthread_join(thread[t], &status);
	}

	return prime;
}

typedef struct primeListStruct {
	unsigned char* primes;
	int* list;
	int* index;
	int primeEnd;
	int threadid;
} primeListStruct;

#define pLhelp(x)	list[count]=x; count++; break;
static void *primeListThread(void* input) {
	primeListStruct* ListStruct = (primeListStruct*) input;
	unsigned char* prime = (*ListStruct).primes;
	int* list = (*ListStruct).list;
	int* index = (*ListStruct).index;
	int primeEnd = (*ListStruct).primeEnd;
	int threadid = (*ListStruct).threadid;
	int begin = (primeEnd / PRIMES_NTHREADS) * threadid;
	int end = 0;
	if (threadid + 1 != PRIMES_NTHREADS)
		end = (primeEnd / PRIMES_NTHREADS) * (threadid + 1);
	else
		end = primeEnd + 1;
	int count = index[threadid];
	int n, k;
	unsigned char s;
	for (n = begin; n < end; n++) {
		for (k = 0, s = 1; s; k++, s += s) {
			if (!(prime[n] & s)) {
				switch (k) {
				case 0:
					pLhelp(n*30+1)
				case 1:
					pLhelp(n*30+7)
				case 2:
					pLhelp(n*30+11)
				case 3:
					pLhelp(n*30+13)
				case 4:
					pLhelp(n*30+17)
				case 5:
					pLhelp(n*30+19)
				case 6:
					pLhelp(n*30+23)
				case 7:
					pLhelp(n*30+29)
				}
			}
		}
	}
	pthread_exit(NULL);
}

int* primeListEThreaded(int N) {
	return primeListEThreaded_inc(N, SieveEratosthenes(N));
}

int* primeListEThreaded_inc(int N, unsigned char* prime) {
	int primeEnd = N / 30;
	int n, k;
	unsigned char s;
	int top = 3;
	int spread = primeEnd / PRIMES_NTHREADS;
	int spreadnum = 0;
	int* StartInd = (int*) malloc(sizeof(int) * PRIMES_NTHREADS);
	for (n = 0; n <= primeEnd; n++) { //Counts primes
		if (n == spreadnum * spread && spreadnum < PRIMES_NTHREADS) {
			StartInd[spreadnum] = top;
			spreadnum++;
		}
		for (k = 0, s = 1; s; k++, s += s)
			if (!(prime[n] & s))
				top++;
	}
	int* list = (int*) (malloc)(sizeof(int) * (top + 8));
	if (!list) {
		printf("Memory Fail\n");
		free(StartInd);
		return NULL;
	}
	list[0] = 2;
	list[1] = 3;
	list[2] = 5;
	pthread_t thread[PRIMES_NTHREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	primeListStruct inputs[PRIMES_NTHREADS];
	int t, rc;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		inputs[t].primes = prime;
		inputs[t].list = list;
		inputs[t].index = StartInd;
		inputs[t].primeEnd = primeEnd;
		inputs[t].threadid = t;
		rc = pthread_create(&thread[t], &attr, primeListThread,
				(void*) &inputs[t]);
		if (rc) {
			printf("pthread_create failed\n%d\n", rc);
			exit(1);
		}
	}
	void* status;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		pthread_join(thread[t], &status);
	}
	list[top] = 0;
	while (list[top - 1] && list[top - 1] > N) {
		top--;
		list[top] = 0;
	}
	return list;
}

typedef struct primeIndexStruct {
	unsigned char* primes;
	unsigned char* list;
	int primeEnd;
	int threadid;
} primeIndexStruct;

#define pILhelp(x)	list[x]=1; break;
static void *primeIndexThread(void* input) {
	primeIndexStruct* IndexStruct = (primeIndexStruct*) input;
	unsigned char* prime = (*IndexStruct).primes;
	unsigned char* list = (*IndexStruct).list;
	int primeEnd = (*IndexStruct).primeEnd;
	int threadid = (*IndexStruct).threadid;

	int n, k;
	unsigned char s;
	for (n = threadid; n <= primeEnd; n += PRIMES_NTHREADS) {
		for (k = 0, s = 1; s; k++, s += s) {
			if (!(prime[n] & s)) {
				switch (k) {
				case 0:
					pILhelp(n*30+1)
				case 1:
					pILhelp(n*30+7)
				case 2:
					pILhelp(n*30+11)
				case 3:
					pILhelp(n*30+13)
				case 4:
					pILhelp(n*30+17)
				case 5:
					pILhelp(n*30+19)
				case 6:
					pILhelp(n*30+23)
				case 7:
					pILhelp(n*30+29)
				}
			}
		}
	}
	pthread_exit(NULL);
}

unsigned char* primeIndexListEThreaded(int N) {
	return primeIndexListEThreaded_inc(N, SieveEratosthenes(N));
}

unsigned char* primeIndexListEThreaded_inc(int N, unsigned char* prime) {
	unsigned char* list = (unsigned char*) calloc(N + 1, sizeof(char));
	if (!list) {
		printf("Memory Fail\n");
		return NULL;
	}
	list[2] = 1;
	list[3] = 1;
	list[5] = 1;
	int primeEnd = N / 30;
	pthread_t thread[PRIMES_NTHREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	primeIndexStruct inputs[PRIMES_NTHREADS];
	int t, rc;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		inputs[t].primes = prime;
		inputs[t].list = list;
		inputs[t].primeEnd = primeEnd;
		inputs[t].threadid = t;
		rc = pthread_create(&thread[t], &attr, primeIndexThread,
				(void*) &inputs[t]);
		if (rc) {
			printf("pthread_create failed\n%d\n", rc);
			exit(1);
		}
	}
	void* status;
	for (t = 0; t < PRIMES_NTHREADS; t++) {
		pthread_join(thread[t], &status);
	}
	return list;
}
