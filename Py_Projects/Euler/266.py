from primes import Primes
from functools import reduce
def Euler_266(primeMax=190, cut=10**16):
	''' Returns the PSR mod input for the number consisting of all the primes
			below the input
	'''
	def prod(ll):
		return reduce(lambda i,j: i*j, ll)

	primeList = Primes(primeMax).pList()
	listA, listB = [], []
	for x in range(0,len(primeList),2):
		listA.append(primeList[x])
	for x in range(1,len(primeList),2):
		listB.append(primeList[x])
	minDiff = abs(prod(listA) - prod(listB))
	return 0

if __name__ == '__main__':
	print(Euler_266())

