#ifndef PRIMES_H
#define PRIMES_H

class Primes
{
	public:
		Primes();
		Primes(int n);
		~Primes();
		void init(int n);
		bool isPrime(int n);
		int* getList(int end = -1);

	private:
		int maxVal;
		int maxList;
		int* pList;
		unsigned char* pSieve;
};

#endif /* PRIMES_H */
