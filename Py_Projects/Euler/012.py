def Euler_12(divisors=500):
	'''First triangle number to have over input number of divisors
	'''
	tri=0
	for x in range(1000000):
		tri = tri + x
		count = 2
		root = 2
		while root * root <= tri:
			if tri % root == 0:
				count += 2
			if root * root == tri:
				count -= 1
			root += 1
		if count > divisors:
			return tri

	raise ValueError('range too small')


if __name__ == '__main__':
	print(Euler_12())
