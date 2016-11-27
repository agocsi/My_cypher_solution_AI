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
  // K�rjen be a felhaszn�l�t�l egy maximum 255 karakternyi, nem �res sz�veget!
  // A tov�bbiakban ez a ny�lt sz�veg.
  cout << "Add meg a k�doland� sz�veget (maximum 255 karakter):\n";
  while (getline(cin,textin)) {
    if (textin.empty() || textin.length() > 255) {
      cout << "Meg kell adni k�doland� sz�veget, ami maximum 255 karakter "
              "hossz� lehet!!"
           << endl;
    } else {
      break;
    }
  };
  cout << "Ny�lt sz�veg: \n" << textin << endl;
  Input text_in;
  text_in.setText(textin);
  text_in.setState(stringstate::plain_text);
  // Alak�tsa �t a ny�lt sz�veget, hogy a k�s�bbi k�dol�s felt�teleinek
  // megfeleljen! A k�dol�s felt�telei: A magyar �kezetes karakterek helyett
  // �kezetmenteseket kell haszn�lni. (P�ld�ul � helyett a; � helyett o stb.) A
  // ny�lt sz�vegben az �talak�t�s ut�n csak az angol �b�c� bet�i
  // szerepelhetnek. A ny�lt sz�veg az �talak�t�s ut�n legyen csupa nagybet�s.
  text_in.format();
  //�rja ki a k�perny�re az �talak�tott ny�lt sz�veget!
  cout << "Sz�veg �talak�t�sa: \n" << text_in.text << endl;

  // K�rjen be a felhaszn�l�t�l egy maximum 5 karakteres, nem �res kulcssz�t! A
  // kulcssz� a k�dol�s felt�teleinek megfelel� legyen! (Sem �talak�t�s, sem
  // ellen�rz�s nem kell!)
  cout << "Add meg a kulcssz�t (maximum 5 karakter): \n";
  while (getline(cin,key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      cout << "Meg kell adni kulcsot, ami maximum 5 karakter hossz� lehet!"
           << endl;
    } else {
      break;
    }
  };
  Input keyin;
  keyin.setText(key_in);
  keyin.setState(stringstate::codeable);
  // Alak�tsa �t a kulcssz�t csupa nagybet�ss�!
  keyin.format();
  // k�dol�s els� l�p�sek�nt f�zze �ssze a kulcssz�t egym�s ut�n annyiszor, hogy
  // az �gy kapott karaktersorozat (tov�bbiakban kulcssz�veg) hossza legyen
  // egyenl� a k�doland� sz�veg hossz�val!
  Input used_key = set_key_l(keyin, text_in);

  cout << "Kulcssz�: \n" << key_in << endl;
  //�rja ki a k�perny�re az �gy kapott kulcssz�veget!
  cout << "Kulcssz� nagybet�ss� alak�t�sa: \n" << keyin.text << endl;

  cout << "Ny�lt sz�veg �s kulcsz�veg egy�tt: \n"
       << text_in.text << endl
       << used_key.text << endl;
  // A k�dol�s m�sodik l�p�sek�nt a k�vetkez�ket hajtsa v�gre! Vegye az
  // �talak�tott ny�lt sz�veg els� karakter�t, �s keresse meg avtabla.dat
  // f�jlb�l beolvasott t�bl�zat els� oszlop�ban! Ezut�n vegye a kulcssz�veg
  // els� karakter�t, �s keresse meg a t�bl�zat els� sor�ban! Az �gy
  // kiv�lasztott sor �s oszlop metsz�spontj�ban l�v� karakter lesz a k�dolt
  // sz�veg els� karaktere. Ezt ism�telje a k�doland� sz�veg t�bbi karakter�vel
  // is!
  array<string, 26> cdf = read_codefile("vtabla.dat");
  Cyphering c1;
  c1.init(used_key, text_in, cdf);
  string coded_text = c1.cypher();

  //�rja ki a k�perny�re-
  cout << "K�dolt sz�veg: \n" << coded_text << endl;

  //-�s a kodolt.dat f�jlba a kapott k�dolt sz�veget!
  ofstream kiirfile("kodolt.dat");
  if (kiirfile.is_open()) {
    kiirfile << coded_text;
    kiirfile.close();
  } else
    cout << "A f�jl nem nyithat� meg!";
  return 0;
}