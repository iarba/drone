#include "engine.h"
#include "wire.h"
#include <cstdio>
#include "constants.h"

#define STAGES 6

Engine::Engine(int pin1, int pin2, int pin3, int id)
{
  this -> pin1 = pin1;
  this -> pin2 = pin2;
  this -> pin3 = pin3;
  wire_init(pin1);
  wire_init(pin2);
  wire_init(pin3);
  this -> reset();
  this -> id = id;
}

Engine::~Engine()
{
  reset();
}

void Engine::reset()
{
  wire_turn_off(this -> pin1);
  wire_turn_off(this -> pin2);
  wire_turn_off(this -> pin3);
  this -> set_rot(ROT_THRESHOLD + 1);
  this -> stage = 0;
}

long Engine::get_rot()
{ // no point locking for reading purposes.
  return this -> rot;
}

void Engine::set_rot(long rot)
{
  engine_lock.lock();
  this -> rot = rot;
  engine_lock.unlock();
}

/* This function is called very frequently, every 10 microseconds
 * To achieve the desired rotation duration {3 * (pup + pdown) * slice = rot}
 * Thus, slice = rot / (3 * (pup + pdown))
 * The time allocated for 1 up stage is stage * pup
 * The time allocated for 1 down stage is stage * pdown
 */
void Engine::duty(long ts)
{
  if(this -> rot > ROT_THRESHOLD) // 1 second
  { // unreasonably slow
    this -> last_point = ts;
    return;
  }
  engine_lock.lock();
  long slice = this -> rot / (3 * (P_UP + P_DOWN));
  engine_lock.unlock();
  if((0 == this -> stage) && (ts - this -> last_point > slice * P_DOWN))
  {
    wire_turn_off(this -> pin3);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
  }
  if((1 == this -> stage) && (ts - this -> last_point > slice * P_UP))
  {
    wire_turn_on(this -> pin1);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
  }
  if((2 == this -> stage) && (ts - this -> last_point > slice * P_DOWN))
  {
    wire_turn_off(this -> pin1);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
  }
  if((3 == this -> stage) && (ts - this -> last_point > slice * P_UP))
  {
    wire_turn_on(this -> pin2);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
  }
  if((4 == this -> stage) && (ts - this -> last_point > slice * P_DOWN))
  {
    wire_turn_off(this -> pin2);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
  }
  if((5 == this -> stage) && (ts - this -> last_point > slice * P_UP))
  {
    wire_turn_on(this -> pin3);
    this -> last_point = ts;
    this -> stage = (this -> stage + 1) % STAGES;
    printf("[%ld, %ld] stage reset\n", ts, this -> rot);
  }
}
