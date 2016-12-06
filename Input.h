#pragma once
#include <string>
#include <algorithm>
using namespace std;

enum class stringstate { plain_text, codeable, codeable_upper, code_ready };
// Change hungarian special characters to their english basic counterparts, keep
// english alphabetic characters, change everything else to whitespace for
// easier erase
char angletize(char ch);

// String with state, to format the inputted data
class Input {
 private:
  string text;
  stringstate state;
  void setInput(string Text, stringstate S);

 public:
  void setText(string Text);
  void setState(stringstate S);
  string getText() const;
  stringstate getState() const;
  Input();
  Input(string Text, stringstate S);
  void format();
};

Input set_key_length(Input key_used, Input text_used);