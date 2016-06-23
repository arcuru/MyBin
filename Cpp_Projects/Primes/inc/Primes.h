#ifndef PRIMES_H
#define PRIMES_H

#include <cstdint>
#include <vector>

class Primes
{
	public:
		Primes();
		Primes(int n);
		~Primes();
		bool isPrime(int n) const;
		std::vector<int> getList(int end = -1);
		int pi(int n = -1);

	protected:
		std::vector<uint8_t> SieveOfEratosthenes(int N) const;
		std::vector<int> SE_List(int N, const std::vector<uint8_t> prime) const;

		//uint8_t* SieveOfSundarem(int N) const;
		//int* SS_List(int N, const uint8_t* primes) const;

	private:
		int maxVal;
		int maxList;
		std::vector<int> pList;
		std::vector<uint8_t> pSieve;
};

#endif /* PRIMES_H */
