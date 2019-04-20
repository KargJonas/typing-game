/* ** ToDo **
 *  - Don't split by screen with but by \n in text.
 *      - Horizontal overflow
 *  - Determine typing speed
 *      - Characters
 *      - Words
 *  - Error highlighting
 *
 */

// #include "./colors.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <streambuf>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "getch.h"
using namespace std;

string red(string message)
{
  return "\033[31m" + message + "\033[0m";
}

const string newlineSymbol = red("↵ ");

int main()
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  unsigned int terminalWidth = w.ws_col;

  ifstream t("text.txt");
  string text(
      (istreambuf_iterator<char>(t)),
      istreambuf_iterator<char>());

  string currentLine = "";
  vector<string> wrappedText;

  for (unsigned int i = 0; i < text.length(); i++) {
    currentLine += text[i];

    if (text[i] == '\n') {
      wrappedText.push_back(currentLine);
      currentLine = "";
    }
  }

  cout << "Press space to start the game!" << endl;
  while (getch() != ' ') {
  }

  unsigned int errors = 0;
  unsigned int lineCount = wrappedText.size();

  for (unsigned int i = 0; i < lineCount; i++) {
    string line = wrappedText[i];
    string displayLine = line.substr(0, line.length() - 1) + newlineSymbol;

    while (line.length() != 0) {
      cout << displayLine << "\r" << flush;
      char input;
      bool correct = false;

      do {
        input = getch();

        if (line[0] == input) {
          correct = true;
        } else {
          errors++;
        }
      } while (!correct);

      line.erase(0, 1);
      displayLine = line.substr(0, line.length() - 1) + newlineSymbol;
    }
  }

  cout << "Errors: " << errors << endl;

  return 0;
}
