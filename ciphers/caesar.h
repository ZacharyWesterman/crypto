#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/util/generic.hpp>

struct codeBreakResult
{
  zstring text;
  float score;
  int key;
};

zstring shiftAlphabet(int offset);

zstring caesarEncode(zstring input, int offset);

zstring caesarDecode(zstring input, int offset);

codeBreakResult caesarCrack(zstring input);

zstring getInput(int argc, char **argv, int index);

void runCaesar(int argc, char **argv);

#endif
