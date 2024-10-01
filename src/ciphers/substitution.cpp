#include "substitution.h"
#include "../dictionary.h"

#include <iostream>

zstring substitutionEncode(const zstring &input, zstring key)
{
  if (key == "")
    key = randomAlphabet();

  return input.cipher(ALPHABET, key.toLower())
      .cipher(ALPHABET.upper(), key.upper());
}

zstring substitutionDecode(const zstring &input, zstring key)
{
  return input.cipher(key.toLower(), ALPHABET)
      .cipher(key.upper(), ALPHABET.upper());
}

z::core::array<substitutionCrackResult> substitutionCrack(const zstring &input)
{
  // TODO: Implement (depends on genetic and graphBreeding)
  return z::core::array<substitutionCrackResult>();
}