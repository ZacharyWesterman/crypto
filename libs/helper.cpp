#include "helper.h"

#include <fstream>
#include <iostream>

zstring getAlphabet()
{
  return "abcdefghijklmnopqrstuvwxyz";
}

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

std::string joinString(const std::vector<std::string> &lst, const std::string &delim)
{
  std::string ret;

  for (const auto &s : lst)
  {
    if (!ret.empty())
      ret += delim;

    ret += s;
  }

  return ret;
}

zstring shiftAlphabet(int offset)
{
  zstring alphabet = getAlphabet();

  return alphabet.substr(offset, 26) + alphabet.substr(0, offset);
}
