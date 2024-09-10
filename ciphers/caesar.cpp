#include "caesar.h"
#include <iostream>
#include "../dictionary.h"

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";

zstring shiftAlphabet(int offset)
{
  return alphabet.substr(offset, 26) + alphabet.substr(0, offset);
}

zstring caesarEncode(zstring input, int offset)
{
  return input.cipher(alphabet, shiftAlphabet(offset));
}

zstring caesarDecode(zstring input, int offset)
{
  return input.cipher(shiftAlphabet(offset), alphabet);
}

zstring caesarCrack(zstring input)
{
  zstring bestGuess;
  float bestScore = 0;

  loadDictionary();

  std::cout << "Testing" << std::flush;

  for (int i = 1; i <= 25; i++)
  {
    std::cout << "." << std::flush;

    zstring guess = caesarDecode(input, i);
    float score = checkSpelling(guess);

    if (score > bestScore)
    {
      bestScore = score;
      bestGuess = guess;
    }
  }

  std::cout << " Done!\n\n"
            << std::flush;

  return bestGuess;
}

zstring getInput(int argc, char **argv, int index)
{
  zstring input;

  for (int i = index; i < argc; i++)
    input += zstring(argv[i]) + " ";

  return input;
}

void runCaesar(int argc, char **argv)
{
  if (argc == 2)
  {
    std::cout << "No command given!" << std::flush;
    return;
  }

  zstring command = argv[2];
  if (command == "encode")
  {
    if (argc < 5)
    {
      std::cout << "Needs both a key and an input!" << std::flush;
      return;
    }

    zstring input = getInput(argc, argv, 4);
    int key = std::stoi(argv[3]);

    std::cout << caesarEncode(input, key) << std::flush;
  }
  else if (command == "decode")
  {
    if (argc < 5)
    {
      std::cout << "Needs both a key and an input!" << std::flush;
      return;
    }

    zstring input = getInput(argc, argv, 4);
    int key = std::stoi(argv[3]);

    std::cout << caesarDecode(input, key) << std::flush;
  }
  else if (command == "crack")
  {
    if (argc < 4)
    {
      std::cout << "Needs something to crack!" << std::flush;
      return;
    }

    zstring input = getInput(argc, argv, 3);
    zstring result = caesarCrack(input);

    std::cout << "The best solution is:\n"
              << result << std::flush;
  }
}
