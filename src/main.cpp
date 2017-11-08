#include <main.hpp>
#include <inputReader.hpp>
#include <manipulator.hpp>
#include <constant.hpp>
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
  engines[0] = new Engine(E1P1, E1P2, E1P3, 0);
  engines[1] = new Engine(E2P1, E2P2, E2P3, 1);
  engines[2] = new Engine(E3P1, E3P2, E3P3, 2);
  engines[3] = new Engine(E4P1, E4P2, E4P3, 3);
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
