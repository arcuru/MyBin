def Euler_131(top=6*10**3):
	''' Returns the number of primes below the input
		where n**3+p*n**2 is a perfect cube
	'''
	from primes import isPrime
	from primes import Primes
	foo = lambda p,n: n**3 + p * n**2
	def bsearch(l, val, low, high):
		while low <= high:
			mid = (low + high) // 2
			if val < l[mid]:
				high = mid - 1
				continue
			elif val > l[mid]:
				low = mid + 1
				continue
			elif val == l[mid]:
				return True
		return False

	cubelist = [x**3 for x in range(1,top)]
	cubetop = top
	a = Primes(top)
	count = 0
	for p in a.pList(top):
		for n in range(1,top):
			tmp = foo(p,n)
			while tmp > cubelist[-1]:
				cubelist.append(cubetop**3)
				cubetop += 1
			if bsearch(cubelist, tmp, 0, cubetop-1):
				print(p,n,tmp)
				count += 1
				break
	return count

	'''
	# Reduce expression to p = cube/n**2 - n
	count=0
	ans = set()
	p = Primes(top)
	p.sieve()
	for b in range(1,top):
		cube = b**3
		for n in range(b,0,-1):
			tmp = cube // n**2
			if tmp * n**2 != cube:
				continue
			tmp -= n
			if tmp >= top:
				break
			if tmp < top and tmp not in ans and p.isPrime(tmp):
				ans.add(tmp)
				count += 1
	return count
	'''

if __name__ == '__main__':
	print(Euler_131())

