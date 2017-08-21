#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <thread>
#include <mutex>
#include <cstdio>

using namespace std;

class InputReader{
  public:
  InputReader(void *manipulator);
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
  void *manipulator;
};

#endif
