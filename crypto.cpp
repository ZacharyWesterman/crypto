#include "ext/argparse.h"

#include "src/ciphers/caesar.h"
#include "src/ciphers/substitution.h"
#include "src/helpers/dictionary.h"
#include "src/helpers/parser.h"

#include <z/core/string.hpp>
#include <z/file/write.hpp>

#include <fstream>
#include <iostream>
#include <time.h>

// TODO: Can this file be covered by tests? (program.parse_args())
// TODO: any random encode call will not tell you the key (how should we handle this?)

template <typename T>
zstring processResults(z::core::array<T> results, bool verbose)
{
  if (!verbose)
    return results[0].text;

  zstring output = "";

  output += "The best solution ("_u8 + results[0].score +
            "% confidence with a key of " + results[0].key + ") is:\n  " +
            results[0].text + "\n";

  if (results[0].score < 80)
  {
    output += "\nLow Confidence! Presenting alternatives...\n\n";

    for (int i = 1; i < results.length(); i++)
      output += results[i].summary;
  }

  return output;
}

// TODO: Should these keynames really be different...? It'd be a lot nicer if they weren't...
commandDetails encodeStruct = {"encod", "randomkey", "a random key will be used"};
commandDetails decodeStruct = {"decod", "unknownkey", "the cipher will be cracked"};

int main(int argc, char **argv)
{
  // General Setup
  srand(time(0));

  // Program Setup (argparse, subcommands, etc; see parser.cpp/h)
  argparse::ArgumentParser program("crypto", "0.0.1");

  argparse::ArgumentParser encodeCommand("encode");
  argparse::ArgumentParser decodeCommand("decode");
  argparse::ArgumentParser test("test");

  addCommand(program, encodeCommand, encodeStruct);
  addCommand(program, decodeCommand, decodeStruct);

  test.add_description("run our sandbox code");
  program.add_subparser(test);

  // Try to actually get the args from the user
  try
  {
    program.parse_args(argc, argv);
  }
  catch (const std::exception &err)
  {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  // Main code
  zstring output;
  parserArgs args; // to hold the re-parsed args from the parser as a nice struct

  if (program.is_subcommand_used("encode"))
  {
    args = parse(program.at<argparse::ArgumentParser>("encode"), "randomkey");

    if (args.cipher == "caesar")
      output = caesarEncode(args.input, args.key);
    else if (args.cipher == "substitution" || args.cipher == "sub")
      output = substitutionEncode(args.input, args.key);
  }
  else if (program.is_subcommand_used("decode"))
  {
    args = parse(program.at<argparse::ArgumentParser>("decode"), "unknownkey");

    if (args.cipher == "caesar")
      output = args.key == "" ? processResults(caesarCrack(args.input), args.verbose)
                              : caesarDecode(args.input, args.key);
    else if (args.cipher == "substitution" || args.cipher == "sub")
      output = args.key == "" ? "Not yet implemented" : substitutionDecode(args.input, args.key);

    if (!output.contains(" "))
      output = wordSearch(output);
  }
  else if (program.is_subcommand_used("test")) // Test code goes here
  {
    wordSearch("testingonetwothree");

    return 0;
  }
  else
  {
    std::cout << program << std::endl;

    return 0;
  }

  // If we made it here, we weren't testing or showing the no-args output
  // So let's clean up the output and put it where the user asked
  if (args.rsFlag)
    output = removeSpaces(output);

  if (args.filename != "")
    z::file::write(output, args.filename);
  else
    output.writeln(std::cout);

  return 0;
}
