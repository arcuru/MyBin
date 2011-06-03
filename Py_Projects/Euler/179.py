def Euler_179(top=10**7):
	''' Returns the number of integers from 1<n<input for which
		n and n+1 have the same number of divisors
	'''
	from math import sqrt
	divlist = [2 for x in range(0,top+2)]
	divlist[1] = 1
	for n in range(2,int(sqrt(top))+1):
		divlist[n*n] += 1
		for s in range(n*n+n,top+1,n):
			divlist[s] += 2
	
	count = 0
	for x in range(1,top+1):
		if divlist[x] == divlist[x+1]:
			count += 1
	return count

if __name__ == '__main__':
	print(Euler_179())

