#include <termios.h>
#include <unistd.h>

char getch()
{
  char buf = 0;
  struct termios old = { 0 };

  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  return (buf);
}