#include "caesar.h"
#include "../libs/dictionary.h"
#include "../libs/file.h"

#include <z/core/timer.hpp>

#include <iostream>

zstring caesarEncode(zstring input, int offset)
{
  return input.cipher(getAlphabet(), shiftAlphabet(offset))
      .cipher(getAlphabet().upper(), shiftAlphabet(offset).upper());
}

zstring caesarEncode(zstring input)
{
  return caesarEncode(input, rand() % 25 + 1);
}

zstring caesarDecode(const zstring &input, int offset)
{
  return input.cipher(shiftAlphabet(offset), getAlphabet())
      .cipher(shiftAlphabet(offset).upper(), getAlphabet().upper());
}

z::core::array<caesarCrackResult> caesarCrack(zstring input) // TODO: Find a 100+ character input to test this
{
  caesarCrackResult bestResult;
  z::core::array<caesarCrackResult> results;

  if (input.length() <= 100)
  {
    loadDictionary();

    "Cracking cipher"_u8.write(std::cout);

    for (int i = 1; i <= 25; i++)
    {
      caesarCrackResult newResult;

      newResult.key = i;
      zstring output = caesarDecode(input, i);
      newResult.text = output.contains(" ") ? output : wordSearch(output);
      newResult.score = checkSpelling(newResult.text);
      newResult.summary = zstring(newResult.key) + ": " + zstring(newResult.text).substr(0, 30) + "... " + newResult.score + "%\n";

      "."_u8.write(std::cout);

      if (newResult.score > bestResult.score || i == 1)
        bestResult = newResult;

      results.append(newResult);
    }

    "Done!"_u8.writeln(std::cout);

    if (bestResult.key != 1)
      results.swap(0, bestResult.key - 1);

    return results;
  }
  else
  {
    results = caesarCrack(input.substr(0, 100));

    caesarCrackResult newBest{
        .text = caesarDecode(input, results[0].key),
        .score = results[0].score,
        .key = results[0].key,
        .summary = results[0].summary,
    };

    results.replace(0, 1, newBest);
    // results[0].text = caesarDecode(input, results[0].key);

    return results;
  }
}
