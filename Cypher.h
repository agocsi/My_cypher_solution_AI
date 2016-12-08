#pragma once
#include <array>

typedef std::array<std::string, 26> ctable;

class Input;

// Inputs with the used codetable to do the actual cyphering
class Cyphering {
 private:
  const Input& key;
  const Input& text_to_code;
  const ctable& codetable;

 public:
  Cyphering(const Input& Key,
            const Input& Text_to_code,
            const ctable& Codetable);

  std::string cypher();
};
// Read the codetable from the provided file
ctable read_codefile(std::string path);