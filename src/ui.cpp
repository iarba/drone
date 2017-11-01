#include <ui.hpp>
#define TS "          "
#define NL "\n"
#define EL TS TS TS TS TS TS TS TS NL

UI::UI()
{
  cur_x = 0;
  cur_y = 0;
  /* set up canvas made of empty spaces */
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  render(cur_x, cur_y, EL);
  /* Load graphics */
  render(0, 0, "name:");
  render(1, 0, "*--------------*");
  render(2, 0, "|E0<   /\\   >E1|");
  render(3, 0, "|              |");
  render(4, 0, "|              |");
  render(5, 0, "|              |");
  render(6, 0, "|              |");
  render(7, 0, "|              |");
  render(8, 0, "|E2>        <E3|");
  render(9, 0, "*--------------*");
  render(1, 18, "Engine 0(front-left) :");
  render(1, 41, "Power(%):");
  render(2, 41, "Frequency(Hz):");
  render(3, 18, "Engine 1(front-right):");
  render(3, 41, "Power(%):");
  render(4, 41, "Frequency(Hz):");
  render(5, 18, "Engine 2(back-left)  :");
  render(5, 41, "Power(%):");
  render(6, 41, "Frequency(Hz):");
  render(7, 18, "Engine 3(back-right) :");
  render(7, 41, "Power(%):");
  render(8, 41, "Frequency(Hz):");
}

UI::~UI()
{
  render(24, 80, "\n");
}

void UI::render(int at_x, int at_y, string s)
{
  render(at_x, at_y, s.c_str());
}

void UI::render(int at_x, int at_y, const char *c)
{
  ui_lock.lock();
  while(at_x < cur_x) // need to navigate up
  {
    printf("\x1b[A");
    cur_x--;
  }
  while(at_x > cur_x) // need to navigate down
  {
    printf("\x1b[B");
    cur_x++;
  }
  while(at_y > cur_y) // need to navigate right
  {
    printf("\x1b[C");
    cur_y++;
  }
  while(at_y < cur_y) // need to navigate left
  {
    printf("\x1b[D");
    cur_y--;
  }
  printf("%s", c);
  const char *key;
  for(key = c; *key; key++)
  {
    if(*key == '\n')
    {
      cur_x++;
      cur_y = 0;
    }
    else
    {
      cur_y ++;
    }
  }
  fflush(stdout);
  ui_lock.unlock();
}

void UI::react(Event *e)
{
  if(e -> type == E_MOTOR_SET)
  {
    render(e -> id * 2 + 1, 56, e -> power);
    render(e -> id * 2 + 2, 56, e -> freq);
  }
  if(e -> type == E_INPUT_UNK)
  {
    render(10, 3, e -> msg);
  }
  delete(e);
}
