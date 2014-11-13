from primes import Primes
def Euler_35(top=10**6):
	''' Returns the number of circular primes below the top
	'''
	def rotate(num):
		return int(str(num)[-1] + str(num)[0:-1])
	count = 0
	primes = Primes(top)
	primes.sieve()
	for val in primes.pList():
		val2 = rotate(val)
		while val2 != val:
			if not primes.isPrime(val2):
				break
			val2 = rotate(val2)
		if val == val2:
			count += 1
	return count

if __name__ == '__main__':
	print(Euler_35())
