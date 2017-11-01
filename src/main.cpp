#include <main.hpp>
#include <inputReader.hpp>
#include <manipulator.hpp>
#include <cstdio>
#include <mutex>

using namespace std;

mutex terminator;

void terminate_main()
{
  if(terminator.try_lock())
  {
    fprintf(stderr, "double termination or incomplete initialisation\n");
  }
  terminator.unlock();
}

int main(int argc, char **argv)
{
  printf("I believe I can fly!\n");
  Manipulator *man = new Manipulator();
  InputReader *ir = new InputReader(man);
  ir -> start();
  terminator.lock();
  terminator.lock();
  ir -> end();
  delete ir;
  delete man;
  return 0;
}
