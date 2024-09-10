#ifndef HELPER_H
#define HELPER_H

#include <z/core/string.hpp>

#include <iostream>

zstring getAlphabet();

zstring shiftAlphabet(int offset);

zstring getInput(int argc, char **argv, int index);

int basicError(zstring msg);

#endif