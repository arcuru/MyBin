def phi(n):
	''' Returns a list of Euler's totient values
		The index of the list is n, the value is phi(n)
	'''
	phiList = [x-1 if x%2==1 else x//2 for x in range(0,n+1)]
	phiList[1] = 1
	for x in range(3, n+1, 2):
		if phiList[x] == x-1:
			for s in range(2*x, n+1, x):
				phiList[s] -= phiList[s] // x
	return phiList
