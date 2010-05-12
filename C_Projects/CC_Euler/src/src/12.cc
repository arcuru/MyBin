#include "CC_Euler.h"

int64 Euler_12()
{
  int tri=0;
  int divisors=0;
  int count=1;
  while ( divisors < 251 )
    {
      tri=tri+count;
      divisors=0;
      int index = 1;
      while ( index*index < tri )
	{
	  if ( tri%index == 0 )
	    {
	      divisors++;
	    }
	  index++;
	}
      count++;
    }
  return (int64)tri;
}
