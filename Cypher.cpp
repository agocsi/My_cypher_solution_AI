#include "stdafx.h"
#include "Cypher.h"
#include "Input.h"
#include <fstream>

Cyphering::Cyphering(const Input& Key,
                     const Input& Text_to_code,
                     const ctable& Codetable)
    : key(Key), text_to_code(Text_to_code), codetable(Codetable){};

// THE task itself, doing the cyphering
std::string Cyphering::cypher() {
  std::string returned;
  int count = 0;
  for (char ch : text_to_code.getText()) {
    int row = 0;
    while (codetable[row].at(0) != ch) {
      row++;
    }
    size_t column = codetable[0].find(key.getText().at(count));
    returned.append(1, codetable[row].at(column));
    count++;
  }
  return returned;
}

// Read the codetable from the provided file
ctable read_codefile(std::string path) {
  std::string line;
  std::ifstream myfile(path);
  int rows = 0;
  ctable codetable;
  if (myfile.is_open()) {
    while (std::getline(myfile, line)) {
      codetable[rows] = line;
      rows++;
    }
  }
  return codetable;
}