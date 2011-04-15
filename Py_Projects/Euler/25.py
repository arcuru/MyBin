def Euler_25(length=1000):
	'''Find the index of the first term in the Fibonacci sequence
	to contain 1000 digits
	'''
	total = 0
	(a, b, count) = (1, 1, 2)
	while True:
		(a, b, count) = (b, a+b, count+1)
		if len(str(b)) >= length:
			return count
	raise Exception

if __name__ == '__main__':
	print(Euler_25())
