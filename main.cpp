#include "ciphers/caesar.h"

#include <z/core/string.hpp>
#include <z/system/stdin.hpp>
#include <z/system/stdout.hpp>

#include <fstream>
#include <iostream>

z::system::stdout console;
z::system::stdin input;

int main(int argc, char **argv)
{
  std::cout << std::endl;

  if (argc == 1)
  {
    "No command given!"_u8.writeln(console);

    return 1;
  }

  zstring cipher = argv[1];
  if (cipher == "caesar")
  {
    runCaesar(argc, argv);
  }
  else
  {
    "Invalid command!"_u8.writeln(console);
    return 1;
  }

  return 0;
}
