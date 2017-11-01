#include <manipulator.hpp>

Manipulator::Manipulator()
{
}

Manipulator::~Manipulator()
{
}

void Manipulator::panic()
{
  // intentionally no lock protection, it's an emergency after all
  printf("Oh no...");
}

void Manipulator::feed_raw(char c)
{
  if(c == 4) // ctrl + D
  {
    panic();
    return;
  }
  manipulator_lock.lock();
  printf("got %c or %hhX \n", c, c);
  manipulator_lock.unlock();
}
