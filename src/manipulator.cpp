#include "manipulator.h"
#include "constants.h"
#include <cstdio>
#include <chrono>
#include <thread>

#define fl 0
#define fr 1
#define bl 2
#define br 3

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

Manipulator::Manipulator()
{
  this -> engines[fl] = new Engine(E1P1, E1P2, E1P3, fl); // front left
  this -> engines[fr] = new Engine(E2P1, E2P2, E2P3, fr); // front right
  this -> engines[bl] = new Engine(E3P1, E3P2, E3P3, bl); // back left
  this -> engines[br] = new Engine(E4P1, E4P2, E4P3, br); // back right
}

Manipulator::~Manipulator()
{
  for(int i = 0; i < N_ENGINES; i++)
  {
    delete this -> engines[i];
  }
}

void Manipulator::panic()
{
  // intentionally no lock protection, it's an emergency after all
  printf("Oh no...\n");
  exit(0);
}

void Manipulator::start()
{
  this -> engines[0] -> set_rot(10000); // DEBUG
  for(int ts = 0; true; ts++)
  {
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    this -> loop(ts);
  }
}

void Manipulator::loop(int ts)
{
  // TODO: probe sensors
  // TODO: process feedback
  // TODO: alter internal representation
  // TODO: adapt engines to fit internal representation
  for(int i = 0; i < N_ENGINES; i++)
  {
    this -> engines[i] -> duty(ts);
  }
}
