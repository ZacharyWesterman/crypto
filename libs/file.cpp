#include "file.h"

#include <fstream>
#include <iostream>

bool writeFile(zstring contents, std::string filepath)
{
  std::ofstream file(filepath);

  if (!file.is_open())
    throw FileWriteError();

  file << contents << std::endl;

  file.close();

  return true;
}

zstring loadFile(std::string filepath)
{
  std::ifstream file;
  zstring contents = "";
  std::string buffer = "";

  file.open(filepath);

  if (!file)
    throw FileReadError();

  while (std::getline(file, buffer))
  {
    contents.append(zstring(buffer));
    contents.append("\n");
  }

  return contents.substr(0, contents.length() - 1); // remove the last newline
}

// TODO: Create a generator that allows you to load one line of a file at a time
