from multiprocessing import Pool,Pipe

p_conn, c_conn = Pipe()

def f(a):
	a2 = a**2
	limit = 1000
	for b in range(a,limit):
		ab2 = a2 + b**2
		c2 = (limit-a-b)**2
		if ab2 > c2:
			break
		elif ab2 == c2:
			c_conn.send(a*b*(limit-a-b))
			c_conn.close()

if __name__ == '__main__':
	pool = Pool(processes=4)
	result = pool.map_async(f, range(1,1000))
	out = p_conn.recv()
	pool.terminate()
	print(out)
