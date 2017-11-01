#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <mutex>
#include <engine.hpp>

#define POW_RATE 1.04
#define FREQ_RATE 1.06
#define FREQ_FLAT 5
using namespace std;

/* Manipulator
 * 
 * Used as a middle-ground between input and engine control.
 * Receives and maintains information from various sensors.
 * Controls engines according to internal representation
 */

class Manipulator{
  public:
  Manipulator(Engine **engines);
  ~Manipulator();
  void panic(); // to be called in times of trouble
  void feed_raw(char c);
  /* public, but handle with care */
  void pitch_m();
  void pitch_p();
  void roll_m();
  void roll_p();
  void yaw_m();
  void yaw_p();
  void pow_m(int sel);
  void pow_p(int sel);
  private:
  Engine *select_engine(int sel);
  mutex manipulator_lock;
  Engine *fl; // front left
  Engine *fr; // front right
  Engine *bl; // back left
  Engine *br; // back right
  int selector;
};

#endif
