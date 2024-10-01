#include "ext/argparse.h"

#include "src/ciphers/caesar.h"
#include "src/ciphers/substitution.h"
#include "src/dictionary.h"
#include "src/parser.h"

#include <z/core/string.hpp>

#include <fstream>
#include <iostream>
#include <time.h>

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

  return "\n"_u8 + output.trim() + "\n"; // HACK: What are the actual newline locations?
}

// TODO: Can this file be covered by tests?

commandDetails encodeStruct = {"encod", "randomkey", "a random key will be used"};
commandDetails decodeStruct = {"decod", "unknownkey", "the cipher will be cracked"};

int main(int argc, char **argv)
{
  srand(time(0));

  argparse::ArgumentParser program("crypto", "0.0.1");

  argparse::ArgumentParser encodeCommand("encode");
  argparse::ArgumentParser decodeCommand("decode");
  argparse::ArgumentParser test("test");

  addCommand(program, encodeCommand, encodeStruct);
  addCommand(program, decodeCommand, decodeStruct);

  test.add_description("run our sandbox code");
  program.add_subparser(test);

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

  zstring output;
  // TODO: Make this pointer stuff work so I can bring things out of loops
  // OR create a function and a struct for parser args that I can declare here
  // and update below to pass that struct of relevant info instead of the whole parser

  // argparse::ArgumentParser *parser;

  if (program.is_subcommand_used("encode"))
  {
    argparse::ArgumentParser &parser = program.at<argparse::ArgumentParser>("encode");

    std::string cipher = parser.get("cipher");
    std::string key = getKey(parser, "randomkey");
    zstring input = getInput(parser);
    bool rsFlag = parser["--removespaces"] == true;

    if (cipher == "caesar")
      output = caesarEncode(input, key);
    else if (cipher == "substitution" || cipher == "sub")
      output = substitutionEncode(input, key);

    if (rsFlag)
      output = removeSpaces(output);

    handleOutput(output, parser);

    return 0;
  }
  else if (program.is_subcommand_used("decode"))
  {
    argparse::ArgumentParser &parser = program.at<argparse::ArgumentParser>("decode");

    std::string cipher = parser.get("cipher");
    std::string key = getKey(parser, "unknownkey");
    zstring input = getInput(parser);
    bool rsFlag = parser["--removespaces"] == true;
    bool verbose = parser["--verbose"] == true;

    if (cipher == "caesar")
      output = key == "" ? processResults(caesarCrack(input), verbose)
                         : caesarDecode(input, key);
    else if (cipher == "substitution" || cipher == "sub")
      output = key == "" ? "Not yet implemented" : substitutionDecode(input, key);

    if (!output.contains(" "))
      output = wordSearch(output);

    if (rsFlag)
      output = removeSpaces(output);

    handleOutput(output, parser);

    return 0;
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

  return 0;
}
