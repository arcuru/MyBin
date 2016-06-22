#include "Primes.h"
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <vector>

#define NDEBUG
#ifdef DEBUG
#include <iostream>
#endif

Primes::Primes()
{
	maxVal = maxList = 0;
	pSieve = nullptr;
}

Primes::Primes(int n)
{
	pSieve = SieveOfEratosthenes(n);
	maxVal = n;
	maxList = 0;
}

Primes::~Primes()
{
	free(pSieve);
}

bool Primes::isPrime(int n) const
{
	if (n < 10) {
		if (n < 2)
			return false;
		if (n < 4)
			return true;
		if (!(n & 1))
			return false;
		if (n < 9)
			return true;
		return false;
	}
	if (!(n & 1))
		return false;
	if (!(n % 3))
		return false;
	if (!(n % 5))
		return false;
	if ( n < maxVal && pSieve != nullptr ) {
		switch (n % 30) {
			case 1:
				return !(pSieve[n / 30] & 0x01);
			case 7:
				return !(pSieve[n / 30] & 0x02);
			case 11:
				return !(pSieve[n / 30] & 0x04);
			case 13:
				return !(pSieve[n / 30] & 0x08);
			case 17:
				return !(pSieve[n / 30] & 0x10);
			case 19:
				return !(pSieve[n / 30] & 0x20);
			case 23:
				return !(pSieve[n / 30] & 0x40);
			case 29:
				return !(pSieve[n / 30] & 0x80);
			}
	}
	int f = 7;
	while (f * f <= n) {
		if (!(n % f))
			return false;
		if (!(n % (f += 4)))
			return false;
		if (!(n % (f += 2)))
			return false;
		if (!(n % (f += 4)))
			return false;
		if (!(n % (f += 2)))
			return false;
		if (!(n % (f += 4)))
			return false;
		if (!(n % (f += 6)))
			return false;
		if (!(n % (f += 2)))
			return false;
		f += 6;
	}
	return true;
}

std::vector<int> Primes::getList(int end)
{
	if (-1 == end)
		end = maxVal;
	if (end <= maxList)
		return pList;
	// Need to add error checking for if end is too high
	//else if (end > maxVal)
	//	return nullptr;
	pList = SE_List(end, pSieve);
	maxList = end;
	return pList;
}

inline void mark(int *mod, int *n, uint8_t* primes)
{
	if(*mod>30) {
		(*mod)-=30;
		(*n)+=1;
	}
	switch(*mod) {
		case 1:		primes[*n] |= 0x01;	break;
		case 7:		primes[*n] |= 0x02;	break;
		case 11:	primes[*n] |= 0x04;	break;
		case 13:	primes[*n] |= 0x08;	break;
		case 17:	primes[*n] |= 0x10;	break;
		case 19:	primes[*n] |= 0x20;	break;
		case 23:	primes[*n] |= 0x40;	break;
		case 29:	primes[*n] |= 0x80;	break;
	}
}

