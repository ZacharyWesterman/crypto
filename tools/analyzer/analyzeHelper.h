#include "../../src/helpers/dictionary.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

// TODO: Split wiki into wordSearch and spellCheck

void analyze(std::function<float(zstring)> evaluator, bool random = false)
{
#define TESTING
  if (random)
  {
#ifdef TESTING
    float total = 2000;
#else
    float total = 31603;
#endif
    z::core::array<zstring> result;

    ("  Generating "_zs + total + " random paragraphs... ").write(cerr);

    z::util::progress loadingBar;
    for (int i : z::core::range(total))
    {
      result.push(evaluator(""));
      loadingBar.set(std::cerr, i, total);
    }

    z::core::join(result, ',').writeln(cout);

    return;
  }

#ifdef TESTING
  for (auto id : z::core::array<zstring>{"5", "6"})
#else
  for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
#endif
  {
    auto lines = z::file::lines("src/data/wiki/wiki"_zs + id + ".txt").collect();
    double total = lines.length();

    ("  Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ").write(cerr);

    int i = 0;
    z::core::array<zstring> result;

    z::util::progress loadingBar;
    for (auto line : lines)
    {
      result.push(evaluator(line.trim()));
      loadingBar.set(std::cerr, i, total);
      i++;
    }

    z::core::join(result, ',').writeln(cout);
  }
}
