def Euler_104():
	'''Find the index of the first Fibonacci number with first and last 9 digits pandigital
	'''
	# a is lower fib number, b is higher fib number
	# index is the fibonacci index of b

	(a, b, index) = ([1, 1], [1, 1], 2)
	while True:
		(a, b, index) = (b, [a[0]+b[0], a[1]+b[1]], index + 1)

		# Modify the numbers to track just the low and high digits
		if b[0] > 10**9:
			b[0] %= 10**9
		while b[1] > 10**20:
			b[1] //= 10
			a[1] //= 10

		if not is_Pandigital(b[0]):
			continue

		if is_Pandigital(int(str(b[1])[:9])):
			return index

pan_set = set(map(str, range(1,10)))

def is_Pandigital(number):
	'''Return true if a number is pandital (contains 1-9 exactly once)
		False otherwise
	'''
	if number < 10 ** 8 or number >= 10 ** 9:
		return False
	return set(str(number)) == pan_set

if __name__ == '__main__':
	print(Euler_104())

