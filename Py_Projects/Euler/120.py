def Euler_120(bot=3,top=1000):
	''' Returns the sum of the max remainders between bot and top inclusive
		when using the formula (a-1)^n+(a+1)^n % a^2
	'''
	from gmpy2 import mpz
	total = 0
	for x in range(bot,top+1):
		a = mpz(x)
		b = a+1
		c = a-1
		aa = a**2
		bb = b
		cc = c
		maxval = 0
		for n in range(1,2000):
			tmp = (bb + cc) % aa
			if tmp > maxval:
				maxval = tmp
			bb *= b
			cc *= c
		total += maxval

	return total

if __name__ == '__main__':
	print(Euler_120())

