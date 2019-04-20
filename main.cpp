/* ** ToDo **
 *  - Horizontal overflow
 *  - Determine typing speed
 *      - Characters
 *      - Words
 *  - Error highlighting
 *
 */

#include "getch.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <streambuf>
#include <sys/ioctl.h>
#include <vector>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"

string red(string message)
{
  return RED + message + RESET;
}

const string newlineSymbol = red("↵ ");

string styleText(string text) {
  return text.substr(0, text.length() - 1) + newlineSymbol;
}

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
  string line;
  string displayLine;

  for (unsigned int i = 0; i < lineCount; i++) {
    // The text, which we are comparing the user's input t
    line = wrappedText[i];

    // The text, which is displayed to the user
    displayLine = styleText(line);
    cout <<  displayLine;
    return 0;

    while (line.length() != 0) {
      cout << displayLine << "\r" << flush;
      char input;
      bool correct = false;

      input = getch();

      if (line[0] == input) {
        correct = true;
        line.erase(0, 1);
        displayLine = styleText(line);
      } else {
        errors++;
      }
    }
  }

  cout << "Errors: " << errors << endl;

  return 0;
}
