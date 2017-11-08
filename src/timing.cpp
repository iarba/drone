#include <time.h>
#include <timing.hpp>
#include <constant.hpp>

void safe_sleep(long nanoseconds)
{
  struct timespec t1, t2;
  t1.tv_sec = nanoseconds / NU_IN_U;
  t1.tv_nsec = nanoseconds % NU_IN_U;
  while(nanosleep(&t1, &t2))
  { // sleep not finished
    t1 = t2;
  }
}
