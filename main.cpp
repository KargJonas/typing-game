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

string red(string message)
{
  return RED + message + RESET;
}

#define NEWLINE_SYMBOL red("↵ ");

int main()
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  unsigned int terminalWidth = w.ws_col;

  clock_t timeBegin;

  ifstream t("text.txt");
  string text(
      (istreambuf_iterator<char>(t)),
      istreambuf_iterator<char>());

  text += "\n";

  const unsigned int textLength = text.length();

  string currentLine = "";
  vector<string> wrappedText;

  for (unsigned int i = 0; i <= textLength; i++) {
    currentLine += text[i];

    if (text[i] == '\n') {
      wrappedText.push_back(currentLine);
      currentLine = "";
    }
  }

  currentLine.clear();
  text.clear();

  cout << "Press space to start the game!" << endl;
  while (getch() != ' ') {
    timeBegin = clock();
  }

  unsigned int errors = 0;
  unsigned int lineCount = wrappedText.size();
  unsigned int lineLength = 0;
  string line;
  string displayLine;

  for (unsigned int i = 0; i < lineCount; i++) {
    // The text, which we are comparing the user's input t
    line = wrappedText[i];

    while (line.length() != 0) {
      lineLength = line.length();

      // The text, which is displayed to the user
      displayLine = line.substr(0, min(terminalWidth, lineLength) - 1);

      if (lineLength < terminalWidth - 1) {
        displayLine += NEWLINE_SYMBOL;
      }

      // Overwriting the last line with the current one
      cout << displayLine << "\r" << flush;

      if (line[0] == getch()) {
        line.erase(0, 1);
      } else {
        errors++;
      }
    }
  }

  clock_t timeEnd = clock();
  int time = (timeEnd - timeBegin) / 1000.0;
  double typingSpeed = textLength / (time / 60.0);

  cout << "[-] Time:\t" << floor(time / 60.0) << "min " << time % 60 << "sec " << endl;
  cout << "[-] Speed:\t" << typingSpeed << " chars/min" << endl;
  cout << "[-] Characters:\t" << textLength << endl;
  cout << "[-] Errors: \t" << errors << endl;
  cout << "[-] Accuracy: \t" << 100 - (min(textLength, errors) / float(textLength)) * 100.0 << "%" << endl;

  return 0;
}
