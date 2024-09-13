#include "ciphers/caesar.h"
#include "tools/helper.h"
#include "tools/dictionary.h"
#include "libs/argparse.h"

#include <z/core/string.hpp>

#include <iostream>
#include <time.h>

zstring getParserInput(argparse::ArgumentParser &parser)
{
  return parser.present("--inputfile") ? loadFile(parser.get("--inputfile")) : zstring(joinString(parser.get<std::vector<std::string>>("input"), " ").c_str());
}

zstring getParserKey(argparse::ArgumentParser &parser)
{
  return parser.present("--keyfile") ? loadFile(parser.get("--keyfile")) : zstring(parser.get("--key").c_str());
}

int main(int argc, char **argv)
{
  srand(time(0));

  argparse::ArgumentParser program("crypto");

  // TODO: This is super reptitive
  // crypto encode subparser
  argparse::ArgumentParser encode_command("encode");
  encode_command.add_description("encode the input given a certain cipher and key");

  encode_command.add_argument("cipher")
      .help("the cipher to use for the encoding")
      .choices("caesar");

  encode_command.add_argument("-O", "--outputfile")
      .help("the output file name for the result");

  auto &encodeKeyGroup = encode_command.add_mutually_exclusive_group(true);
  encodeKeyGroup.add_argument("-k", "--key")
      .help("the key to use for the encoding");
  encodeKeyGroup.add_argument("-K", "--keyfile")
      .help("the key file path to use for the encoding");

  auto &encodeInputGroup = encode_command.add_mutually_exclusive_group(true);
  encodeInputGroup.add_argument("-I", "--inputfile")
      .help("specify the input file to be encoded");
  encodeInputGroup.add_argument("input")
      .help("the input to be encoded")
      .remaining();

  // crypto decode subparser
  argparse::ArgumentParser decode_command("decode");
  decode_command.add_description("Decode the input given a certain cipher and key");

  decode_command.add_argument("cipher")
      .help("the cipher to use for the decoding")
      .choices("caesar");

  decode_command.add_argument("-O", "--outputfile")
      .help("the output file name for the result");

  auto &decodeKeyGroup = decode_command.add_mutually_exclusive_group(true);
  decodeKeyGroup.add_argument("-k", "--key")
      .help("the key to use for the decoding");
  decodeKeyGroup.add_argument("-K", "--keyfile")
      .help("the key file path to use for the decoding");

  auto &decodeInputGroup = decode_command.add_mutually_exclusive_group(true);
  decodeInputGroup.add_argument("-I", "--inputfile")
      .help("specify the input file to be decoded");
  decodeInputGroup.add_argument("input")
      .help("the input to be decoded")
      .remaining();

  // crypto crack subparser
  argparse::ArgumentParser crack_command("crack");
  crack_command.add_description("Crack the input given a certain cipher");

  crack_command.add_argument("cipher")
      .help("the cipher to use for the decoding")
      .choices("caesar");

  crack_command.add_argument("-O", "--outputfile")
      .help("the output file name for the result");

  auto &crackInputGroup = crack_command.add_mutually_exclusive_group(true);
  crackInputGroup.add_argument("-I", "--inputfile")
      .help("specify the input file to be decoded");
  crackInputGroup.add_argument("input")
      .help("the input to be decoded")
      .remaining();

  program.add_subparser(encode_command);
  program.add_subparser(decode_command);
  program.add_subparser(crack_command);

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

  // Main logic control
  // TODO: This is also pretty repetitive
  if (program.is_subcommand_used("encode"))
  {
    auto cipher = encode_command.get("cipher");
    std::string key = getParserKey(encode_command).cstring();
    zstring input = getParserInput(encode_command);
    zstring output = "";

    if (cipher == "caesar")
    {
      int offset = std::stoi(key) == -1 ? (rand() % 25) + 1 : std::stoi(key);

      output = caesarEncode(input, offset);
      ("\n"_u8 + output).writeln(std::cout);
    }

    if (encode_command.present("--outputfile"))
      "File output not yet implemented"_u8.writeln(std::cout);
  }
  else if (program.is_subcommand_used("decode"))
  {
    auto cipher = decode_command.get("cipher");
    auto key = decode_command.present("--key") ? decode_command.get("--key") : decode_command.get("--keyfile");
    zstring input = getParserInput(decode_command);
    zstring output = "";

    if (cipher == "caesar")
    {
      output = caesarDecode(input, std::stoi(key));
      ("\n"_u8 + output).writeln(std::cout);
    }

    if (decode_command.present("--outputfile"))
      "File output not yet implemented"_u8.writeln(std::cout);
  }
  else if (program.is_subcommand_used("crack"))
  {
    auto cipher = crack_command.get("cipher");
    zstring input = getParserInput(crack_command);

    if (cipher == "caesar")
    {
      z::core::array<caesarCrackResult> results = caesarCrack(input);

      ("The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text).writeln(std::cout);

      if (results[0].score < 80)
      {
        "\nLow Confidence! Presenting alternatives...\n"_u8.writeln(std::cout);

        for (int i = 1; i < results.length(); i++)
          results[i].summary.write(std::cout);
      }
    }

    if (crack_command.present("--outputfile"))
      "File output not yet implemented"_u8.writeln(std::cout);
  }
  else
  {
    std::cout << program;
  }

  return 0;
}
