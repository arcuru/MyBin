def Euler_173(top=10**6):
	''' Returns the number of ways to make a square shape with
		a square hole with no more than the input blocks
	'''
	# Each successive layer is another 4*(n+1) where n = smaller side length
	count = 0
	# Loop through each size hole
	for n in range(1,top//4):
		blocks = 4*(n+1)
		nn = n+2
		# Add layers and count each one
		while blocks <= top:
			count += 1
			blocks += 4*(nn+1)
			nn += 2
	return count

if __name__ == '__main__':
	print(Euler_173())