uint8_t* Primes::SieveOfEratosthenes(int N) const
{
	int SQRTN = (int) sqrt(N);
	int sqrtEnd = (SQRTN / 30) + 1;
	int primeEnd = (N / 30) + 1;
	uint8_t* primes = (uint8_t*) calloc(primeEnd + 1, sizeof(uint8_t));
	if (!primes) {
#ifdef DEBUG
		std::cout << "Could not allocate " << primeEnd+1 << " bytes." << std::endl;
#endif
		return nullptr;
	}
	int n, s, num, num1, num2, num4, num6;
	int mod = 0, mod2 = 0, mod22 = 0, mod23 = 0;
	int incr2, incr4, incr6, s30;
	uint8_t k;
	primes[0] |= 1;
	for (n = 0, num1 = 0; n <= sqrtEnd; num1 += 30, n++) {
		for (k = 1; k; k += k) {
			if (!(primes[n] & k)) {
				num = num1;
				switch (k) {//mod=(num^2)%30; mod2=(num*2)%30; mod22=(mod2*2)%30;
				case 0x01:
					mod = 1;
					mod2 = 2;
					mod22 = 4;
					mod23 = 6;
					num += 1;
					break;
				case 0x02:
					mod = 19;
					mod2 = 14;
					mod22 = 28;
					mod23 = 12;
					num += 7;
					break;
				case 0x04:
					mod = 1;
					mod2 = 22;
					mod22 = 14;
					mod23 = 6;
					num += 11;
					break;
				case 0x08:
					mod = 19;
					mod2 = 26;
					mod22 = 22;
					mod23 = 18;
					num += 13;
					break;
				case 0x10:
					mod = 19;
					mod2 = 4;
					mod22 = 8;
					mod23 = 12;
					num += 17;
					break;
				case 0x20:
					mod = 1;
					mod2 = 8;
					mod22 = 16;
					mod23 = 24;
					num += 19;
					break;
				case 0x40:
					mod = 19;
					mod2 = 16;
					mod22 = 2;
					mod23 = 18;
					num += 23;
					break;
				case 0x80:
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
				switch (k)do {
					case 0x01: mark(&mod,&s30,primes); s+=num6;
					if (s>=N) break;
					s30+=incr6; mod+=mod23;
					case 0x02: mark(&mod,&s30,primes); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 0x04: mark(&mod,&s30,primes); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
					case 0x08: mark(&mod,&s30,primes); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 0x10: mark(&mod,&s30,primes); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
					case 0x20: mark(&mod,&s30,primes); s+=num4;
					if (s>=N) break;
					s30+=incr4; mod+=mod22;
					case 0x40: mark(&mod,&s30,primes); s+=num6;
					if (s>=N) break;
					s30+=incr6; mod+=mod23;
					case 0x80: mark(&mod,&s30,primes); s+=num2;
					if (s>=N) break;
					s30+=incr2; mod+=mod2;
				}while(1);
			}
		}
	}
	return primes;
}

//Returns vector filled with primes from 2 to N
//Index 0 starts off with 2
#define pLhelp(x)	if (x>N) break; list.push_back(x); break;
std::vector<int> Primes::SE_List(int N, const uint8_t* prime) const
{
	int primeEnd = (N / 30) + 1;
	int n;
	uint8_t s;

	std::vector<int> list({2,3,5});

	// Reserve an approximate length
	// This is a formula for the upper bound of pi(x)
	int upper = (N/log(N))*(1 + (1.2762/log(N)));
	list.reserve(upper);

	for (n = 0; n < primeEnd; n++) {
		for (s = 1; s; s += s) {
			if (!(prime[n] & s)) {
				switch (s) {
				case 0x01:
					pLhelp(n*30+1)
				case 0x02:
					pLhelp(n*30+7)
				case 0x04:
					pLhelp(n*30+11)
				case 0x08:
					pLhelp(n*30+13)
				case 0x10:
					pLhelp(n*30+17)
				case 0x20:
					pLhelp(n*30+19)
				case 0x40:
					pLhelp(n*30+23)
				case 0x80:
					pLhelp(n*30+29)
				}
			}
		}
	}
	return list;
}

/*
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
	static unsigned char* saved_list = nullptr;
	static int current_byte = 0, current_bitval = 0, last_prime = 0;
	static char current_bit = 1;
	if (list != nullptr) {
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
		return nullptr;
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
*/

uint8_t* Primes::SieveOfSundarem(int N) const
{
	// i+j+2ij marked off as 1<=i<=j and i+j+2ij<=n, k are numbers left, 2k+1 are prime
	int n = N/2;
	uint8_t* primes = (uint8_t*) calloc(n+1, sizeof(uint8_t));
	int tmp;
	for (int i = 1; i < n/4; i++) {
		for (int j = i; j <= (n-i)/(2*i+1); j++) {
			tmp = i + j + 2*(i * j);
			if (tmp > n)
				break;
			primes[tmp] = 1;
		}
	}
	return primes;
}

int* Primes::SS_List(int N, const uint8_t* primes) const
{
	int n = N/2;
	int top = 1;
	for (int i = 0; i < n; i++) {
		if (0 == primes[i])
			top++;
	}
	int* list = (int*) malloc((top+1) * sizeof(int));
	if (!list) {
		return nullptr;
	}
	int current = 0;
	list[current++] = 2;
	for (int k = 1; k < n; k++) {
		if (0 == primes[k])
			list[current++] = 2*k + 1;
	}
	list[current] = 0;
	return list;
}
