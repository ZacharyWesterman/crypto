#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <z/util/dictionary.hpp>

void loadDictionary();

zstring stripNonChars(zstring text);

float checkSpelling(zstring text);

#endif
