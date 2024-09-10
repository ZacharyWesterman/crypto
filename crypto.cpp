#include "ciphers/caesar.h"

#include <z/core/string.hpp>
#include <z/system/stdout.hpp>

z::system::stdout console;

int main(int argc, char **argv)
{
  zstring().writeln(console);

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
