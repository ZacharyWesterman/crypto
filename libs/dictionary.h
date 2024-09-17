#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <z/util/dictionary.hpp>

void loadDictionary();

float checkSpelling(zstring text);

zstring wordSearch(zstring text);

zstring getAlphabet();

zstring shiftAlphabet(int offset);

#endif
