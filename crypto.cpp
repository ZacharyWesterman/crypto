#include "ciphers/caesar.h"
#include "ciphers/substitution.h"
#include "libs/dictionary.h"
#include "ext/argparse.h"
#include "parser/commands.h"

#include <z/core/string.hpp>

#include <iostream>
#include <time.h>
#include <fstream>

// TODO: Can these be covered by tests?

// TODO: In general, we need more validation on functions

template <typename T>
zstring processResults(z::core::array<T> results, bool verbose = false)
{
  if (!verbose)
    return results[0].text;

  zstring output = "";

  output += "The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text + "\n";

  if (results[0].score < 80)
  {
    output += "\nLow Confidence! Presenting alternatives...\n\n";

    for (int i = 1; i < results.length(); i++)
      output += results[i].summary;
  }

  return "\n"_u8 + output.trim() + "\n"; // HACK: What are the actual newline locations?
}

int main(int argc, char **argv)
{
  srand(time(0));

  argparse::ArgumentParser program("crypto", "0.0.1");

  argparse::ArgumentParser encode_command("encode");
  argparse::ArgumentParser decode_command("decode");
  argparse::ArgumentParser test("test");

  addEncodeCommand(program, encode_command);
  addDecodeCommand(program, decode_command);

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

  zstring output = "";

  if (program.is_subcommand_used("encode"))
  {
    std::string cipher = encode_command.get("cipher");
    std::string key = getKey(encode_command, "randomkey").cstring();
    zstring input = getInput(encode_command);

    if (cipher == "caesar")
      output = key == "" ? caesarEncode(input) : caesarEncode(input, std::stoi(key));
    else if (cipher == "substitution" || cipher == "sub")
      output = key == "" ? substitutionEncode(input) : substitutionEncode(input, key);

    if (encode_command["--removespaces"] == true)
      output = removeSpaces(output);

    handleOutput(output, encode_command);

    return 0;
  }
  else if (program.is_subcommand_used("decode"))
  {
    std::string cipher = decode_command.get("cipher");
    std::string key = getKey(decode_command, "unknownkey").cstring();
    zstring input = getInput(decode_command);

    bool hadSpaces = input.count(" ") > 0;
    bool verbose = decode_command["--verbose"] == true;

    if (cipher == "caesar")
      output = key == "" ? processResults(caesarCrack(input), verbose) : caesarDecode(input, std::stoi(key));
    else if (cipher == "substitution" || cipher == "sub")
      output = key == "" ? "Not yet implemented" : substitutionDecode(input, key);

    if (!output.contains(" "))
      output = wordSearch(output);

    if (!hadSpaces && decode_command["--preservespaces"] == true)
      output = removeSpaces(output);

    handleOutput(output, decode_command);

    return 0;
  }
  else if (program.is_subcommand_used("test"))
  {
    // Test code goes here
    wordSearch("testingonetwothree");
  }
  else
  {
    std::cout << program << std::endl;

    return 0;
  }

  return 0;
}
