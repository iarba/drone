#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

typedef void * MANIPTYPE;

#include <thread>
#include <mutex>
#include <cstdio>
#include <termios.h>

using namespace std;

class InputReader{
  public:
  InputReader(MANIPTYPE manipulator);
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
  MANIPTYPE manipulator;
  struct termios *backup;
};

#endif
