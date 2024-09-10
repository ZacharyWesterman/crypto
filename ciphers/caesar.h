#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>

struct caesarCrackResult
{
  zstring text;
  float score;
  int key;
  zstring summary;
};

zstring caesarEncode(zstring input, int offset);

zstring caesarDecode(zstring input, int offset);

caesarCrackResult caesarCrack(zstring input);

int runCaesar(int argc, char **argv);

#endif
