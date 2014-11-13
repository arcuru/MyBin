def Euler_6(top=100):
	'''Finds the difference between the sum of the squares and the square of the sums
		for numbers from 1 to the input
	'''
	(sum_sq, sq_sum) = (0, 0)
	for x in range(top+1):
		(sum_sq, sq_sum) = (sum_sq + x ** 2, sq_sum + x)
	return (sq_sum ** 2) - sum_sq

if __name__ == '__main__':
	print(Euler_6())
