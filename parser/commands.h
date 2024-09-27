#ifndef COMMANDS_H
#define COMMANDS_H

#include "../ext/argparse.h"
#include <z/core/string.hpp>

void addEncodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command);

void addDecodeCommand(argparse::ArgumentParser &program, argparse::ArgumentParser &command);

zstring getInput(argparse::ArgumentParser &parser);

zstring getKey(argparse::ArgumentParser &parser, std::string keyFlagName);

void handleOutput(zstring output, argparse::ArgumentParser &parser);

#endif
