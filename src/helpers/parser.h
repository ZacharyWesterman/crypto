#ifndef PARSER_H
#define PARSER_H

#include "../../libs/argparse.h"
#include <z/core/string.hpp>
#include <z/core/array.hpp>

struct programArgs
{
  bool failed;
  bool encoding;
  std::string cipher;
  std::string key;
  zstring input;
  std::string filename;
  bool rsFlag;
  bool verbose;

  programArgs(bool _failed) : failed(_failed), encoding(false), cipher(""), key(""), input(""), filename(""), rsFlag(false), verbose(false) {};

  programArgs(bool _failed, bool _encoding, std::string _cipher, std::string _key, zstring _input, std::string _filename, bool _rsFlag, bool _verbose) : failed(_failed), encoding(_encoding), cipher(_cipher), key(_key), input(_input), filename(_filename), rsFlag(_rsFlag), verbose(_verbose) {};
};

void setupProgram(argparse::ArgumentParser &program);

zstring getInput();

programArgs parse(argparse::ArgumentParser &program);

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

#endif
