#include "dictionary.h"

#include <z/core.hpp>
#include <z/file/exceptions.hpp>

#include <fstream>
#include <iostream>
#include <cmath>

using namespace z::core;

z::util::dictionary dict;

zstring randomAlphabet()
{
  auto output = split(ALPHABET, ""_u8);

  return join(output.shuffled(), "");
}

zstring shiftAlphabet(int offset)
{
  offset = offset % 26;

  if (offset <= 0)
    offset = offset + 26;

  return ALPHABET.substr(offset, 26) + ALPHABET.substr(0, offset);
}

void loadDictionary()
{
  if (dict.length() > 0)
    return;

  dict.read("src/words.txt");
}

float spellCheck(zstring text)
{
  loadDictionary();

  float successes = 0;
  array<zstring> words = split(text, zstring(" "));
  float total = float(words.length());

  for (int i = 0; i < words.length(); i++)
  {
    zstring word = words[i].filter({{'a', 'z'}, {'A', 'Z'}}).lower();

    if (dict.isWord(word))
      successes++;
  }

  return round(10'000 * (successes / total)) / 100;
}

zstring wordSearch(zstring input)
{
  loadDictionary();

  // First pass, greedy longest-first search for word options
  zstring output = "";
  int i = 0;
  bool midIsland = false;

  while (i < input.length())
  {
    bool wordFound = false;

    for (auto k : range(dict.maxWordLength(), 0, -1))
    {
      zstring word = input.substr(i, k);

      if (dict.isWord(word))
      {
        output.append(" "_u8 + word);

        i += k;
        wordFound = true;
        midIsland = false;
        break;
      }
    }

    if (!wordFound)
    {
      output.append(zstring(midIsland ? "" : " ") + input.substr(i++, 1));
      midIsland = true;
    }
  }

  // Second pass, correct for the greed errors
  array<zstring> words = split(output.trim(), " "_u8);

  for (int i = 0; i < words.length() - 1; i++)
  {
    if (dict.isWord(words[i]) && !dict.isWord(words[i + 1]))
    {
      zstring combo = words[i] + words[i + 1];

      // Try every way of putting a space between these two words until they're both real words
      for (int j = combo.length() - 1; j >= 1; j--)
      {
        zstring subA = combo.substr(0, j);
        zstring subB = combo.substr(j, combo.length() - j);

        if (dict.isWord(subA) && dict.isWord(subB))
        {
          words.replace(i, 1, subA);
          words.replace(i + 1, 1, subB);
        }
      }
    }
  }

  // Fix punctuation
  zstring result = join(words, " ");

  array<char> punc = {'.', ',', '\'', ':'};
  for (char p : punc)
    result.replace(" "_u8 + p, p);

  result.replace(" - ", "-");
  result.replace("( ", "(");
  result.replace(" )", ")");

  // TODO: Some of these above conditions need to be accounted for in spellcheck

  return result;
}

zstring removeSpaces(zstring text)
{
  return text.replace(" ", "");
}
