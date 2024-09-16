#ifndef HELPER_H
#define HELPER_H

#include <z/core/string.hpp>

zstring getAlphabet();

zstring shiftAlphabet(int offset);

std::string joinString(const std::vector<std::string> &lst, const std::string &delim);

void writeFile(zstring contents, std::string filepath);

zstring loadFile(std::string filepath);

#endif