#include "Primes.h"
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
					prime[n] |= kk;

unsigned char* SieveEratosthenes(int N) {
	int SQRTN = (int) sqrt(N);
	int sqrtEnd = SQRTN / 30;
	int primeEnd = N / 30;
	unsigned char* prime = (unsigned char*) calloc(primeEnd + 1, sizeof(char));
	if (!prime) {
		printf("Memory Fail\n");
		return NULL;
	}
	int n, s, j, num, num1, num2, num4, num6;
	int mod = 0, mod2 = 0, mod22 = 0, mod23 = 0;
	int incr2, incr4, incr6, s30;
	unsigned char k, kk;
	prime[0] |= 1;
	for (n = 0, num1 = 0; n <= sqrtEnd; num1 += 30, n++) {
		for (j = 0, k = 1; k; j++, k += k) {
			if (!(prime[n] & k)) {
				num = num1;
				switch (j) {//mod=(num^2)%30; mod2=(num*2)%30; mod22=(mod2*2)%30;
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
	return prime;
}

//Returns array filled with primes from 2 to N
//Index 0 starts off with 2
//Fills an extra place with value of 0 for terminator
int* primeListE(int N) {
	return primeListE_inc(N, SieveEratosthenes(N));
}

#define pLhelp(x)	if (x>N) break; list[count]=x; count++; break;
int* primeListE_inc(int N, unsigned char* prime) {
	int primeEnd = N / 30;
	int n, k;
	unsigned char s;
	int top = 3;
	for (n = 0; n <= primeEnd; n++) //Counts primes
		for (k = 0, s = 1; s; k++, s += s)
			if (!(prime[n] & s))
				top++;

	int* list = (int*) (malloc)(sizeof(int) * top);
	if (!list) {
		printf("Memory Fail\n");
		return NULL;
	}
	int count = 3;
	list[0] = 2;
	list[1] = 3;
	list[2] = 5;
	for (n = 0; n <= primeEnd; n++) {
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
	list[count] = 0;
	return list;
}

//The first time it is called it returns the first prime in the list
//Each subsequent time it returns the next prime in the list
//Returns a 0 once complete
//List is in the form from SieveEratosthenes
//Null should be passed as the list for all but the first call
#define NPhelp(x)	if (x>saved_eol) return 0; ++current_bitval;current_bit+=current_bit;return x;
int NextPrime(int end_of_list, unsigned char* list) {
	static int saved_eol = 0;
	static int primeEnd = 0;
	if (saved_eol != end_of_list) {
		saved_eol = end_of_list;
		primeEnd = saved_eol / 30;
	}
	static unsigned char* saved_list = NULL;
	static int current_byte = 0, current_bitval = 0, last_prime = 0;
	static char current_bit = 1;
	if (list != NULL) {
		current_byte = 0;
		current_bit = 1;
		current_bitval = 0;
		saved_list = list;
		last_prime = 0;
	}
	if (last_prime < 5)
		switch (last_prime) {
		case 0:
			last_prime = 2;
			return 2;
		case 2:
			last_prime = 3;
			return 3;
		case 3:
			last_prime = 5;
			return 5;
		}
	for (; current_byte <= primeEnd; ++current_byte) {
		for (; current_bit; ++current_bitval, current_bit += current_bit) {
			if (!(saved_list[current_byte] & current_bit)) {
				switch (current_bitval) {
				case 0:
					NPhelp(current_byte*30+1)
				case 1:
					NPhelp(current_byte*30+7)
				case 2:
					NPhelp(current_byte*30+11)
				case 3:
					NPhelp(current_byte*30+13)
				case 4:
					NPhelp(current_byte*30+17)
				case 5:
					NPhelp(current_byte*30+19)
				case 6:
					NPhelp(current_byte*30+23)
				case 7:
					NPhelp(current_byte*30+29)
				}
			}
		}
		current_bitval=0;
		current_bit=1;
	}
//	printf("%d\t%d\t%d\n", current_byte, current_bitval, current_bit);
	return 0;
}

//Returns an array of unsigned char's that holds a 1
//at the index of a prime and 0 otherwise
unsigned char* primeIndexListE(int N) {
	return primeIndexListE_inc(N, SieveEratosthenes(N));
}

#define pILhelp(x)	list[x]=1; break;
unsigned char* primeIndexListE_inc(int N, unsigned char* prime) {
	unsigned char* list = (unsigned char*) calloc(N + 1, sizeof(char));
	if (!list) {
		printf("Memory Fail\n");
		return NULL;
	}
	list[2] = 1;
	list[3] = 1;
	list[5] = 1;
	int primeEnd = N / 30;
	int n, k;
	unsigned char s;
	for (n = 0; n <= primeEnd; n++) {
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
	return list;
}

//Returns an array filled with prime factors of input
//Repeats are in the output twice
//End is expressed by a value of 0
int* primeFactorsE(int N) {
	return primeFactorsE_inc(N, primeListE((int) sqrt(N) + 1));
}

int* primeFactorsE_inc(int N, int* primes) {
	int* list = (int*) calloc(32, sizeof(int));
	if (isPrime(N)){
        list[0]=N;
        list[1]=0;
        return list;
    }
	int n;
	int s = 0;
	for (n = 0; N > 1 && primes[n]; n++)
		if (!(N % primes[n])) {
			list[s] = primes[n];
			N /= list[s];
			n--;
			s++;
			if (isPrime(N)){
                list[s]=N;
                list[s+1]=0;
                return list;
			}
		}
	list[s] = 0;
	return list;
}

uns64* primeFactorsE_uns64(uns64 N) {
	int* primes = primeListE(1000000);
	uns64* list = (uns64*) calloc(64, sizeof(uns64));
	int n;
	int s = 0;
	for (n = 0; N > 1 && primes[n]; n++) {
		if (!(N % primes[n])) {
			list[s] = primes[n];
			N /= list[s];
			n--;
			s++;
		}
	}
	if (!(N - 1)) {
		list[s] = 0;
		return list;
	}
	if (isPrime(N)) {
		list[s] = N;
		s++;
		N = 1;
	}
	for (n = 999999; N > 1; n += 2) {
		if (isPrime(n)) {
			if (!(N % n)) {
				list[s] = n;
				N /= n;
				n -= 2;
				s++;
				if (isPrime(N)) {
					list[s] = N;
					s++;
					break;
				}
			}
		}
	}
	list[s] = 0;
	return list;
}

//Checks a single number for primality
//Must be within range of input list
//Returns TRUE if prime, FALSE if not

int isPrimeE(int n, unsigned char* primes) {
	if (n <= 6) {
		if (n == 2 || n == 3 || n == 5)
			return TRUE;
		return FALSE;
	}
	if (!(n & 1) || (n%3 == 0))
		return FALSE;
	switch (n % 30) {
	case 1:
		return !(primes[n / 30] & 1);
	case 7:
		return !(primes[n / 30] & 2);
	case 11:
		return !(primes[n / 30] & 4);
	case 13:
		return !(primes[n / 30] & 8);
	case 17:
		return !(primes[n / 30] & 16);
	case 19:
		return !(primes[n / 30] & 32);
	case 23:
		return !(primes[n / 30] & 64);
	case 29:
		return !(primes[n / 30] & 128);
	}
	return FALSE;
}

int isPrime(int n) {
	if (n < 10) {
		if (n < 2)
			return FALSE;
		if (n < 4)
			return TRUE;
		if (!(n & 1))
			return FALSE;
		if (n < 9)
			return TRUE;
		return FALSE;
	}
	if (!(n & 1))
		return FALSE;
	if (!(n % 3))
		return FALSE;
	if (!(n % 5))
		return FALSE;
	int f = 7;
	while (f * f <= n) {
		if (!(n % f))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 6)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		f += 6;
	}
	return TRUE;
}

int isPrime_uns64(uns64 n) {
	if (n < 10) {
		if (n < 2)
			return FALSE;
		if (n < 4)
			return TRUE;
		if (!(n & 1))
			return FALSE;
		if (n < 9)
			return TRUE;
		return FALSE;
	}
	if (!(n & 1))
		return FALSE;
	if (!(n % 3))
		return FALSE;
	if (!(n % 5))
		return FALSE;
	uns64 f = 7;
	while (f * f <= n) {
		if (!(n % f))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		if (!(n % (f += 4)))
			return FALSE;
		if (!(n % (f += 6)))
			return FALSE;
		if (!(n % (f += 2)))
			return FALSE;
		f += 6;
	}
	return TRUE;
}
