#include "ciphers/caesar.h"
#include "tools/helper.h"

#include <z/core/string.hpp>

#include <iostream>

int main(int argc, char **argv)
{
  zstring().writeln(std::cout);

  if (argc == 1)
    return basicError("No command given!");

  zstring cipher = argv[1];

  if (cipher == "caesar")
    runCaesar(argc, argv);
  else
    return basicError("Invalid command!");

  return 0;
}
