#include "file.h"

#include <fstream>
#include <iostream>

void writeFile(zstring contents, std::string filepath)
{
  std::ofstream file(filepath);

  if (!file.is_open())
  {
    ("Unable to write to output file: "_u8 + filepath).writeln(std::cout);
    exit(1);
  }

  file << contents << std::endl;

  file.close();

  ("Written to output file: "_u8 + filepath).writeln(std::cout);
}

zstring loadFile(std::string filepath)
{
  std::ifstream file;
  zstring contents = "";
  std::string buffer = "";

  file.open(filepath);

  if (!file)
  {
    ("Unable to open output file: "_u8 + filepath).writeln(std::cout);
    exit(1);
  }

  while (file >> buffer)
    contents.append(zstring(buffer));

  return contents;
}
