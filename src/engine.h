#ifndef ENGINE_H
#define ENGINE_H

#include <mutex>

using namespace std;

class Engine{
  public:
  Engine(int pin1, int pin2, int pin3, int id);
  ~Engine();
  void reset();
  long get_rot();
  void set_rot(long rot);
  void duty(long ts);
  private:
  mutex engine_lock;
  long rot;
  long last_point;
  int pin1;
  int pin2;
  int pin3;
  int id;
  int stage;
};

#endif
