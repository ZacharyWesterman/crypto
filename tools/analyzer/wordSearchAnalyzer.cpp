#include "../../src/helpers/dictionary.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

float spellCheckEvaluator(zstring input)
{
  return spellCheck(wordSearch(removeSpaces(input.trim())));
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing WordSearch..." << std::endl;
  analyze(spellCheckEvaluator);
}
