#ifndef PARSER_H
#define PARSER_H

#include "../../ext/argparse.h"
#include <z/core/string.hpp>
#include <z/core/array.hpp>

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

// template <typename T>
// zstring processResults(z::core::array<T> results, bool verbose = false);

#endif
