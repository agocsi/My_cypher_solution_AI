#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include "Input.h"
using namespace std;
// Inputs with the used codetable to do the actual cyphering
class Cyphering {
 private:
  Input key;
  Input text_to_code;
  array<string, 26> codetable;

 public:
  Cyphering(Input Key, Input Text_to_code, array<string, 26> Codetable);
  void setCyph(Input Key, Input Text_to_code, array<string, 26> Codetable);

  string cypher();
};
// Read the codetable from the provided file
array<string, 26> read_codefile(string path);