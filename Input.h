#pragma once
#include <algorithm>
#include <string>

// Possible states of the Input
enum class stringstate { plain_text, codeable, codeable_upper, code_ready };

// Change hungarian special characters to their english basic counterparts, keep
// english alphabetic characters, change everything else to whitespace for
// easier erase
char angletize(char ch);

// String with state, to format the inputted data
class Input {
 private:
  std::string text;
  stringstate state;

 public:
  void setText(std::string Text);
  void setState(stringstate S);
  std::string getText() const;
  stringstate getState() const;
  Input(std::string Text, stringstate S);
  void format();
};

Input set_key_length(Input key_used, Input text_used);