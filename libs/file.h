#ifndef FILE_H
#define FILE_H

#include <z/core/string.hpp>

class FileWriteError : public std::runtime_error
{
public:
  FileWriteError() : std::runtime_error("Unable to open file for writing.") {}
};

class FileReadError : public std::runtime_error
{
public:
  FileReadError() : std::runtime_error("Unable to open file for reading.") {}
};

bool writeFile(zstring contents, std::string filepath);

zstring loadFile(std::string filepath);

#endif