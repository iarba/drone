#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "engine.h"
#include "constants.h"

/* Manipulator
 * 
 * Used as a middle-ground between input and engine control.
 * Receives and maintains information from various sensors.
 * Controls engines according to internal representation
 */

class Manipulator{
  public:
  Manipulator();
  ~Manipulator();
  void panic(); // to be called in times of trouble
  void start();
  private:
  void loop(int ts);
  Engine *engines[N_ENGINES];
};

#endif
