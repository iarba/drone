#include <inputReader.hpp>

InputReader::InputReader(void *manipulator)
{
  this -> listener_thread = NULL;
  this -> manipulator = manipulator;
}

void InputReader::start()
{
  if(!listener_thread)
  {
    listener_thread = new thread(&InputReader::run, this);
  }
}

void InputReader::end()
{
  input_lock.lock();
  listener_thread -> join();
  delete listener_thread;
}

void InputReader::run()
{
  while(input_lock.try_lock())
  {
    input_lock.unlock();
    directInputDetector();
  }
}

/* Strategies for reading input */

void InputReader::directInputDetector()
{
  char c;
  // get character c
  c = 'w';
  // give char to manipulator
  printf("%c", c);
}