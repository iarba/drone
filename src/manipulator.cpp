#include <manipulator.hpp>
#include <main.hpp>

/* Layout:
 *
 * *--------------*
 * |E0    /\    E1|
 * |              |
 * |              |
 * |              |
 * |              |
 * |              |
 * |E2          E3|
 * *--------------*
 *
 */

Manipulator::Manipulator(Engine **engines)
{
  this -> fl = engines[0] -> start(); // front left
  this -> fr = engines[1] -> start(); // front right
  this -> bl = engines[2] -> start(); // back left
  this -> br = engines[3] -> start(); // back right
}

Manipulator::~Manipulator()
{
  thread *tfl = fl -> stop_nb();
  thread *tfr = fr -> stop_nb();
  thread *tbl = bl -> stop_nb();
  thread *tbr = br -> stop_nb();
  tfl -> join();
  tfr -> join();
  tbl -> join();
  tbr -> join();
  delete tfl;
  delete tfr;
  delete tbl;
  delete tbr;
}

void Manipulator::panic()
{
  // intentionally no lock protection, it's an emergency after all
  printf("Oh no...\n");
  exit(0);
}

void Manipulator::feed_raw(char c)
{
  if(c == 0x04) // ctrl + D -> panic
  {
    panic();
    return;
  }
  if(c == 0x1B) // esc -> terminate
  {
    terminate_main();
    return;
  }
  manipulator_lock.lock();
  printf("got %c or %hhX \n", c, c);
  manipulator_lock.unlock();
}
