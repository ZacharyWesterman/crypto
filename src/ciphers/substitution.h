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

zstring substitutionEncode(const zstring &input, zstring key = "");

zstring substitutionDecode(const zstring &input, zstring key);

z::core::array<substitutionCrackResult> substitutionCrack(const zstring &input);

#endif