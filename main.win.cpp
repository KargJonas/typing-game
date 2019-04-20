#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <windows.h>

using namespace std;

#define NEWLINE_SYMBOL "\033[31m↵ \033[0m"

char getch() {
  DWORD mode, cc;
  HANDLE h = GetStdHandle( STD_INPUT_HANDLE );
  if (h == NULL) {
        return 0; // console not found
  }
  GetConsoleMode( h, &mode );
  SetConsoleMode( h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT) );
  TCHAR c = 0;
  ReadConsole( h, &c, 1, &cc, NULL );
  SetConsoleMode( h, mode );
  return c;
}

int main(int argc, char *argv[])
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  unsigned int terminalWidth = w.ws_col;

  clock_t timeBegin;
  string file = "text.txt";

  if (argc >= 2) {
    file = argv[1];
  }

  ifstream t(file);
  string text(
      (istreambuf_iterator<char>(t)),
      istreambuf_iterator<char>());

  const unsigned int textLength = text.length();

  if (textLength <= 0) {
    cout << "The file you loaded seems to be empty..." << endl;
    return 0;
  }

  text += "\n";

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
