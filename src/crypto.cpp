#include "../libs/argparse.h"

#include "ciphers/caesar.h"
#include "ciphers/substitution.h"
#include "helpers/dictionary.h"
#include "helpers/parser.h"

#include <z/core/string.hpp>
#include <z/file/write.hpp>

#include <fstream>
#include <iostream>
#include <time.h>

int main(int argc, char **argv)
{
  // General Setup
  srand(time(0));

  // Program Setup (see parser.cpp/h)
  argparse::ArgumentParser program("crypto", "0.0.1");
  setupProgram(program);

  // Main code
  zstring output;
  programArgs args = parse(program, argc, argv); // to hold the re-parsed args from the parser as a nice struct

  if (args.failed)
    return 1;

  if (args.encoding)
  {
    if (args.cipher == "caesar")
    {
      args.key = args.key == "" ? std::to_string(rand() % 25 + 1) : args.key;
      output = caesarEncode(args.input, args.key);
    }
    else if (args.cipher == "substitution" || args.cipher == "sub")
    {
      args.key = args.key == "" ? randomAlphabet().cstring() : args.key;
      output = substitutionEncode(args.input, args.key);
    }

    if (args.verbose)
      output += " key="_zs + args.key;
  }
  else if (!args.encoding)
  {
    if (args.cipher == "caesar")
      output = args.key == "" ? processResults(caesarCrack(args.input), args.verbose)
                              : caesarDecode(args.input, args.key);
    else if (args.cipher == "substitution" || args.cipher == "sub")
      output = args.key == "" ? "Not yet implemented" : substitutionDecode(args.input, args.key);

    if (!output.contains(" "))
      output = wordSearch(output);
  }

  if (args.rsFlag)
    output = removeSpaces(output);

  if (args.filename.length() > 0)
    z::file::write(output, args.filename);
  else
    output.writeln(std::cout);

  return 0;
}
