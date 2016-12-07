#include "stdafx.h"
#include "Input.h"

// Change hungarian special characters to their english basic counterparts, keep
// english alphabetic characters, change everything else to whitespace for
// easier erase
char angletize(char ch) {
  if (ch >= 'a' && ch <= 'z') {
  } else if (ch >= 'A' && ch <= 'Z') {
    ch = ch + 32;
  } else if (ch == static_cast<char>(-31) || ch == static_cast<char>(-63)) {
    ch = 'a';
  } else if (ch == static_cast<char>(-23) || ch == static_cast<char>(-55)) {
    ch = 'e';
  } else if (ch == static_cast<char>(-19) || ch == static_cast<char>(-51)) {
    ch = 'i';
  } else if (ch == static_cast<char>(-13) || ch == static_cast<char>(-45) ||
             ch == static_cast<char>(-10) || ch == static_cast<char>(-42) ||
             ch == static_cast<char>(-11) || ch == static_cast<char>(-43)) {
    ch = 'o';
  } else if (ch == static_cast<char>(-4) || ch == static_cast<char>(-36) ||
             ch == static_cast<char>(-5) || ch == static_cast<char>(-37) ||
             ch == static_cast<char>(-6) || ch == static_cast<char>(-38)) {
    ch = 'u';
  } else {
    ch = ' ';
  }
  return ch;
}

inline void Input::setText(std::string Text) {
  text = Text;
}

inline void Input::setState(stringstate S) {
  state = S;
}

inline std::string Input::getText() const {
  return text;
}

inline stringstate Input::getState() const {
  return state;
}

Input::Input(std::string Text, stringstate S) : text(Text), state(S) {}

void Input::format() {
  if (state == stringstate::plain_text) {
    std::string textout;
    transform(text.begin(), text.end(), text.begin(), angletize);
    text.erase(remove_if(text.begin(), text.end(), isspace), text.end());
    state = stringstate::codeable;
  }
  if (state == stringstate::codeable) {
    transform(text.begin(), text.end(), text.begin(), toupper);
    state = stringstate::codeable_upper;
  }
}

// Match key length to the given text
Input set_key_length(Input key_used, Input text_used) {
  if ((key_used.getState() == stringstate::codeable_upper) &&
      (text_used.getState() == stringstate::codeable_upper)) {
    std::string new_key = text_used.getText();
    int t = 0;
    for (char& ch : new_key) {
      int key_at = div(t, key_used.getText().length()).rem;
      ch = key_used.getText().at(key_at);
      t++;
    }
    Input key_l(new_key, stringstate::code_ready);
    return key_l;
  } else
    exit(1);
}