def Euler_1(top=1000):
	'''Find the sum of all the multiples of 3 or 5 below the input
	'''
	total = 0
	for x in range(top):
		if x % 5 == 0 or x % 3 == 0:
			total += x
	return total

if __name__ == '__main__':
	print(Euler_1())
