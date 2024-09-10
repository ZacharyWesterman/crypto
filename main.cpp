#include <z/core/string.hpp>
#include <z/system/stdin.hpp>
#include <z/system/stdout.hpp>
#include <z/util/dictionary.hpp>
#include <fstream>

#include "ciphers/caesar.h"

z::system::stdout console;
z::system::stdin input;
z::util::dictionary dict;

int main(int argc, char **argv)
{

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
