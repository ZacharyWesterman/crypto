#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <z/util/dictionary.hpp>

#define ALPHABET zstring("abcdefghijklmnopqrstuvwxyz")

zstring randomAlphabet();

zstring shiftAlphabet(int offset);

void loadDictionary();

float spellCheck(zstring text);

zstring wordSearch(zstring text);

zstring removeSpaces(zstring text);

#endif
