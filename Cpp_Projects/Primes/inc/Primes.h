#ifndef PRIMES_H
#define PRIMES_H

#include <cstdint>

class Primes
{
	public:
		Primes();
		Primes(int n);
		~Primes();
		bool isPrime(int n) const;
		int* getList(int end = -1);

	private:
		int maxVal;
		int maxList;
		int* pList;
		uint8_t* pSieve;
};

#endif /* PRIMES_H */
