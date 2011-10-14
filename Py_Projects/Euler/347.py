def Euler_347(top=10**7):
	'''Find S(top) where S(N) = sum of all M(p,q,N) where M(p,q,N) is the highest number <=N 
		where the only prime factors are p and q
	'''
	top += 1
	a = [0]*top
	b = [0]*top
	for x in range(2, top//2 + 1):
		#print(x)
		if a[x] != 0:
			continue
		for y in range(x*2, top, x):
			if -1 == a[y]:
				continue
			if 0 == a[y]:
				a[y] = x
			elif 0 == b[y]:
				b[y] = x
			else: # Both are filled
				a[y] = -1
	
	total = 0
	for x in range(top-1, 2, -1):
		if a[x] < 2:
			continue
		if b[x] < 2:
			continue
		total += x
		#print(x, a[x], b[x])
		tmp = a[x] * b[x] * -1
		for y in range(x, 2, tmp):
			a[y] = -1
	return total


if __name__ == '__main__':
	print(Euler_347())
