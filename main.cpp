/* ** ToDo **
 *  - Horizontal overflow
 *  - Determine typing speed
 *      - Characters
 *      - Words
 *  - Error highlighting
 *
 */

#include "getch.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sys/ioctl.h>
#include <vector>

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"

string red(string message) { return RED + message + RESET; }

#define NEWLINE_SYMBOL red("↵ ");

string styleText(string text)
{
  return text.substr(0, text.length() - 1) + NEWLINE_SYMBOL;
}

int main()
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  unsigned int terminalWidth = w.ws_col;

  clock_t begin;

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
    begin = clock();
  }

  unsigned int errors = 0;
  unsigned int lineCount = wrappedText.size();
  string line;

  for (unsigned int i = 0; i < lineCount; i++) {
    // The text, which we are comparing the user's input t
    line = wrappedText[i];

    while (line.length() != 0) {
      // Overwriting the last line with the current one
      cout << styleText(line) << "\r" << flush;

      if (line[0] == getch()) {
        line.erase(0, 1);
      } else {
        errors++;
      }
    }
  }

  cout << "Errors: " << errors << endl;

  return 0;
}
