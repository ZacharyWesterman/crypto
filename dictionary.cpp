#include "dictionary.h"

#include <iostream>
#include <cmath>
#include <z/core/split.hpp>
#include <z/core/array.hpp>

z::util::dictionary dict;

void loadDictionary()
{
  std::ifstream file("words.txt");

  z::core::timeout time(1000000); // 1 second timeout

  std::cout << "Loading dictionary..." << std::flush;
  while (!dict.read(file, time))
  {
    std::cout << '.' << std::flush;
    time.reset();
  }

  std::cout << " Done! Loaded " << dict.length() << " words." << std::endl;
}

zstring stripNonChars(zstring text)
{
  zstring output;

  for (int i = 0; i < text.chars(); i++)
  {
    if (std::isalpha(text[i]))
      output.append(text[i]);
  }

  return output;
}

float checkSpelling(zstring text)
{
  z::core::array<zstring> words = z::core::split(text, zstring(" "));
  float successes;

  for (int i = 0; i < words.length(); i++)
  {
    zstring word = stripNonChars(words[i]).lower();

    if (dict.isWord(word))
      successes++;
  }

  return round(10000 * (successes / float(words.length() - 1))) / 100; // todo: confirm the -1
}
