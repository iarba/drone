#include <manipulator.hpp>
#include <main.hpp>

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
  if(c == 0x04) // ctrl + D - panic
  {
    panic();
    return;
  }
  if(c == 0x1B) // esc - terminate
  {
    terminate_main();
    return;
  }
  manipulator_lock.lock();
  printf("got %c or %hhX \n", c, c);
  manipulator_lock.unlock();
}
