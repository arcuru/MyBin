#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_47()
{
	int num=2000000;
	int count=1;
	int candidate=1;
	int list[200000];
	list[0]=2;
	while ( candidate < num )
	{
		if ( isPrime(candidate) == 1 )
		{
			list[count]=candidate;
			count++;
		}
		candidate+=2;
	}
	count--;
	int anslist[200000];
	int jim=0;
	int counter;
	for (counter=1; counter <= num; counter++)
	{
		int index=0;
		int value=counter;
		int crazy=0;
		while ( value >= 2 )
		{
			int check=0;
			while ( list[check] <= value )
			{
				int tmp=list[check];
				if ( value%tmp == 0 )
				{
					if ( crazy == tmp )
					{
						value=value/tmp;
						check--;
					}
					else
					{
						value=value/tmp;
						index++;
						crazy=tmp;
						check--;
					}
				}
				check++;
			}
		}

		if ( index == 4 )
		{
			anslist[jim]=counter;
			jim++;
		}
		if ( jim >= 4 )
		{
			if ( anslist[jim-4] == (counter-3) )
			{
				return (int64)(counter-3);
			}
		}
	}
	return 0;
}
