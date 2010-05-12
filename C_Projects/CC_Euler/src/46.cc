#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_46()
{
	int number=2000000;
	int count=1;
	int candidate=1;
	int list[200000];
	list[0]=2;
	while ( candidate < number )
	{
		if ( isPrime(candidate) == 1 )
		{
			list[count]=candidate;
			count++;
		}
		candidate+=2;
	}
	count--;
	int check;
	int num=9;
	while ( list[count] > num )
	{
		if ( isPrime(num) == 1 )
		{
			num+=2;
			continue;
		}
		check=0;
		int truth=1;
		while ( list[check] < num )
		{
			int pot=num-list[check];
			int square=0;
			while ( square*square*2 <= pot )
			{
				if ( (square*square*2) == pot )
				{
					truth=0;
					break;
				}
				square++;
			}
			if ( truth == 0 )
			{
				break;
			}
			check++;
		}
		if ( truth == 1 )
		{
			return (int64)num;
		}
		num+=2;
	}
	return 0;
}
