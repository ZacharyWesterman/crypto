#ifndef COMMANDS_H
#define COMMANDS_H

#include "../ext/argparse.h"

void generateEncodeCommand(argparse::ArgumentParser &command);

void generateDecodeCommand(argparse::ArgumentParser &command);

void generateCrackCommand(argparse::ArgumentParser &command);

#endif