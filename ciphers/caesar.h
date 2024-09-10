#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>

zstring shiftAlphabet(int offset);

zstring caesarEncode(zstring input, int offset);

zstring caesarDecode(zstring input, int offset);

zstring getInput(int argc, char **argv, int index);

void runCaesar(int argc, char **argv);

#endif
