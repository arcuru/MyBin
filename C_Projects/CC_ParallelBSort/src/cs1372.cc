// Helper subroutines for CS1372 bubble sort algorithm
// George F. Riley, Georgia Tech, CS1372


#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void RandomizeArray(int d[], int arraySize)
{
  // Populate with random values
  static bool seeded = false;
  static unsigned long heuristic_sequence = 0;
  if (!seeded)
    { // Seed the random number generator with time of day
      timeval tv;
      gettimeofday(&tv, 0);
      heuristic_sequence++;   // Always make sure different than last time.
      int seed = (tv.tv_sec^tv.tv_usec^(heuristic_sequence << 8)) & 0x7fffffff;
      srand48(seed);
      seeded = true;
    }
  for (int i = 0; i < arraySize; ++i)
    {
      d[i] = (int)(drand48() * 1000.0);
    }
}

int GetMillisecondClock()
{
  timeval tv;
  gettimeofday(&tv, 0);
  static bool first = true;
  static int startSec = 0;
  if (first)
    {
      startSec = tv.tv_sec;
      first = false;
    }
  
  return (tv.tv_sec - startSec) * 1000 + tv.tv_usec / 1000; // Time in milliseconds
}


