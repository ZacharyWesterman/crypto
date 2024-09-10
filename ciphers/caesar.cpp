#include "caesar.h"
#include "../tools/dictionary.h"

#include <iostream>

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";

zstring shiftAlphabet(int offset)
{
  return alphabet.substr(offset, 26) + alphabet.substr(0, offset);
}

zstring caesarEncode(zstring input, int offset)
{
  input = input.cipher(alphabet, shiftAlphabet(offset));
  return input.cipher(alphabet.upper(), shiftAlphabet(offset).upper());
}

zstring caesarDecode(zstring input, int offset)
{
  input = input.cipher(shiftAlphabet(offset), alphabet);
  return input.cipher(shiftAlphabet(offset).upper(), alphabet.upper());
}

codeBreakResult caesarCrack(zstring input)
{
  codeBreakResult result;

  loadDictionary();

  std::cout << "Cracking cipher" << std::flush;

  bool verbose = false;
  if (verbose)
  {
    std::cout << "...\n"
              << std::endl;
  }

  for (int i = 1; i <= 25; i++)
  {
    zstring guess = caesarDecode(input, i);
    float score = checkSpelling(guess);

    if (verbose)
    {
      std::cout << guess << " " << score << "%"
                << std::endl;
    }
    else
    {
      std::cout << "." << std::flush;
    }

    if (score > result.score)
    {
      result.score = score;
      result.text = guess;
      result.key = i;
    }
  }

  if (verbose)
  {
    std::cout << "\n"
              << std::flush;
  }
  else
  {
    std::cout << " "
              << std::flush;
  }

  std::cout << "Done!\n"
            << std::endl;

  return result;
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

    int key = std::stoi(argv[3]);
    zstring input = getInput(argc, argv, 4);

    std::cout << caesarEncode(input, key) << std::flush;
  }
  else if (command == "decode")
  {
    if (argc < 5)
    {
      std::cout << "Needs both a key and an input!" << std::flush;
      return;
    }

    int key = std::stoi(argv[3]);
    zstring input = getInput(argc, argv, 4);

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
    codeBreakResult result = caesarCrack(input);

    if (result.score == 0)
    {
      std::cout << "No solution found." << std::endl;
    }
    else
    {
      std::cout << "The best solution is:\n"
                << result.text
                << "(" << result.score << "%) "
                << "with a key of " << result.key
                << std::endl;
    }
  }
}
