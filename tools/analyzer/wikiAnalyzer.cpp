#include "../../src/helpers/dictionary.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

float wikiEvaluator(zstring input)
{
  return spellCheck(wordSearch(removeSpaces(input.trim())));
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing Wiki..." << std::endl;
  analyze(wikiEvaluator);
}
