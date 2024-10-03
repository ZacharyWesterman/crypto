#ifndef PARSER_H
#define PARSER_H

#include "../../ext/argparse.h"
#include <z/core/string.hpp>
#include <z/core/array.hpp>

// TODO: Allow for piped in input to be treating as the rest of of inputs?
// remember though, this wouldn't be cases for things like `cat file | ./crypto` because we already have file read support for input

struct commandDetails
{
  std::string mainStub;
  std::string randomKeyName;
  std::string randomkeyDescription;
};

struct parserArgs
{
  std::string cipher;
  std::string key;
  zstring input;
  std::string filename;
  bool rsFlag;
  bool verbose;
};

void addCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command, commandDetails cStruct);

parserArgs parse(argparse::ArgumentParser &parser, std::string keyname);

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
