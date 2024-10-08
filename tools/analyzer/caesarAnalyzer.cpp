#include "../../src/helpers/dictionary.h"
#include "../../src/ciphers/caesar.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

float caesarEvaluator(zstring input)
{
  int key = rand() % 25 + 1;
  return spellCheck(wordSearch(removeSpaces(caesarEncode(input, key))));
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing Caesar..." << std::endl;
  analyze(caesarEvaluator);
}
