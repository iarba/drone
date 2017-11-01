#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <mutex>
#include <engine.hpp>
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
  private:
  mutex manipulator_lock;
  Engine *fl; // front left
  Engine *fr; // front right
  Engine *bl; // back left
  Engine *br; // back right
};

#endif
