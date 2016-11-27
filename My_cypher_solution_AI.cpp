#include "stdafx.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum class stringstate { plain_text, codeable, codeable_upper, code_ready };

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

// String with state, to format the inputted data
class Input {
 private:
  string text;
  stringstate state;

 public:
  void setText(string Text) { text = Text; }
  void setState(stringstate S) { state = S; }

  string getText() { return text; }
  stringstate getState() { return state; }

  void format() {
    if (state == stringstate::plain_text) {
      string textout;
      transform(text.begin(), text.end(), text.begin(), angletize);
      text.erase(remove_if(text.begin(), text.end(),
                           isspace),
                 text.end());
      state = stringstate::codeable;
    }
    if (state == stringstate::codeable) {
      transform(text.begin(), text.end(), text.begin(), toupper);
      state = stringstate::codeable_upper;
    }
  }
};

// Inputs with the used codetable to do the actual cyphering
class Cyphering {
 private:
  Input key;
  Input text_to_code;
  array<string, 26> codetable;
 public:
  void setKey(Input Key) { key = Key; }
  void setText_to_code(Input Text_to_code) { text_to_code = Text_to_code; }
  void setCodetable(array<string, 26> Codetable) { codetable = Codetable; }
  void init(Input Key, Input Text_to_code, array<string, 26> Codetable) {
    setKey(Key);
    setText_to_code(Text_to_code);
    setCodetable(Codetable);
  };

  string cypher() {
    string line;
    string returned;
    for (int i = 0; i < static_cast<int>(text_to_code.getText().length());
         i++) {
      int j = 0;
      while (codetable[j].at(0) != text_to_code.getText().at(i)) {
        j++;
      }
      int k = codetable[0].find(key.getText().at(i));
      returned.append(1, codetable[j].at(k));
    }
    return returned;
  }
};

// Match key length to the text length
Input set_key_length(Input key_used, Input text_used) {
  if ((key_used.getState() == stringstate::codeable_upper) &&
      (text_used.getState() == stringstate::codeable_upper)) {
    int t, k;
    Input key_l;
    for (t = 0, k = 0; t < static_cast<int>(text_used.getText().length());
         t++, k++) {
      if (k >= static_cast<int>(key_used.getText().length()))
        k = 0;
      key_l.setText(
          key_l.getText().append(string(1, static_cast<char>(key_used.getText()[k]))));
    }
    key_l.setState(stringstate::code_ready);
    return key_l;
  } else
    exit(1);
}

// Read the codetable from the provided file
array<string, 26> read_codefile(string path) {
  string line;
  ifstream myfile(path);
  int rows = 0;
  array<string, 26> codetable;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      codetable[rows] = line;
      rows++;
    }
    myfile.close();
  }
  return codetable;
};

int main() {
  system("chcp 1250");
  system("cls");

  string text_in;
  string key_in;
  // Kérjen be a felhasználótól egy maximum 255 karakternyi, nem üres szöveget!
  // A továbbiakban ez a nyílt szöveg.
  cout << "Add meg a kódolandó szöveget (maximum 255 karakter):\n";
  while (getline(cin, text_in)) {
    if (text_in.empty() || text_in.length() > 255) {
      cout << "Meg kell adni kódolandó szöveget, ami maximum 255 karakter "
              "hosszú lehet!!"
           << endl;
    } else {
      break;
    }
  };
  cout << "Nyílt szöveg: \n" << text_in << endl;
  Input text_input;
  text_input.setText(text_in);
  text_input.setState(stringstate::plain_text);
  // Alakítsa át a nyílt szöveget, hogy a késõbbi kódolás feltételeinek
  // megfeleljen! A kódolás feltételei: A magyar ékezetes karakterek helyett
  // ékezetmenteseket kell használni. (Például á helyett a; õ helyett o stb.) A
  // nyílt szövegben az átalakítás után csak az angol ábécé betûi
  // szerepelhetnek. A nyílt szöveg az átalakítás után legyen csupa nagybetûs.
  text_input.format();
  //Írja ki a képernyõre az átalakított nyílt szöveget!
  cout << "Szöveg átalakítása: \n" << text_input.getText() << endl;

  // Kérjen be a felhasználótól egy maximum 5 karakteres, nem üres kulcsszót! A
  // kulcsszó a kódolás feltételeinek megfelelõ legyen! (Sem átalakítás, sem
  // ellenõrzés nem kell!)
  cout << "Add meg a kulcsszót (maximum 5 karakter): \n";
  while (getline(cin, key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      cout << "Meg kell adni kulcsot, ami maximum 5 karakter hosszú lehet!"
           << endl;
    } else {
      break;
    }
  };
  Input key_input;
  key_input.setText(key_in);
  key_input.setState(stringstate::codeable);
  // Alakítsa át a kulcsszót csupa nagybetûssé!
  key_input.format();
  // kódolás elsõ lépéseként fûzze össze a kulcsszót egymás után annyiszor, hogy
  // az így kapott karaktersorozat (továbbiakban kulcsszöveg) hossza legyen
  // egyenlõ a kódolandó szöveg hosszával!
  Input used_key = set_key_length(key_input, text_input);

  cout << "Kulcsszó: \n" << key_in << endl;
  //Írja ki a képernyõre az így kapott kulcsszöveget!
  cout << "Kulcsszó nagybetûssé alakítása: \n" << key_input.getText() << endl;

  cout << "Nyílt szöveg és kulcsszöveg együtt: \n"
       << text_input.getText() << "\n"
       << used_key.getText() << "\n";
  // A kódolás második lépéseként a következõket hajtsa végre! Vegye az
  // átalakított nyílt szöveg elsõ karakterét, és keresse meg avtabla.dat
  // fájlból beolvasott táblázat elsõ oszlopában! Ezután vegye a kulcsszöveg
  // elsõ karakterét, és keresse meg a táblázat elsõ sorában! Az így
  // kiválasztott sor és oszlop metszéspontjában lévõ karakter lesz a kódolt
  // szöveg elsõ karaktere. Ezt ismételje a kódolandó szöveg többi karakterével
  // is!
  array<string, 26> cdf = read_codefile("vtabla.dat");
  Cyphering c1;
  c1.init(used_key, text_input, cdf);
  string coded_text = c1.cypher();

  //Írja ki a képernyõre-
  cout << "Kódolt szöveg: \n" << coded_text << endl;

  //-és a kodolt.dat fájlba a kapott kódolt szöveget!
  ofstream kiirfile("kodolt.dat");
  if (kiirfile.is_open()) {
    kiirfile << coded_text;
    kiirfile.close();
  } else
    cout << "A fájl nem nyitható meg!";
  return 0;
}