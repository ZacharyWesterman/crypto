#include "ciphers/caesar.h"
#include "tools/helper.h"

#include <z/core/string.hpp>

#include <iostream>

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

int main(int argc, char **argv)
{
  zstring().writeln(std::cout);

  if (argc == 1)
  {
    return basicError("No command given!");
  }

  zstring cipher = argv[1];

  if (cipher == "caesar")
  {
    runCaesar(argc, argv);
  }
  else
  {
    return basicError("Invalid command!");
  }

  return 0;
}
