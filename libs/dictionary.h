#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <z/util/dictionary.hpp>

zstring getAlphabet();

zstring shiftAlphabet(int offset);

void loadDictionary();

float checkSpelling(zstring text);

zstring wordSearch(zstring text);

#endif
