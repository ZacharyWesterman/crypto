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

z::core::array<caesarCrackResult> caesarCrack(zstring input)
{
  caesarCrackResult bestResult;
  z::core::array<caesarCrackResult> results;

  loadDictionary();

  "Cracking cipher"_u8.write(std::cout);

  for (int i = 1; i <= 25; i++)
  {
    caesarCrackResult newResult;

    newResult.key = i;
    newResult.text = caesarDecode(input, i);
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

int runCaesar(int argc, char **argv)
{
  if (argc == 2)
  {
    return basicError("No command given!");
  }

  zstring command = argv[2];
  if (command == "encode")
  {
    if (argc < 5)
    {
      return basicError("Needs both a key and an input!");
    }

    int key = std::stoi(argv[3]);
    if (key == -1)
    {
      key = rand() % 25 + 1;
    }

    zstring input = getInput(argc, argv, 4);

    caesarEncode(input, key).writeln(std::cout);
  }
  else if (command == "decode")
  {
    if (argc < 5)
    {
      return basicError("Needs both a key and an input!");
    }

    int key = std::stoi(argv[3]);
    zstring input = getInput(argc, argv, 4);

    caesarDecode(input, key).writeln(std::cout);
  }
  else if (command == "crack")
  {
    if (argc < 4)
    {
      return basicError("Needs something to crack!");
    }

    zstring input = getInput(argc, argv, 3);

    z::core::array<caesarCrackResult> results = caesarCrack(input);

    ("The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text).writeln(std::cout);

    if (results[0].score < 50)
    {
      "\nLow Confidence! Presenting alternatives...\n"_u8.writeln(std::cout);

      for (int i = 1; i < results.length(); i++)
      {
        results[i].summary.write(std::cout);
      }
    }
  }
  else
  {
    return basicError("Unknown command!");
  }

  return 0;
}
