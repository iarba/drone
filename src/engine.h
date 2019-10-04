#ifndef ENGINE_H
#define ENGINE_H

#include <mutex>

using namespace std;

class Engine{
  public:
  Engine(int pin1, int pin2, int pin3, int id);
  ~Engine();
  void reset();
  double get_pow();
  void set_pow(double pow);
  void duty(long ts);
  private:
  mutex engine_lock;
  double pow;
  int pin1;
  int pin2;
  int pin3;
  int id;
  int stage;
};

#endif
