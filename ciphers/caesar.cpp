#include "caesar.h"
#include "../tools/dictionary.h"
#include "../tools/helper.h"

#include <z/core/timer.hpp>

#include <iostream>

zstring caesarEncode(zstring input, int offset) // TODO: guard on offset?
{
  zstring alphabet = getAlphabet(); // TODO: this kinda sucks...

  return input.cipher(alphabet, shiftAlphabet(offset))
      .cipher(alphabet.upper(), shiftAlphabet(offset).upper());
}

zstring caesarDecode(zstring input, int offset)
{
  zstring alphabet = getAlphabet();

  return input.cipher(shiftAlphabet(offset), alphabet)
      .cipher(shiftAlphabet(offset).upper(), alphabet.upper());
}

z::core::array<caesarCrackResult> caesarCrack(zstring input) // TODO: possibly crack only the first K terms instead of the whole thing, then apply thr transformation and (maybe) reconfirm
{
  caesarCrackResult bestResult;
  z::core::array<caesarCrackResult> results;

  loadDictionary();

  "Cracking cipher"_u8.write(std::cout);

  for (int i = 1; i <= 25; i++)
  {
    caesarCrackResult newResult;

    newResult.key = i;
    newResult.text = wordSearch(caesarDecode(input, i));
    newResult.score = checkSpelling(newResult.text);
    newResult.summary = zstring(i) + ": " + zstring(newResult.text).substr(0, 30) + "... " + newResult.score + "%\n";

    "."_u8.write(std::cout);

    if (newResult.score > bestResult.score || i == 1)
    {
      bestResult = newResult;
    }

    results.append(newResult);
  }

  "Done!\n"_u8.writeln(std::cout);

  if (bestResult.key != 1)
  {
    caesarCrackResult swap = results[0];
    results.replace(0, 1, bestResult);
    results.replace(bestResult.key - 1, 1, swap);
  }

  return results;
}
