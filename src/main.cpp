#include <cstdio>
#include "manipulator.h"

int main(int argc, char **argv)
{
  printf("I believe I can fly!\n");
  Manipulator man = Manipulator();
  man.start();
  return 0;
}
