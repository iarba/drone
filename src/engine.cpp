#include <engine.hpp>
#include <event.hpp>
#include <timing.hpp>
#include <wiringPi.h>
#include <constant.hpp>

Engine::Engine(int pin1, int pin2, int pin3, int id)
{
  this -> pin1 = pin1;
  this -> pin2 = pin2;
  this -> pin3 = pin3;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  this -> engine_thread = NULL;
  this -> id = id;
  fresh_pow = 10;
  fresh_freq = 0;
  (new Event(E_MOTOR_SET))
    -> with_id(id)
    -> with_power(fresh_pow)
    -> with_freq(fresh_freq)
    -> dispatch();
}

Engine::~Engine()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
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
  if((pow >= 0) && (pow <= 90))
  {
    this -> fresh_pow = pow;
  }
  if((freq >= 0) && (freq <= 500))
  {
    this -> fresh_freq = freq;
  }
  engine_lock.unlock();
  (new Event(E_MOTOR_SET))
    -> with_id(id)
    -> with_power(fresh_pow)
    -> with_freq(fresh_freq)
    -> dispatch();
}

Engine *Engine::start()
{
  if(!engine_thread)
  {
    engine_thread = new thread(&Engine::duty, this);
  }
  return this;
}

void Engine::stop()
{
  kill_lock.lock();
  engine_thread -> join();
  delete engine_thread;
  engine_thread = NULL;
}

thread *Engine::stop_nb()
{
  kill_lock.lock();
  thread *value = engine_thread;
  engine_thread = NULL;
  return value;
}

int Engine::cycle_pin(int last_pin)
{
  if(last_pin == pin1)
  {
    return pin2;
  }
  if(last_pin == pin2)
  {
    return pin3;
  }
  if(last_pin == pin3)
  {
    return pin1;
  }
  /* shouldn't happen, but better be safe */
  return pin1;
}

void Engine::duty()
{
  double active_pow = 10;
  double active_freq = 0;
  long t_time, p_time;
  int next_pin = pin1;
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
    t_time = (long)((double)NU_IN_U / active_freq);
    p_time = (long)((double)t_time * active_pow / 100);
    digitalWrite(next_pin, HIGH);
    safe_sleep(p_time);
    digitalWrite(next_pin, LOW);
    safe_sleep(t_time - p_time);
    next_pin = cycle_pin(next_pin);
  }
}
