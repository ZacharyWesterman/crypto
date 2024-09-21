#ifndef CAESAR_H
#define CAESAR_H

#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <iostream>

#include "../libs/dictionary.h"

// TODO: Can this be generalized to the point of there only being one
//  struct between all the ciphers?

class missingText : public std::runtime_error
{
public:
  missingText() : std::runtime_error("Need to define the text first!") {}
};

struct crackResult
{
  zstring text;
  zstring summary;
  float score;

  virtual void update(zstring){};

  virtual zstring getKey() const noexcept;
};

struct caesarCrackResult : public crackResult
{
  int key;

  caesarCrackResult() : key(0)
  {
    this->text = text;
    summary = 0;
    score = 0.f;
  }

  caesarCrackResult(const zstring &text, int key) : key(key)
  {
    this->text = text;

    if (!text)
      throw missingText();

    score = checkSpelling(text);

    summary = zstring(key) + ": " + text.substr(0, 30) + "... " + score + "%\n";
  }

  void update(zstring newText)
  {
    text = newText;
    score = checkSpelling(text);
  }

  zstring getKey() const noexcept override
  {
    return key;
  }
};

zstring caesarEncode(zstring input, int offset);
zstring caesarEncode(zstring input);

zstring caesarDecode(const zstring &input, int offset);

z::core::array<crackResult> caesarCrack(zstring input);

#endif
