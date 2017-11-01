#include <engine.hpp>

Engine::Engine(int pin1, int pin2, int pin3)
{
  this -> pin1 = pin1;
  this -> pin2 = pin2;
  this -> pin3 = pin3;
  this -> engine_thread = NULL;
}

Engine::~Engine()
{
}

double Engine::get_mod_pow()
{
  double value;
  engine_lock.lock();
  value = this -> fresh_pow;
  engine_lock.unlock();
  return value;
}

double Engine::get_mod_freq()
{
  double value;
  engine_lock.lock();
  value = this -> fresh_freq;
  engine_lock.unlock();
  return value;
}

void Engine::set_mod(double pow, double freq)
{
  engine_lock.lock();
  if(pow >= 0)
  {
    this -> fresh_pow = pow;
  }
  if(freq >= 0)
  {
    this -> fresh_freq = freq;
  }
  engine_lock.unlock();
}

void Engine::start()
{
  if(!engine_thread)
  {
    engine_thread = new thread(&Engine::duty, this);
  }
}

void Engine::stop()
{
  kill_lock.lock();
  engine_thread -> join();
  delete engine_thread;
  engine_thread = NULL;
}

void Engine::duty()
{
  double active_pow = 0;
  double active_freq = 0;
  while(kill_lock.try_lock())
  {
    kill_lock.unlock();
    if(engine_lock.try_lock())
    {
      active_pow = fresh_pow;
      active_freq = fresh_freq;
      engine_lock.unlock();
    }
    if(active_freq * active_pow == 0) // What am I supposed to do?
    {
      this_thread::yield();
      continue;
    }
  }
}
