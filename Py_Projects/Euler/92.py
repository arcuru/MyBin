def Euler_92(top=10**7):
	''' Returns the number of chains under the input that get to 89
	'''
	def step(num):
		n = 0
		while num > 0:
			n += (num % 10)**2
			num //= 10
		return n
		return sum([int(x)**2 for x in str(num)])
	anslist = [False for i in range(0, len(str(top)) * 9**2)]
	for ind in range(1, len(str(top)) * 9**2):
		x = ind
		while True:
			x = step(x)
			if x is 89:
				anslist[ind] = True
				break
			if x is 1:
				break
	count = 0
	for x in range(1, top):
		if anslist[step(x)]:
			count += 1
	return count

if __name__ == '__main__':
	print(Euler_92())
