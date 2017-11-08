#include <time.h>
#include <timing.hpp>

#define NANO_SIZE 1000000000

void modulate(long nanoseconds)
{
  struct timespec t1, t2;
  t1.tv_sec = nanoseconds / NANO_SIZE;
  t1.tv_nsec = nanoseconds % NANO_SIZE;
  while(nanosleep(&t1, &t2))
  { // sleep not finished
    t1 = t2;
  }
}
