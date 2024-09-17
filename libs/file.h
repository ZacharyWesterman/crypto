#ifndef FILE_H
#define FILE_H

#include <z/core/string.hpp>

void writeFile(zstring contents, std::string filepath);

zstring loadFile(std::string filepath);

#endif