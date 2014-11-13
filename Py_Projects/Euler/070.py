def Euler_70(top=10**7):
	''' Returns the value for which phi(n) is a permutation of n and
		n/phi(n) produces a minimum in the range 1<n<top
	'''
	from numbertheory import phi
	phiList = phi(top)
	minN = 0
	minVal = top
	for x in range(2, top):
		if x/phiList[x] < minVal and sorted(str(x)) == sorted(str(phiList[x])):
			minN = x
			minVal = x/phiList[x]
	return minN

if __name__ == '__main__':
	print(Euler_70())
