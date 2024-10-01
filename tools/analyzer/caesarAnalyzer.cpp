#include "../../src/dictionary.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

float caesarEvaluator(zstring input)
{
  return spellCheck(wordSearch(removeSpaces(caesarEncode(input))));
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing Caesar..." << std::endl;
  analyze(caesarEvaluator);
}
