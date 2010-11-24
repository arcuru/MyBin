def Euler_5(num=20):
	'''Find the smallest integer evenly divisible by all numbers up to the input
	'''
	factor_list = []
	for x in range(1,num+1):
		for i in factor_list:
			if x % i == 0:
				x //= i
		if x != 1:
			factor_list.append(x)
	total = 1
	for x in factor_list:
		total *= x
	return total

if __name__ == '__main__':
	print(Euler_5())
