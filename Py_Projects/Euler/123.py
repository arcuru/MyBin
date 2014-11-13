from gmpy2 import mpz
from primes import Primes
def Euler_123(low = 10**10):
	''' Returns the nth prime that has a remainder above low when using
			the given formula
	'''
	p = Primes(10**6)
	primes = p.pList()
	for x in range(0,len(primes)):
		n = mpz(x+1)
		p = mpz(primes[x]-1)**n + mpz(primes[x]+1)**n
		if p % mpz(primes[x])**2 > low:
			return n

if __name__ == '__main__':
	print(Euler_123())

