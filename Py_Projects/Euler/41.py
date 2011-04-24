def Euler_41():
	''' Returns the largest pandigital prime
	'''
	# 8 and 9 digits don't work, since sum is multiple of 3
	from itertools import permutations
	from primes import Primes
	p = Primes()
	for x in sorted([int(''.join(list(x))) for x in permutations('7654321')], reverse=True):
		if p.isPrime(x):
			return x
	raise ValueError

if __name__ == '__main__':
	print(Euler_41())

