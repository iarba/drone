#include <manipulator.hpp>
#include <main.hpp>
#include <event.hpp>
#include <constant.hpp>
#include <iostream>
#include <sstream>

/* Layout:
 *
 * *--------------*
 * |E0<   /\   >E1|
 * |              |
 * |              |
 * |              |
 * |              |
 * |              |
 * |E2>        <E3|
 * *--------------*
 *
 */

Manipulator::Manipulator(Engine **engines)
{
  this -> fl = engines[0] -> start(); // front left
  this -> fr = engines[1] -> start(); // front right
  this -> bl = engines[2] -> start(); // back left
  this -> br = engines[3] -> start(); // back right
  this -> selector = -1;
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
  switch(c)
  {
    /* pitch control */
    case 'w':
      return pitch_m();
    case 's':
      return pitch_p();
    /* roll control */
    case 'a':
      return roll_m();
    case 'd':
      return roll_p();
    /* yaw control */
    case 'q':
      return yaw_m();
    case 'e':
      return yaw_p();
    /* power control */
    case ',':
      return pow_m(selector);
    case '.':
      return pow_p(selector);
    case '1':
    case '2':
    case '3':
    case '4':
      manipulator_lock.lock();
      selector = (int)(c - '1');
      manipulator_lock.unlock();
      return;
    case '`':
      manipulator_lock.lock();
      selector = -1;
      manipulator_lock.unlock();
      return;
  }
  stringstream ss;
  ss<< hex << c;
  (new Event(E_INPUT_UNK))
    -> with_message("got unidentified keypress [" + ss.str() +"]")
    -> dispatch();
}

void Manipulator::pitch_m()
{
  pow_m(0);
  pow_m(1);
  pow_p(2);
  pow_p(3);
}

void Manipulator::pitch_p()
{
  pow_p(0);
  pow_p(1);
  pow_m(2);
  pow_m(3);
}

void Manipulator::roll_m()
{
  pow_p(0);
  pow_m(1);
  pow_p(2);
  pow_m(3);
}

void Manipulator::roll_p()
{
  pow_m(0);
  pow_p(1);
  pow_m(2);
  pow_p(3);
}

void Manipulator::yaw_m()
{
  pow_m(0);
  pow_p(1);
  pow_p(2);
  pow_m(3);
}

void Manipulator::yaw_p()
{
  pow_p(0);
  pow_m(1);
  pow_m(2);
  pow_p(3);
}

void Manipulator::pow_m(int sel)
{
  if(sel == -1)
  {
    pow_m(0);
    pow_m(1);
    pow_m(2);
    pow_m(3);
    return;
  }
  Engine *e = select_engine(sel);
  e -> set_mod(
       e -> get_mod_pow() / POW_RATE,
       (e -> get_mod_freq() - FREQ_FLAT) / FREQ_RATE
  );
}

void Manipulator::pow_p(int sel)
{
  if(sel == -1)
  {
    pow_p(0);
    pow_p(1);
    pow_p(2);
    pow_p(3);
    return;
  }
  Engine *e = select_engine(sel);
  e -> set_mod(
       e -> get_mod_pow() * POW_RATE, 
       e -> get_mod_freq() * FREQ_RATE + FREQ_FLAT
  );
}

Engine *Manipulator::select_engine(int sel)
{
  switch (sel)
  {
    case 0:
      return fl;
    case 1:
      return fr;
    case 2:
      return bl;
    case 3:
      return br;
    default:
      return NULL;
  }
}
