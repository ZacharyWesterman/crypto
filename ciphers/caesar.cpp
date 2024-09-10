#include "caesar.h"
#include "../tools/dictionary.h"
#include "../tools/helper.h"

#include <z/core/timer.hpp>

#include <iostream>

zstring caesarEncode(zstring input, int offset)
{
  zstring alphabet = getAlphabet();

  return input.cipher(alphabet, shiftAlphabet(offset))
      .cipher(alphabet.upper(), shiftAlphabet(offset).upper());
}

zstring caesarDecode(zstring input, int offset)
{
  zstring alphabet = getAlphabet();

  return input.cipher(shiftAlphabet(offset), alphabet)
      .cipher(shiftAlphabet(offset).upper(), alphabet.upper());
}

caesarCrackResult caesarCrack(zstring input)
{
  z::core::timer timer;
  caesarCrackResult result;
  bool verbose = false;

  loadDictionary();

  ("Cracking cipher"_u8 + (verbose ? "...\n\n" : "")).write(std::cout);

  for (int i = 1; i <= 25; i++)
  {
    zstring guess = caesarDecode(input, i);
    float score = checkSpelling(guess);

    (verbose ? zstring(guess) + " " + score + "%\n" : "."_u8).write(std::cout);

    if (score > result.score)
    {
      result.score = score;
      result.text = guess;
      result.key = i;
    }
  }

  ((verbose ? "\n"_u8 : " "_u8) + "Done!\n"_u8).writeln(std::cout);

  result.summary = (result.score ? "The best solution ("_u8 + result.score + "% confidence with a key of " + result.key + ", in " + timer.micros() / 1000.0 + "ms) is:\n  " + result.text : "No solution found!");

  return result;
}

int runCaesar(int argc, char **argv)
{
  if (argc == 2)
    return basicError("No command given!");

  zstring command = argv[2];
  if (command == "encode")
  {
    if (argc < 5)
      return basicError("Needs both a key and an input!");

    int key = std::stoi(argv[3]);
    zstring input = getInput(argc, argv, 4);

    caesarEncode(input, key).writeln(std::cout);
  }
  else if (command == "decode")
  {
    if (argc < 5)
      return basicError("Needs both a key and an input!");

    int key = std::stoi(argv[3]);
    zstring input = getInput(argc, argv, 4);

    caesarDecode(input, key).writeln(std::cout);
  }
  else if (command == "crack")
  {
    if (argc < 4)
      return basicError("Needs something to crack!");

    zstring input = getInput(argc, argv, 3);

    caesarCrack(input).summary.writeln(std::cout);
  }
  else
    return basicError("Unknown command!");

  return 0;
}
