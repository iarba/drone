#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

#define E_MOTOR_SET 1 
#define E_INPUT_UNK 2

using namespace std;

class Event{
  public:
  Event(int type);
  Event *with_id(int id);
  Event *with_power(double p);
  Event *with_freq(double f);
  Event *with_message(char *c);
  Event *with_message(string m);
  void dispatch();
  string power;
  string freq;
  string msg;
  int id;
  int type;
};

#endif
