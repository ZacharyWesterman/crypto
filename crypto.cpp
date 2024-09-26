#include "ciphers/caesar.h"
#include "ciphers/substitution.h"
#include "libs/dictionary.h"
#include "libs/file.h"
#include "ext/argparse.h"
#include "parser/commands.h"

#include <z/core/string.hpp>

#include <iostream>
#include <time.h>
#include <fstream>

// TODO: crack has a very verbose output and should have a verbose flag

template <typename T>
zstring processResults(z::core::array<T> results)
{
  zstring output = "";

  output += "The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text + "\n";

  if (results[0].score < 80)
  {
    output += "\nLow Confidence! Presenting alternatives...\n\n";

    for (int i = 1; i < results.length(); i++)
      output += results[i].summary;
  }

  return output;
}

// TODO: carefully check output for multiple commands and make sure
// we have a consistent output structure

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

  zstring().writeln(std::cout);
  zstring output = "";

  if (program.is_subcommand_used("encode"))
  {
    std::string cipher = encode_command.get("cipher");
    std::string key = getParserKey(encode_command, "randomkey").cstring();
    zstring input = getParserInput(encode_command);

    if (cipher == "caesar")
      output = key == "" ? caesarEncode(input) : caesarEncode(input, std::stoi(key));
    else if (cipher == "substitution" || cipher == "sub")
      output = key == "" ? substitutionEncode(input) : substitutionEncode(input, key);

    if (encode_command["--removespaces"] == true)
      output = removeSpaces(output);

    handleOutput(output, encode_command);
  }
  else if (program.is_subcommand_used("decode"))
  {
    std::string cipher = decode_command.get("cipher");
    std::string key = getParserKey(decode_command, "unknownkey").cstring();
    zstring input = getParserInput(decode_command);

    bool hadSpaces = input.count(" ") > 0;

    if (cipher == "caesar")
    {
      if (key == "")
      {
        output = processResults(caesarCrack(input));
      }
      else
      {
        zstring plaintext = caesarDecode(input, std::stoi(key));
        output = plaintext.contains(" ") ? plaintext : wordSearch(plaintext);
      }
    }
    else if (cipher == "substitution" || cipher == "sub")
    {
      if (key == "")
      {
        std::cout << "Not yet implemented" << std::endl;
      }
      else
      {
        zstring plaintext = substitutionDecode(input, key);
        output = plaintext.contains(" ") ? plaintext : wordSearch(plaintext);
      }
    }

    if (!hadSpaces && decode_command["--preservespaces"] == true)
      output = removeSpaces(output);

    handleOutput(output, decode_command);
  }
  else if (program.is_subcommand_used("test"))
  {
    std::ifstream file;
    zstring contents = "";
    std::string buffer = "";

    file.open("data/paragraphs.txt");

    if (!file)
      throw FileReadError();

    int i = 0;
    while (std::getline(file, buffer) && i == 0)
    {
      zstring p = zstring(buffer);
      auto result = wordSearch(removeSpaces(p));
      std::cout << '.' << result << '.' << std::endl;
      std::cout << '.' << p.trim() << '.' << std::endl;

      i++;
    }
  }
  else
  {
    std::cout << program << std::endl;
  }

  return 0;
}
