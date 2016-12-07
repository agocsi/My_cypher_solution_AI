#include "stdafx.h"
#include "Cypher.h"
#include <iostream>

// Match key length to the text length
int main() {
  system("chcp 1250");
  system("cls");

  std::string text_in;
  std::string key_in;
  // K�rjen be a felhaszn�l�t�l egy maximum 255 karakternyi, nem �res sz�veget!
  // A tov�bbiakban ez a ny�lt sz�veg.
  std::cout << "Add meg a k�doland� sz�veget (maximum 255 karakter):\n";
  while (std::getline(std::cin, text_in)) {
    if (text_in.empty() || text_in.length() > 255) {
      std::cout << "Meg kell adni k�doland� sz�veget, ami maximum 255 karakter "
                   "hossz� lehet!!"
                << "\n";
    } else {
      break;
    }
  };
  std::cout << "Ny�lt sz�veg: \n" << text_in << "\n";
  Input text_input(text_in, stringstate::plain_text);
  // Alak�tsa �t a ny�lt sz�veget, hogy a k�s�bbi k�dol�s felt�teleinek
  // megfeleljen! A k�dol�s felt�telei: A magyar �kezetes karakterek helyett
  // �kezetmenteseket kell haszn�lni. (P�ld�ul � helyett a; � helyett o stb.) A
  // ny�lt sz�vegben az �talak�t�s ut�n csak az angol �b�c� bet�i
  // szerepelhetnek. A ny�lt sz�veg az �talak�t�s ut�n legyen csupa nagybet�s.
  text_input.format();
  //�rja ki a k�perny�re az �talak�tott ny�lt sz�veget!
  std::cout << "Sz�veg �talak�t�sa: \n" << text_input.getText() << "\n";

  // K�rjen be a felhaszn�l�t�l egy maximum 5 karakteres, nem �res kulcssz�t! A
  // kulcssz� a k�dol�s felt�teleinek megfelel� legyen! (Sem �talak�t�s, sem
  // ellen�rz�s nem kell!)
  std::cout << "Add meg a kulcssz�t (maximum 5 karakter): \n";
  while (std::getline(std::cin, key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      std::cout << "Meg kell adni kulcsot, ami maximum 5 karakter hossz� lehet!"
                << "\n";
    } else {
      break;
    }
  };
  Input key_input(key_in, stringstate::codeable);
  // Alak�tsa �t a kulcssz�t csupa nagybet�ss�!
  key_input.format();
  // k�dol�s els� l�p�sek�nt f�zze �ssze a kulcssz�t egym�s ut�n annyiszor, hogy
  // az �gy kapott karaktersorozat (tov�bbiakban kulcssz�veg) hossza legyen
  // egyenl� a k�doland� sz�veg hossz�val!
  Input used_key = set_key_length(key_input, text_input);

  std::cout << "Kulcssz�: \n" << key_in << "\n";
  //�rja ki a k�perny�re az �gy kapott kulcssz�veget!
  std::cout << "Kulcssz� nagybet�ss� alak�t�sa: \n"
            << key_input.getText() << "\n";

  std::cout << "Ny�lt sz�veg �s kulcssz�veg egy�tt: \n"
            << text_input.getText() << "\n"
            << used_key.getText() << "\n";
  // A k�dol�s m�sodik l�p�sek�nt a k�vetkez�ket hajtsa v�gre! Vegye az
  // �talak�tott ny�lt sz�veg els� karakter�t, �s keresse meg a vtabla.dat
  // f�jlb�l beolvasott t�bl�zat els� oszlop�ban! Ezut�n vegye a kulcssz�veg
  // els� karakter�t, �s keresse meg a t�bl�zat els� sor�ban! Az �gy
  // kiv�lasztott sor �s oszlop metsz�spontj�ban l�v� karakter lesz a k�dolt
  // sz�veg els� karaktere. Ezt ism�telje a k�doland� sz�veg t�bbi karakter�vel
  // is!
  ctable cdf = read_codefile("vtabla.dat");
  Cyphering c1 = Cyphering(used_key, text_input, cdf);
  std::string coded_text = c1.cypher();
  //�rja ki a k�perny�re-
  std::cout << "K�dolt sz�veg: \n" << coded_text << "\n";

  //-�s a kodolt.dat f�jlba a kapott k�dolt sz�veget!
  std::ofstream kiirfile("kodolt.dat");
  if (kiirfile.is_open()) {
    kiirfile << coded_text;
    kiirfile.close();
  } else
    std::cout << "A f�jl nem nyithat� meg!";
  return 0;
}