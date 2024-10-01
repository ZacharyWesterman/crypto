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
  return join(split(ALPHABET, ""_u8).shuffled(), "");
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

  dict.read("src/data/words.txt");
}

float spellCheck(zstring text)
{
  loadDictionary();

  float successes = 0;
  array<zstring> words = split(text, zstring(" "));
  float total = float(words.length());

  for (int i : range(words.length()))
  {
    zstring word = words[i].filter({{'a', 'z'}, {'A', 'Z'}}).lower();

    if (dict.isWord(word))
      successes++;
  }

  return round(10'000 * (successes / total)) / 100;
}

zstring greedyFindWords(zstring input)
{
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

  return output;
}

zstring reduceWordIslands(zstring input)
{
  // Second pass, correct for the greed errors
  array<zstring> words = split(input.trim(), " "_u8);

  for (int i : range(words.length() - 1))
  {
    if (dict.isWord(words[i]) && !dict.isWord(words[i + 1]))
    {
      zstring combo = words[i] + words[i + 1];

      // Try every way of putting a space between these two words until they're both real words
      // Going right-to-left to try to offset the last step's greedy left-to-right search
      for (int j : range(words.length() - 1, 0, -1))
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

  return join(words, " ");
}

zstring wordSearch(zstring input)
{
  loadDictionary();

  zstring output = greedyFindWords(input);
  output = reduceWordIslands(output);

  // fix punctuation
  array<char> punc = {'.', ',', '\'', ':'};
  for (char p : punc)
    output.replace(" "_u8 + p, p);

  output.replace(" - ", "-");
  output.replace("( ", "(");
  output.replace(" )", ")");

  return output;
}

zstring removeSpaces(zstring text)
{
  return text.replace(" ", "");
}
