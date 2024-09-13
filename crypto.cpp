#include "ciphers/caesar.h"
#include "tools/helper.h"
#include "tools/dictionary.h"
#include "tools/argparse.h"

#include <z/core/string.hpp>

#include <iostream>

int runCaesar(int argc, char **argv)
{
  if (argc == 2)
  {
    return basicError("No command given!");
  }

  zstring command = argv[2];
  if (command == "encode")
  {
    // if (argc < 5)
    // {
    //   return basicError("Needs both a key and an input!");
    // }

    // int key = std::stoi(argv[3]);

    // if (key == -1)
    // {
    //   key = rand() % 25 + 1;
    // }

    // zstring input = getInput(argc, argv, 4);

    // caesarEncode(input, key).writeln(std::cout);
  }
  else if (command == "decode")
  {
    // if (argc < 5)
    // {
    //   return basicError("Needs both a key and an input!");
    // }

    // int key = std::stoi(argv[3]);
    // zstring input = getInput(argc, argv, 4);

    // caesarDecode(input, key).writeln(std::cout);
  }
  else if (command == "crack")
  {
    if (argc < 4)
    {
      return basicError("Needs something to crack!");
    }

    zstring input = getInput(argc, argv, 3);

    z::core::array<caesarCrackResult> results = caesarCrack(input);

    ("The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text).writeln(std::cout);

    if (results[0].score < 50)
    {
      "\nLow Confidence! Presenting alternatives...\n"_u8.writeln(std::cout);

      for (int i = 1; i < results.length(); i++)
      {
        results[i].summary.write(std::cout);
      }
    }
  }
  else
  {
    return basicError("Unknown command!");
  }

  return 0;
}

int main2(int argc, char **argv)
{
  zstring().writeln(std::cout);

  if (argc == 1)
  {
    return basicError("No command given!");
  }

  zstring cipher = argv[1];

  if (cipher == "caesar")
  {
    runCaesar(argc, argv);
  }
  else if (cipher == "test")
  {
    ("\n  "_u8 + wordSearch(argv[2])).writeln(std::cout);
  }
  else
  {
    return basicError("Invalid command!");
  }

  return 0;
}

int main(int argc, char **argv)
{
  argparse::ArgumentParser program("crypto");

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
      .help("the key filepath to use for the encoding");

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
      .help("the key filepath to use for the decoding");

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

  if (program.is_subcommand_used("encode"))
  {
    zstring cipher = zstring(encode_command.get("cipher").c_str());
    zstring key = zstring((encode_command.present("--key") ? encode_command.get("--key") : encode_command.get("--keyfile")).c_str());
    zstring input = zstring((encode_command.present("--inputfile") ? encode_command.get("--inputfile") : joinString(encode_command.get<std::vector<std::string>>("input"), " ")).c_str());

    if (cipher == "caesar")
    {
      int offset = int(key);
      if (offset == -1)
      {
        offset = rand() % 25 + 1;
      }

      ("\n"_u8 + caesarEncode(input, offset)).writeln(std::cout);
    }

    if (encode_command.present("--outputfile"))
    {
      "File output not yet implemented"_u8.writeln(std::cout);
    }
  }
  else if (program.is_subcommand_used("decode"))
  {
    zstring cipher = zstring(decode_command.get("cipher").c_str());
    zstring key = zstring((decode_command.present("--key") ? decode_command.get("--key") : decode_command.get("--keyfile")).c_str());
    zstring input = zstring((decode_command.present("--inputfile") ? decode_command.get("--inputfile") : joinString(decode_command.get<std::vector<std::string>>("input"), " ")).c_str());

    if (cipher == "caesar")
    {
      int offset = int(key);
      if (offset == -1)
      {
        offset = rand() % 25 + 1;
      }

      ("\n"_u8 + caesarDecode(input, offset)).writeln(std::cout);
    }

    if (encode_command.present("--outputfile"))
    {
      "File output not yet implemented"_u8.writeln(std::cout);
    }
  }
  else if (program.is_subcommand_used("crack"))
  {
    zstring cipher = zstring(crack_command.get("cipher").c_str());
    zstring input = zstring((crack_command.present("--inputfile") ? crack_command.get("--inputfile") : joinString(crack_command.get<std::vector<std::string>>("input"), " ")).c_str());

    if (cipher == "caesar")
    {
      z::core::array<caesarCrackResult> results = caesarCrack(input);

      ("The best solution ("_u8 + results[0].score + "% confidence with a key of " + results[0].key + ") is:\n  " + results[0].text).writeln(std::cout);

      if (results[0].score < 50)
      {
        "\nLow Confidence! Presenting alternatives...\n"_u8.writeln(std::cout);

        for (int i = 1; i < results.length(); i++)
        {
          results[i].summary.write(std::cout);
        }
      }
    }

    if (crack_command.present("--outputfile"))
    {
      "File output not yet implemented"_u8.writeln(std::cout);
    }
  }
  else
  {
    std::cout << program;
  }

  return 0;
}
