#include "helper.h"

#include <fstream>
#include <iostream>

zstring getAlphabet()
{
  return "abcdefghijklmnopqrstuvwxyz";
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
  {
    contents.append(zstring(buffer.c_str()));
  }

  ("."_u8 + contents + ".").writeln(std::cout);

  return contents;
}

std::string joinString(const std::vector<std::string> &lst, const std::string &delim)
{
  std::string ret;

  for (const auto &s : lst)
  {
    if (!ret.empty())
    {
      ret += delim;
    }

    ret += s;
  }

  return ret;
}

zstring shiftAlphabet(int offset)
{
  zstring alphabet = getAlphabet();

  return alphabet.substr(offset, 26) + alphabet.substr(0, offset);
}
