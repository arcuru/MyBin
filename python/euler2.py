import sys
a=1
while a < 1000:
	b=a
	c=1000-b-a
	while c>b:
		if a*a+b*b==c*c:
			print a,b,c
			sys.exit()
		b+=1
		c=1000-b-a
	a+=1