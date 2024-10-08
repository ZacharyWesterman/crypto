#include "../../src/helpers/dictionary.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

void analyze(std::function<float(zstring)> evaluator, bool random = false)
{
#define TESTING
  if (random)
  {
#ifdef TESTING
    float total = 1000;
#else
    float total = 31603;
#endif
    z::core::array<zstring> result;
    z::util::progress loadingBar;
    for (int i : z::core::range(total))
    {
      result.push(evaluator(""));
      loadingBar.set(std::cerr, i, total, "  Generating "_zs + total + " random paragraphs... ");
    }

    z::core::join(result, ',').writeln(cout);

    return;
  }

#ifdef TESTING
  for (auto id : z::core::array<zstring>{"Short"})
#else
  for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
#endif
  {
    auto lines = z::file::lines("src/data/wiki/wiki"_zs + id + ".txt").collect();
    double total = lines.length();

    z::core::array<zstring> result;
    z::util::progress loadingBar;
    for (int i=0; i < lines.length(); i++)
    {
      result.push(evaluator(lines[i].trim()));
      loadingBar.set(std::cerr, i, total, "  Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ");
    }

    z::core::join(result, ',').writeln(cout);
  }
}
