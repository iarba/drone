#include <main.hpp>
#include <inputReader.hpp>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  printf("I believe I can fly!\n");
  (new InputReader(NULL)) -> start();
  while(1);
  return 0;
}
