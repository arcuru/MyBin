#include "Euler.h"
#include <stdlib.h>

int64_t Euler_341()
{
	int limit = 1000000;
	short* clist = (short*)malloc(sizeof(short)*50000000);
	clist[0]=0; clist[1]=1; clist[2]=2;
	int endlist = 3;
	int total = 0;
	int i = 0;
	int j = 2;
	int jcount = 1;
	int s = 0;
	int64_t base = 1;
	int64_t base3 = base * base * base;
	int64_t n = limit * limit * limit;
	printf("%lld\n",n);
	while (base < limit) {
		i++;
		total += clist[i];
		while (base3 <= total && base3 <= n-1) {
			s += i;
			base++;
			base3 = base * base * base;
		}
		if (i == endlist-1) {
			if (j > 65000) {
				puts("Too big\n");
				printf("%lld\n",base);
				return (int64_t)base;
			}
			clist[i+1]=j;
			jcount++;
			endlist++;
			if (jcount == clist[j]) {
				j++;
				jcount = 0;
			}
		}
	}
	return (int64_t)s;
}
/*
def Euler_341(limit=10**3):
	''' Returns the sum of all the elements of the Golomb sequence
		1 <= n < limit**3
	'''
	clist = [0 for x in range(500000)]
	clist[1]=1
	clist[2]=2
	endlist = 3
	total = 0
	i = 0
	j = 2
	jcount = 1
	s = 0
	base = 1
	base3 = base ** 3
	n = limit ** 3
	while base < limit:
		i += 1
		total += clist[i]
		while base3 <= min(n-1,total):
			s += i
			base += 1
			base3 = base ** 3
		# Add to list if necessary
		if i == endlist-1:
			clist[i+1]=j
			if i%100 == 0:
				print(j)
			jcount += 1
			endlist += 1
			if jcount == clist[j]:
				j += 1
				jcount = 0
	return s

if __name__ == '__main__':
	print(Euler_341())
	*/
