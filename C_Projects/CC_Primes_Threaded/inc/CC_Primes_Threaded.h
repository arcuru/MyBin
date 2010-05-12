#ifndef CC_PRIMES_THREADED_H_
#define CC_PRIMES_THREADED_H_

/*
 * Sets the number of threads to use for the Prime Threading functions
 */
#define PRIMES_CC_NTHREADS 2

#ifndef uns64
	#define uns64 unsigned long long
#endif

/*
 * Threaded
 *
 * Each functions performs in exactly the same way as their non-threaded counterparts
 */
unsigned char* SieveEratosthenesThreaded(int);
int* primeListEThreaded(int);
int* primeListEThreaded(int,unsigned char*);
unsigned char* primeIndexListEThreaded(int);
unsigned char* primeIndexListEThreaded(int,unsigned char*);

#endif /* CC_PRIMES_THREADED_H_ */
