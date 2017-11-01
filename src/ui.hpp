#ifndef USERINTERF_HPP
#define USERINTERF_HPP

#include <mutex>
#include <cstring>
#include <string>
#include <cstdio>
#include <event.hpp>

using namespace std;

class UI{
  public:
  UI();
  ~UI();
  void render(int at_x, int at_y, string s);
  void render(int at_x, int at_y, const char *c);
  void react(Event *e);
  private:
  mutex ui_lock;
  int cur_x;
  int cur_y;
};

#endif
