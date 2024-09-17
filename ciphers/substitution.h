#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>

struct substitutionCrackResult
{
  zstring text;
  float score;
  int key;
  zstring summary;
};

zstring substitutionEncode(zstring input, zstring key);

zstring substitutionDecode(zstring input, zstring key);

z::core::array<substitutionCrackResult> substitutionCrack(zstring input);

#endif