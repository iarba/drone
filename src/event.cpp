#include <main.hpp>
#include <event.hpp>

using namespace std;

Event::Event(int type)
{
  this -> type = type;
}

Event *Event::with_id(int id)
{
  this -> id = id;
  return this;
}

Event *Event::with_power(double p)
{
  this -> power = to_string(p);
  return this;
}

Event *Event::with_freq(double f)
{
  this -> freq = to_string(f);
  return this;
}

Event *Event::with_message(char *c)
{
  this -> msg = string(c);
  return this;
}

Event *Event::with_message(string m)
{
  this -> msg = m;
  return this;
}

void Event::dispatch()
{
  ui -> react(this);
}
