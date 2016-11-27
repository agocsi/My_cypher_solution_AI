#include "stdafx.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum class stringstate { plain_text, codeable, codeable_upper, code_ready };

//Change hungarian special characters to their english basic counterparts, keep english alphabetic characters, change everything else to whitespace for easier erase
char angletize(char ch) {
	if (ch >= 'a' && ch <= 'z') {
	}
	else if (ch >= 'A' && ch <= 'Z') {
		ch = ch + 32;
	}
	else if (ch == static_cast<char>(-31) || ch == static_cast<char>(-63)) {
		ch = 'a';
	}
	else if (ch == static_cast<char>(-23) || ch == static_cast<char>(-55)) {
		ch = 'e';
	}
	else if (ch == static_cast<char>(-19) || ch == static_cast<char>(-51)) {
		ch = 'i';
	}
	else if (ch == static_cast<char>(-13) || ch == static_cast<char>(-45) ||
		ch == static_cast<char>(-10) || ch == static_cast<char>(-42) ||
		ch == static_cast<char>(-11) || ch == static_cast<char>(-43)) {
		ch = 'o';
	}
	else if (ch == static_cast<char>(-4) || ch == static_cast<char>(-36) ||
		ch == static_cast<char>(-5) || ch == static_cast<char>(-37) ||
		ch == static_cast<char>(-6) || ch == static_cast<char>(-38)) {
		ch = 'u';
	}
	else {
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
	void setText(string Text) { text = Text; };
	void setState(stringstate S) { state = S; };
	string getText() const { return text; }
	stringstate getState() const { return state; }
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
  Cyphering(Input Key, Input Text_to_code, array<string, 26> Codetable) {
    key = Key;
    text_to_code = Text_to_code;
    codetable = Codetable;
  };

  string cypher() {
    string returned;
	int count = 0;
    for (char ch : text_to_code.getText()) {
		int row = 0;
      while (codetable[row].at(0) != ch) {
        row++;
      }
	  int column = codetable[0].find(key.getText().at(count));
	  returned.append(1, codetable[row].at(column));
	  count++;
    }
	return returned;
  }
};

// Match key length to the text length
Input set_key_length(Input key_used, Input text_used) {
  if ((key_used.getState() == stringstate::codeable_upper) &&
      (text_used.getState() == stringstate::codeable_upper)) {
    Input key_l;
	string new_key = text_used.getText();
	int t = 0;
	for (char& ch : new_key)
	{
		int key_at = div(t, key_used.getText().length()).rem;
		ch = key_used.getText().at(key_at);
		t++;
	}
	key_l.setText(new_key);
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
  }
  return codetable;
};

int main() {
  system("chcp 1250");
  system("cls");

  string text_in;
  string key_in;
  // K�rjen be a felhaszn�l�t�l egy maximum 255 karakternyi, nem �res sz�veget!
  // A tov�bbiakban ez a ny�lt sz�veg.
  cout << "Add meg a k�doland� sz�veget (maximum 255 karakter):\n";
  while (getline(cin, text_in)) {
    if (text_in.empty() || text_in.length() > 255) {
      cout << "Meg kell adni k�doland� sz�veget, ami maximum 255 karakter "
              "hossz� lehet!!"
           << "\n";
    } else {
      break;
    }
  };
  cout << "Ny�lt sz�veg: \n" << text_in << "\n";
  Input text_input;
  text_input.setText(text_in);
  text_input.setState(stringstate::plain_text);
  // Alak�tsa �t a ny�lt sz�veget, hogy a k�s�bbi k�dol�s felt�teleinek
  // megfeleljen! A k�dol�s felt�telei: A magyar �kezetes karakterek helyett
  // �kezetmenteseket kell haszn�lni. (P�ld�ul � helyett a; � helyett o stb.) A
  // ny�lt sz�vegben az �talak�t�s ut�n csak az angol �b�c� bet�i
  // szerepelhetnek. A ny�lt sz�veg az �talak�t�s ut�n legyen csupa nagybet�s.
  text_input.format();
  //�rja ki a k�perny�re az �talak�tott ny�lt sz�veget!
  cout << "Sz�veg �talak�t�sa: \n" << text_input.getText() << "\n";

  // K�rjen be a felhaszn�l�t�l egy maximum 5 karakteres, nem �res kulcssz�t! A
  // kulcssz� a k�dol�s felt�teleinek megfelel� legyen! (Sem �talak�t�s, sem
  // ellen�rz�s nem kell!)
  cout << "Add meg a kulcssz�t (maximum 5 karakter): \n";
  while (getline(cin, key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      cout << "Meg kell adni kulcsot, ami maximum 5 karakter hossz� lehet!"
           << "\n";
    } else {
      break;
    }
  };
  Input key_input;
  key_input.setText(key_in);
  key_input.setState(stringstate::codeable);
  // Alak�tsa �t a kulcssz�t csupa nagybet�ss�!
  key_input.format();
  // k�dol�s els� l�p�sek�nt f�zze �ssze a kulcssz�t egym�s ut�n annyiszor, hogy
  // az �gy kapott karaktersorozat (tov�bbiakban kulcssz�veg) hossza legyen
  // egyenl� a k�doland� sz�veg hossz�val!
  Input used_key = set_key_length(key_input, text_input);

  cout << "Kulcssz�: \n" << key_in << "\n";
  //�rja ki a k�perny�re az �gy kapott kulcssz�veget!
  cout << "Kulcssz� nagybet�ss� alak�t�sa: \n" << key_input.getText() << "\n";

  cout << "Ny�lt sz�veg �s kulcssz�veg egy�tt: \n"
       << text_input.getText() << "\n"
       << used_key.getText() << "\n";
  // A k�dol�s m�sodik l�p�sek�nt a k�vetkez�ket hajtsa v�gre! Vegye az
  // �talak�tott ny�lt sz�veg els� karakter�t, �s keresse meg avtabla.dat
  // f�jlb�l beolvasott t�bl�zat els� oszlop�ban! Ezut�n vegye a kulcssz�veg
  // els� karakter�t, �s keresse meg a t�bl�zat els� sor�ban! Az �gy
  // kiv�lasztott sor �s oszlop metsz�spontj�ban l�v� karakter lesz a k�dolt
  // sz�veg els� karaktere. Ezt ism�telje a k�doland� sz�veg t�bbi karakter�vel
  // is!
  array<string, 26> cdf = read_codefile("vtabla.dat");
  Cyphering c1 = Cyphering(used_key, text_input, cdf);
   string coded_text = c1.cypher();

  //�rja ki a k�perny�re-
  cout << "K�dolt sz�veg: \n" << coded_text << "\n";

  //-�s a kodolt.dat f�jlba a kapott k�dolt sz�veget!
  ofstream kiirfile("kodolt.dat");
  if (kiirfile.is_open()) {
    kiirfile << coded_text;
    kiirfile.close();
  } else
    cout << "A f�jl nem nyithat� meg!";
  return 0;
}