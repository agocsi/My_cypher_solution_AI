#include "stdafx.h"
#include "Cypher.h"
#include <iostream>

// Match key length to the text length
int main() {
  system("chcp 1250");
  system("cls");

  std::string text_in;
  std::string key_in;
  // Kérjen be a felhasználótól egy maximum 255 karakternyi, nem üres szöveget!
  // A továbbiakban ez a nyílt szöveg.
  std::cout << "Add meg a kódolandó szöveget (maximum 255 karakter):\n";
  while (std::getline(std::cin, text_in)) {
    if (text_in.empty() || text_in.length() > 255) {
      std::cout << "Meg kell adni kódolandó szöveget, ami maximum 255 karakter "
                   "hosszú lehet!!"
                << "\n";
    } else {
      break;
    }
  };
  std::cout << "Nyílt szöveg: \n" << text_in << "\n";
  Input text_input(text_in, stringstate::plain_text);
  // Alakítsa át a nyílt szöveget, hogy a késõbbi kódolás feltételeinek
  // megfeleljen! A kódolás feltételei: A magyar ékezetes karakterek helyett
  // ékezetmenteseket kell használni. (Például á helyett a; õ helyett o stb.) A
  // nyílt szövegben az átalakítás után csak az angol ábécé betûi
  // szerepelhetnek. A nyílt szöveg az átalakítás után legyen csupa nagybetûs.
  text_input.format();
  //Írja ki a képernyõre az átalakított nyílt szöveget!
  std::cout << "Szöveg átalakítása: \n" << text_input.getText() << "\n";

  // Kérjen be a felhasználótól egy maximum 5 karakteres, nem üres kulcsszót! A
  // kulcsszó a kódolás feltételeinek megfelelõ legyen! (Sem átalakítás, sem
  // ellenõrzés nem kell!)
  std::cout << "Add meg a kulcsszót (maximum 5 karakter): \n";
  while (std::getline(std::cin, key_in)) {
    if (key_in.empty() || key_in.length() > 5) {
      std::cout << "Meg kell adni kulcsot, ami maximum 5 karakter hosszú lehet!"
                << "\n";
    } else {
      break;
    }
  };
  Input key_input(key_in, stringstate::codeable);
  // Alakítsa át a kulcsszót csupa nagybetûssé!
  key_input.format();
  // kódolás elsõ lépéseként fûzze össze a kulcsszót egymás után annyiszor, hogy
  // az így kapott karaktersorozat (továbbiakban kulcsszöveg) hossza legyen
  // egyenlõ a kódolandó szöveg hosszával!
  Input used_key = set_key_length(key_input, text_input);

  std::cout << "Kulcsszó: \n" << key_in << "\n";
  //Írja ki a képernyõre az így kapott kulcsszöveget!
  std::cout << "Kulcsszó nagybetûssé alakítása: \n"
            << key_input.getText() << "\n";

  std::cout << "Nyílt szöveg és kulcsszöveg együtt: \n"
            << text_input.getText() << "\n"
            << used_key.getText() << "\n";
  // A kódolás második lépéseként a következõket hajtsa végre! Vegye az
  // átalakított nyílt szöveg elsõ karakterét, és keresse meg a vtabla.dat
  // fájlból beolvasott táblázat elsõ oszlopában! Ezután vegye a kulcsszöveg
  // elsõ karakterét, és keresse meg a táblázat elsõ sorában! Az így
  // kiválasztott sor és oszlop metszéspontjában lévõ karakter lesz a kódolt
  // szöveg elsõ karaktere. Ezt ismételje a kódolandó szöveg többi karakterével
  // is!
  ctable cdf = read_codefile("vtabla.dat");
  Cyphering c1 = Cyphering(used_key, text_input, cdf);
  std::string coded_text = c1.cypher();
  //Írja ki a képernyõre-
  std::cout << "Kódolt szöveg: \n" << coded_text << "\n";

  //-és a kodolt.dat fájlba a kapott kódolt szöveget!
  std::ofstream kiirfile("kodolt.dat");
  if (kiirfile.is_open()) {
    kiirfile << coded_text;
    kiirfile.close();
  } else
    std::cout << "A fájl nem nyitható meg!";
  return 0;
}