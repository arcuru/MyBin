from primes import Primes
def Euler_10(top=2*10**6):
	''' Returns the sum of all primes below the input
	'''
	return sum(Primes().pList(top))

if __name__ == '__main__':
	print(Euler_10())
