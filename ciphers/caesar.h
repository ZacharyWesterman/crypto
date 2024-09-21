#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <iostream>

#include "../libs/dictionary.h"

// TODO: Can this be generalized to the point of there only being one
//  struct between all the ciphers?

class missingText : public std::exception
{
public:
  std::string what()
  {
    return "Need to define the text first!";
  }
};

struct caesarCrackResult
{
  zstring text;
  int key;
  zstring summary;
  float score;

  caesarCrackResult() : text(), key(0), summary(), score(0.f)
  {
  }

  caesarCrackResult(const zstring &text, int key) : text(text), key(key)
  {
    if (!text)
    {
      throw missingText();
    }

    score = checkSpelling(text);

    summary = zstring(key) + ": " + text.substr(0, 30) + "... " + score + "%\n";
  }
};

zstring caesarEncode(zstring input, int offset);
zstring caesarEncode(zstring input);

zstring caesarDecode(const zstring &input, int offset);

z::core::array<caesarCrackResult> caesarCrack(zstring input);

#endif
