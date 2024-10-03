#include "../../src/helpers/dictionary.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

struct LoadingBar
{
  int length;
  bool showPercent;
  ostream &os;
  zstring message;

  LoadingBar(int _length = 102, ostream &_os = cout, bool _showPercent = true) : length(_length - 2), showPercent(_showPercent), os(_os), message("") {};

  void clear()
  {
    for (int i : z::core::range(message.length()))
      os << "\b \b" << flush;
  }

  zstring getBar(float progress)
  {
    zstring bar = "[";

    for (int i : z::core::range(length))
      bar += i < progress * length ? "#" : " ";

    return bar + "]";
  }

  zstring getPercentage(float progress)
  {
    zstring p;

    if (progress == 1)
    {
      p += "Done!";
    }
    else
    {
      p += zstring(((int)(progress * 1000)) / 10.0);

      if (!p.count('.'))
        p += ".0";

      p += "%";
    }

    return p;
  }

  void update(float progress = 1)
  {
    clear();

    message = getBar(progress);

    if (showPercent)
      message += " "_zs + getPercentage(progress);

    message.write(os);
  }

  void finish()
  {
    update();
    message = "";
    os << endl;
  }
};

void analyze(std::function<float(zstring)> evaluator, bool random = false)
{
  LoadingBar loadingBar(102, cerr);

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

    for (int i : z::core::range(total)) // roughly the number of paragraphs
    {
      result.push(evaluator(""));

      if (i % 50 == 0)
        loadingBar.update(i / total);
    }

    loadingBar.finish();

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

    for (auto line : lines)
    {
      result.push(evaluator(line.trim()));

      if (i % 50 == 0)
        loadingBar.update(i / total);

      i++;
    }

    loadingBar.finish();

    z::core::join(result, ',').writeln(cout);
  }
}
