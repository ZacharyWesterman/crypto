#include "caesar.h"
#include "../libs/dictionary.h"
#include "../libs/file.h"

#include <z/core/timer.hpp>

#include <iostream>

zstring caesarEncode(zstring input, int offset) // TODO: guard on offset?
{
  return input.cipher(getAlphabet(), shiftAlphabet(offset))
      .cipher(getAlphabet().upper(), shiftAlphabet(offset).upper());
}

zstring caesarDecode(zstring input, int offset)
{
  zstring plainText = input.cipher(shiftAlphabet(offset), getAlphabet())
                          .cipher(shiftAlphabet(offset).upper(), getAlphabet().upper());

  return wordSearch(plainText);
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
    newResult.summary = zstring(newResult.key) + ": " + zstring(newResult.text).substr(0, 30) + "... " + newResult.score + "%\n";

    "."_u8.write(std::cout);

    if (newResult.score > bestResult.score || i == 1)
      bestResult = newResult;

    results.append(newResult);
  }

  "Done!\n"_u8.writeln(std::cout);

  if (bestResult.key != 1)
    results.swap(0, bestResult.key - 1);

  return results;
}
