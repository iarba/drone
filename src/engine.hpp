#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <mutex>
#include <thread>

using namespace std;

class Engine{
  public:
  Engine(int pin1, int pin2, int pin3, int id);
  ~Engine();
  double get_mod_pow(); // the width of the modulation, in % of available power.
  double get_mod_freq(); // the frequency of the modulation, in hz.
  void set_mod(double pow, double freq); // set new details. negative ignored.
  Engine *start();
  void stop();
  thread *stop_nb(); // nonblocking stop, useful when stopping all engines.
  private:
  void duty();
  mutex engine_lock;
  double fresh_pow;
  double fresh_freq;
  int pin1;
  int pin2;
  int pin3;
  int id;
  thread *engine_thread;
  mutex kill_lock;
};

#endif
