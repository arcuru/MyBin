#ifndef PRIMES_THREADED_H_
#define PRIMES_THREADED_H_

/*
 * Sets the number of threads to use for the Prime Threading functions
 */
#define PRIMES_NTHREADS 2

/*
 * Threaded
 *
 * Each functions performs in exactly the same way as their non-threaded counterparts
 */
unsigned char* SieveEratosthenesThreaded(int);
int* primeListEThreaded(int);
int* primeListEThreaded_inc(int,unsigned char*);
unsigned char* primeIndexListEThreaded(int);
unsigned char* primeIndexListEThreaded_inc(int,unsigned char*);

#endif /* PRIMES_THREADED_H_ */
