// Helper subroutines for CS1372 bubble sort algorithm
// George F. Riley, Georgia Tech, CS1372


#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int UniformRandom(int minimum, int maximum)
{
  // Choose a uniform random value
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
  double r = drand48();
  return (minimum + r * (maximum - minimum));
}


