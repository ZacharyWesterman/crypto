#include "substitution.h"
#include "../libs/dictionary.h"

#include <iostream>

zstring substitutionEncode(zstring input, zstring key)
{
  return input.cipher(getAlphabet(), key.toLower())
      .cipher(getAlphabet().upper(), key.upper());
}

zstring substitutionDecode(zstring input, zstring key)
{
  return input.cipher(key.toLower(), getAlphabet())
      .cipher(key.upper(), getAlphabet().upper());
}

z::core::array<substitutionCrackResult> substitutionCrack(zstring input)
{
  // TODO: Implement
  return z::core::array<substitutionCrackResult>();
}