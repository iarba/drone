#include <inputReader.hpp>
#include <unistd.h>

struct termios orig_termios;

struct termios *getTerminal()
{
  struct termios *terminal = (struct termios *) malloc(sizeof(struct termios));
  tcgetattr(STDIN_FILENO, terminal);
  return terminal;
}

void setTerminal(struct termios *setting)
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, setting);
}

void enableRawMode()
{
  struct termios *terminal = getTerminal();
  terminal -> c_lflag &= ~(ECHO | ICANON);
  setTerminal(terminal);
  free(terminal);
}

InputReader::InputReader(Manipulator *manipulator)
{
  this -> listener_thread = NULL;
  this -> manipulator = manipulator;
  this -> backup = getTerminal();
}

InputReader::~InputReader()
{
  setTerminal(this -> backup);
  free(this -> backup);
}

void InputReader::start()
{
  if(!listener_thread)
  {
    enableRawMode();
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
  read(STDIN_FILENO, &c, 1);
  // give char to manipulator
  this -> manipulator -> feed_raw(c);
}
