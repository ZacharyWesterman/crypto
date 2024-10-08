#include "../../src/helpers/dictionary.h"
#include "analyzeHelper.h"

#include <z/core/string.hpp>
#include <iostream>

float spellCheckEvaluator(zstring input)
{
  return spellCheck(input.trim());
}

int main(int argc, char *argv[])
{
  std::cerr << "Analyzing SpellCheck..." << std::endl;
  analyze(spellCheckEvaluator);
}
