#include "stdafx.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum class stringstate { plain_text, codeable, codeable_upper, code_ready };

class Input {
public:
  string text;
  stringstate state;
  void setText(string Text) { text = Text; }
  void setState(stringstate S) { state = S; }
  void format() {
    if (state == stringstate::plain_text) {
      int c;
      string textout;
      for (c = 0; c <= static_cast<int>(text.length()); c++) {
        if (text[c] >= 'a' && text[c] <= 'z') {
          textout.append(string(1, (char)(text[c])));
        } else if (text[c] >= 'A' && text[c] <= 'Z') {
          textout.append(string(1, (char)(text[c] + 32)));
        } else if (text[c] == -31 || text[c] == -63) {
          textout.append(string(1, (char)(int('a'))));
        } else if (text[c] == -23 || text[c] == -55) {
          textout.append(string(1, (char)(int('e'))));
        } else if (text[c] == -19 || text[c] == -51) {
          textout.append(string(1, (char)(int('i'))));
        } else if (text[c] == -13 || text[c] == -45 || text[c] == -10 ||
                   text[c] == -42 || text[c] == -11 || text[c] == -43) {
          textout.append(string(1, (char)(int('o'))));
        } else if (text[c] == -4 || text[c] == -36 || text[c] == -5 ||
                   text[c] == -37 || text[c] == -6 || text[c] == -38) {
          textout.append(string(1, (char)(int('u'))));
        }
      }
      state = stringstate::codeable;
      text = textout;
    }
    if (state == stringstate::codeable) {
      int c;
      for (c = 0; c < static_cast<int>(text.length()); c++) {
		  text[c] = static_cast<char>(toupper(text[c]));
      }
      state = stringstate::codeable_upper;
    }
  }
};

class Cyphering {
public:
  Input key;
  Input text_to_code;
  array<string, 26> codetable;
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
    for (int i = 0; i < static_cast<int>(text_to_code.text.length()); i++) {
      int j = 0;
      while (codetable[j].at(0) != text_to_code.text.at(i)) {
        j++;
      }
      int k = codetable[0].find(key.text.at(i));
      returned.append(1, codetable[j].at(k));
    }
    return returned;
  }
  string decypher() {
    string line;
    string returned;
    for (int i = 0; i < static_cast<int>(text_to_code.text.length()); i++) {
      int j = 0;
      while (codetable[j].at(0) != key.text.at(i)) {
        j++;
      }
      int k = codetable[0].find(text_to_code.text.at(i));
      returned.append(1, codetable[j].at(k));
    }
    return returned;
  }
};

Input set_key_l(Input key_used, Input text_used) {
  if ((key_used.state == stringstate::codeable_upper) &&
      (text_used.state == stringstate::codeable_upper)) {
    int t, k;
    Input key_l;
    for (t = 0, k = 0; t < static_cast<int>(text_used.text.length());
         t++, k++) {
      if (k >= static_cast<int>(key_used.text.length()))
        k = 0;
      key_l.text.append(string(1, (char)(key_used.text[k])));
    }
    key_l.setState(stringstate::code_ready);
    return key_l;
  } else
    exit(1);
}

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

  string textin;
  string key_in;
  // Kérjen be a felhasználótól egy maximum 255 karakternyi, nem üres szöveget!
  // A továbbiakban ez a nyílt szöveg.
  cout << "Add meg a kódolandó szöveget (maximum 255 karakter):\n";
  while (getline(cin,textin)) {
    if (textin.empty() || textin.length() > 255) {
      cout << "Meg kell adni kódolandó szöveget, ami maximum 255 karakter "
              "hosszú lehet!!"
           << endl;
    } else {
      break;
    }
  };
  cout << "Nyílt szöveg: \n" << textin << endl;
  Input text_in;
  text_in.setText(textin);
  text_in.setState(stringstate::plain_text);
  // Alakítsa át a nyílt szöveget, hogy a késõbbi kódolás feltételeinek
  // megfeleljen! A kódolás feltételei: A magyar ékezetes karakterek helyett
  // ékezetmenteseket kell használni. (Például á helyett a; õ helyett o stb.) A
  // nyílt szövegben az átalakítás után csak az angol ábécé betûi
  // szerepelhetnek. A nyílt szöveg az átalakítás után legyen csupa nagybetûs.
  text_in.format();
  //Írja ki a képernyõre az átalakított nyílt szöveget!
  cout << "Szöveg átalakítása: \n" << text_in.text << endl;

  // Kérjen be a felhasználótól egy maximum 5 karakteres, nem üres kulcsszót! A
  // kulcsszó a kódolás feltételeinek megfelelõ legyen! (Sem átalakítás, sem
  // ellenõrzés nem kell!)
  cout << "Add meg a kulcsszót (maximum 5 karakter): \n";
  while (getline(cin,key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      cout << "Meg kell adni kulcsot, ami maximum 5 karakter hosszú lehet!"
           << endl;
    } else {
      break;
    }
  };
  Input keyin;
  keyin.setText(key_in);
  keyin.setState(stringstate::codeable);
  // Alakítsa át a kulcsszót csupa nagybetûssé!
  keyin.format();
  // kódolás elsõ lépéseként fûzze össze a kulcsszót egymás után annyiszor, hogy
  // az így kapott karaktersorozat (továbbiakban kulcsszöveg) hossza legyen
  // egyenlõ a kódolandó szöveg hosszával!
  Input used_key = set_key_l(keyin, text_in);

  cout << "Kulcsszó: \n" << key_in << endl;
  //Írja ki a képernyõre az így kapott kulcsszöveget!
  cout << "Kulcsszó nagybetûssé alakítása: \n" << keyin.text << endl;

  cout << "Nyílt szöveg és kulcszöveg együtt: \n"
       << text_in.text << endl
       << used_key.text << endl;
  // A kódolás második lépéseként a következõket hajtsa végre! Vegye az
  // átalakított nyílt szöveg elsõ karakterét, és keresse meg avtabla.dat
  // fájlból beolvasott táblázat elsõ oszlopában! Ezután vegye a kulcsszöveg
  // elsõ karakterét, és keresse meg a táblázat elsõ sorában! Az így
  // kiválasztott sor és oszlop metszéspontjában lévõ karakter lesz a kódolt
  // szöveg elsõ karaktere. Ezt ismételje a kódolandó szöveg többi karakterével
  // is!
  array<string, 26> cdf = read_codefile("vtabla.dat");
  Cyphering c1;
  c1.init(used_key, text_in, cdf);
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