#include "../../src/helpers/dictionary.h"

#include <z/all.hpp>
#include <iostream>

using namespace std;

void deleteMessage(zstring message, ostream &os)
{
  for (int i : z::core::range(message.length()))
    os << "\b \b" << flush;
}

// TODO: Can this read the screen width and do some math?
zstring loadingBar(float progress, int size = 102)
{
  size -= 2;

  zstring bar = "[";

  for (int i : z::core::range(size))
    bar += i < progress * size ? "#" : " ";

  return bar + "]";
}

// FIXME: This needs to be cleaned up
void analyze(std::function<float(zstring)> evaluator, bool skipRead = false)
{
  if (skipRead)
  {
    zstring message;
    // float total = 200;
    float total = 31603;
    z::core::array<zstring> result;

    ("  Generating "_zs + total + " random paragraphs... ").write(cerr);

    for (int i : z::core::range(total)) // roughly the number of paragraphs
    {
      if (i % 50 == 0 || i == total)
      {
        deleteMessage(message, cerr);

        float progress = i / total;
        zstring p = zstring(((int)(progress * 1000)) / 10.0);
        if (!p.count('.'))
          p += ".0";

        // FIXME: Maybe we can wrap it into the loading bar and make it something cool
        // zstring p = zstring::precision(i / total * 100, 1);

        message = loadingBar(progress) + " " + p + "%";
        message.write(cerr);
      }

      result.push(evaluator(""));
    }

    deleteMessage(message, cerr);

    cerr << loadingBar(1) + " Done!" << endl;

    z::core::join(result, ',').writeln(cout);

    cerr << endl;
    return;
  }

  for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
  // for (auto id : z::core::array<zstring>{"5", "6"})
  {
    zstring message;
    auto lines = z::file::lines("src/data/wiki/wiki"_zs + id + ".txt").collect();
    double total = lines.length();

    ("  Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ").write(cerr);

    int i = 0;
    z::core::array<zstring> result;

    for (auto line : lines)
    {
      if (++i % 50 == 0 || i == total)
      {
        deleteMessage(message, cerr);

        float progress = i / total;
        zstring p = zstring(((int)(progress * 1000)) / 10.0);
        if (!p.count('.'))
          p += ".0";

        // zstring p = zstring::precision(i / total * 100, 1);

        message = loadingBar(progress) + " " + p + "%";
        message.write(cerr);
      }

      result.push(evaluator(line.trim()));
    }

    deleteMessage(message, cerr);

    cerr << loadingBar(1) + " Done!" << endl;

    z::core::join(result, ',').writeln(cout);
  }
  cerr << endl;
}
