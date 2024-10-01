#ifndef PARSER_H
#define PARSER_H

#include "../ext/argparse.h"
#include <z/core/string.hpp>
#include <z/core/array.hpp>

struct commandDetails
{
  std::string mainStub;

  std::string randomKeyName;
  std::string randomkeyDescription;
};

void addCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command, commandDetails cStruct);

zstring getInput(argparse::ArgumentParser &parser);

zstring getKey(argparse::ArgumentParser &parser, std::string keyFlagName);

void handleOutput(zstring output, argparse::ArgumentParser &parser);

// template <typename T>
// zstring processResults(z::core::array<T> results, bool verbose = false);

#endif
