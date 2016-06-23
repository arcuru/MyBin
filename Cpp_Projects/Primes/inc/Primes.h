#ifndef PRIMES_H
#define PRIMES_H

#include <cstdint>
#include <vector>

class Primes
{
	public:
		Primes();
		Primes(int64_t n);
		~Primes();
		bool isPrime(int64_t n) const;
		std::vector<int64_t> getList(int64_t end = -1);
		int64_t pi(int64_t n = -1);

	protected:
		std::vector<uint8_t> SieveOfEratosthenes(int64_t N) const;
		std::vector<int64_t> SE_List(int64_t N, const std::vector<uint8_t> prime) const;

		//uint8_t* SieveOfSundarem(int N) const;
		//int* SS_List(int N, const uint8_t* primes) const;

	private:
		int64_t maxVal;
		int64_t maxList;
		std::vector<int64_t> pList;
		std::vector<uint8_t> pSieve;
};

#endif /* PRIMES_H */
