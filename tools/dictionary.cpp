#include "dictionary.h"

#include <z/core/split.hpp>
#include <z/core/array.hpp>

#include <fstream>
#include <iostream>
#include <cmath>

z::util::dictionary dict;

void loadDictionary()
{
  std::ifstream file("tools/words.txt");

  z::core::timeout time(1000000); // 1 second timeout

  "Loading dictionary..."_u8.write(std::cout);
  while (!dict.read(file, time))
  {
    '.'_u8.write(std::cout);
    time.reset();
  }

  (" Done! Loaded "_u8 + dict.length() + " words.").writeln(std::cout);
}

float checkSpelling(zstring text)
{
  float successes;

  z::core::array<zstring> words = z::core::split(text, zstring(" "));

  for (int i = 0; i < words.length(); i++)
  {
    zstring word = words[i].filter({{'a', 'z'}, {'A', 'Z'}}).lower();

    if (dict.isWord(word))
    {
      successes++;
    }
  }

  return round(10000 * (successes / float(words.length() - 1))) / 100; // todo: confirm the -1
}
