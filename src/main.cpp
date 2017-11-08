#include <main.hpp>
#include <inputReader.hpp>
#include <manipulator.hpp>
#include <cstdio>
#include <mutex>
#include <csignal>
#include <wiringPi.h>

using namespace std;

mutex terminator;

UI *ui;

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
  ui = new UI();
  wiringPiSetup();
  signal(SIGINT, [](int sig) -> void{terminate_main();});
  Engine **engines = new Engine *[4];
  engines[0] = new Engine( 1,  2,  3, 0);
  engines[1] = new Engine( 4,  5,  6, 1);
  engines[2] = new Engine( 7,  8,  9, 2);
  engines[3] = new Engine(10, 11, 12, 3);
  Manipulator *man = new Manipulator(engines);
  InputReader *ir = new InputReader(man);
  ir -> start();
  terminator.lock();
  terminator.lock();
  ir -> end();
  delete ir;
  delete man;
  delete engines[0];
  delete engines[1];
  delete engines[2];
  delete engines[3];
  delete[] engines;
  delete ui;
  return 0;
}
