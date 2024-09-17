#include "file.h"

#include <fstream>
#include <iostream>

void writeFile(zstring contents, std::string filepath)
{
  std::ofstream file(filepath);

  if (file.is_open())
  {
    file << contents << std::endl;

    file.close();
    ("Written to output file: "_u8 + zstring(filepath.c_str())).writeln(std::cout);
  }
  else
  {
    "Unable to open file for writing."_u8.writeln(std::cout);
  }
}

zstring loadFile(std::string filepath)
{
  std::ifstream file;
  zstring contents = "";
  std::string buffer;

  file.open(filepath);

  if (!file)
  {
    std::cerr << "Unable to open file " << filepath;
    exit(1);
  }

  while (file >> buffer)
    contents.append(zstring(buffer.c_str()));

  return contents;
}
