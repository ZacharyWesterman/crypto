#include "ciphers/caesar.h"
#include "ciphers/substitution.h"
#include "libs/dictionary.h"
#include "ext/argparse.h"
#include "parser/commands.h"

#include <z/core/string.hpp>

#include <iostream>
#include <time.h>

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

int main(int argc, char **argv)
{
  srand(time(0));

  argparse::ArgumentParser program("crypto", "0.0.1");

  argparse::ArgumentParser encode_command("encode");
  argparse::ArgumentParser decode_command("decode");

  addEncodeCommand(program, encode_command);
  addDecodeCommand(program, decode_command);

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
    std::string key = encode_command["--randomkey"] == true ? "" : getParserKey(encode_command).cstring(); // TODO: ADD FURTHER VALIDATION
    zstring input = getParserInput(encode_command);

    if (cipher == "caesar")
    {
      output = key == "" ? caesarEncode(input) : caesarEncode(input, std::stoi(key));
    }
    else if (cipher == "substitution" || cipher == "sub")
    {
      "sub encode called"_u8.writeln(std::cout);
    }

    handleOutput(output, encode_command);
  }
  else if (program.is_subcommand_used("decode"))
  {
    std::string cipher = decode_command.get("cipher");
    std::string key = decode_command["--unknownkey"] == true ? "" : getParserKey(decode_command).cstring(); // TODO: ADD FURTHER VALIDATION
    zstring input = getParserInput(decode_command);

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
      "sub decode called"_u8.writeln(std::cout);
    }

    handleOutput(output, decode_command);
  }
  else
  {
    std::cout << program << std::endl;
  }

  return 0;
}
