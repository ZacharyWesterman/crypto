#include "caesar.h"
#include <iostream>

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

zstring getInput(int argc, char **argv, int index)
{
  zstring input;

  for (int i = index; i < argc; i++)
  {
    input += zstring(argv[i]) + " ";
  }

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
    if (argc < 4)
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
    if (argc < 4)
    {
      std::cout << "Needs both a key and an input!" << std::flush;
      return;
    }

    zstring input = getInput(argc, argv, 4);
    int key = std::stoi(argv[3]);

    std::cout << caesarDecode(input, key) << std::flush;
  }
}
