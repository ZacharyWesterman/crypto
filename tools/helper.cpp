#include "helper.h"

zstring getAlphabet()
{
  return "abcdefghijklmnopqrstuvwxyz";
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

zstring getInput(int argc, char **argv, int index)
{
  zstring input;

  for (int i = index; i < argc; i++)
  {
    input += zstring(argv[i]) + " ";
  }

  return input;
}

int basicError(zstring msg)
{
  zstring(msg).writeln(std::cout);
  return 1;
}