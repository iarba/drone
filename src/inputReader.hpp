#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <thread>
#include <mutex>
#include <cstdio>
#include <termios.h>
#include <manipulator.hpp>

using namespace std;

class InputReader{
  public:
  InputReader(Manipulator *manipulator);
  ~InputReader();
  void start();
  void end();
  private:
  /* runner */
  void run();
  /* strategies */
  void directInputDetector();
  /* variables */
  thread *listener_thread;
  mutex input_lock;
  Manipulator *manipulator;
  struct termios *backup;
};

#endif
