#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

string read() {
  string input;
  cin >> input;
  return input;
}

int main() {
  string chars;

  cout << "Please provide allowed characters" << endl; 
  cin >> chars;
  
  vector<char> permitted(chars.begin(), chars.end());
  int charSpace = permitted.size();

  if (charSpace == 0) {
    cout << "No characters provided." << endl;
    return 0;
  }
  
  int amount;
  cout << "Amount?" << endl;
  cin >> amount;

  string generated = "";
  srand(time(NULL));

  cout << "Spaces? [y/n]" << endl;
  bool spaces = read() == "y";
  
  int lastSpace = -2;

  for (int i = 0; i < amount; i++) {
    if (lastSpace > 2 && rand() % 100 < 20) {
      generated += " ";
    }

    lastSpace++;
    generated += permitted[rand() % charSpace];
  }

  cout << generated << endl;

  return 0;
}
