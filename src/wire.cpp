#include "wire.h"

#ifdef wiring
#include <wiringPi.h>
#endif

void wires_init()
{
#ifdef wiring
  wiringPiSetup(); 
#endif  
}

int wire_init(int id)
{
#ifdef wiring
  pinMode(id, OUTPUT);
#endif  
  wire_turn_off(id);
  return 0;
}

void wire_turn_on(int id)
{
#ifdef wiring
  digitalWrite(id, HIGH);
#endif  
}

void wire_turn_off(int id)
{
#ifdef wiring
  digitalWrite(id, LOW);
#endif  
}
