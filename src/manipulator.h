#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#define N_ENGINES 4

#include "engine.h"

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
  private:
  void loop();
  Engine *engines[N_ENGINES];
};

#endif
