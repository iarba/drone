#include <cstdio>
#include "manipulator.h"
#include "wire.h"

int main(int argc, char **argv)
{
  printf("I believe I can fly!\n");
  wires_init();
  Manipulator man = Manipulator();
  man.start();
  return 0;
}
