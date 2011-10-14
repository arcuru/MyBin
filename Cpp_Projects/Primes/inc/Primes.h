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
	
	protected:
		uint8_t* SieveOfEratosthenes(int N) const;
		int* SE_List(int N, const uint8_t* prime) const;

		uint8_t* SieveOfSundarem(int N) const;
		int* SS_List(int N, const uint8_t* primes) const;

	private:
		int maxVal;
		int maxList;
		int* pList;
		uint8_t* pSieve;
};

#endif /* PRIMES_H */
