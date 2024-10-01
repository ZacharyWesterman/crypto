#include "../../src/helpers/dictionary.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

zstring randomParagraph(int length = 200)
{
  zstring output;

  for (int i : z::core::range(length))
    output += ALPHABET[rand() % 26];

  return output;
}

float randomEvaluator(zstring input)
{
  return spellCheck(wordSearch(randomParagraph()));
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing Random..." << std::endl;
  analyze(randomEvaluator, true);
}
