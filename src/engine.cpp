#include "engine.h"
#include "wire.h"

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
  this -> set_pow(0);
  this -> stage = 0;
}

double Engine::get_pow()
{ // no point locking for reading purposes.
  return this -> pow;
}

void Engine::set_pow(double pow)
{
  engine_lock.lock();
  this -> pow = pow;
  engine_lock.unlock();
}

void Engine::duty(long ts)
{
  // TODO: adapt stages so that their chain spins engine
  if(0 == this -> stage)
  {
    wire_turn_off(this -> pin3);
  }
  if(1 == this -> stage)
  {
    wire_turn_on(this -> pin1);
  }
  if(2 == this -> stage)
  {
    wire_turn_off(this -> pin1);
  }
  if(3 == this -> stage)
  {
    wire_turn_on(this -> pin2);
  }
  if(4 == this -> stage)
  {
    wire_turn_off(this -> pin2);
  }
  if(5 == this -> stage)
  {
    wire_turn_on(this -> pin3);
  }
  this -> stage = (this -> stage + 1) % STAGES;
}
