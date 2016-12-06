#include "stdafx.h"
#include "Cypher.h"

void Cyphering::setCyph(Input Key,
                               Input Text_to_code,
                               array<string, 26> Codetable) {
  key = Key;
  text_to_code = Text_to_code;
  codetable = Codetable;
}

Cyphering::Cyphering(Input Key,
                            Input Text_to_code,
                            array<string, 26> Codetable) {
  setCyph(Key, Text_to_code, Codetable);
}

string Cyphering::cypher() {
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
}