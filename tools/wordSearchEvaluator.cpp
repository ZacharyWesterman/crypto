#include "../libs/dictionary.h"

#include <z/all.hpp>
#include <iostream>
#include <iomanip>

using namespace std;

void deleteMessage(zstring message, ostream &os)
{
  for (int i : z::core::range(message.length()))
    os << '\b' << ' ' << '\b' << flush;
}

int main(int argc, char *argv[])
{
  zstring().writeln(cerr);

  // for (auto id : z::core::array<zstring>{"1", "2", "3", "4"})
  for (auto id : z::core::array<zstring>{"4"})
  {
    zstring message;
    auto lines = z::file::lines("data/p"_zs + id + ".txt").collect();
    double total = lines.length();

    ("Analyzing file "_u8 + id + " (" + total + " paragraphs)" + "... ").write(cerr);

    int i = 0;
    z::core::array<zstring> result;

    for (auto line : lines)
    {
      if (++i % 50 == 0 || i == total)
      {
        deleteMessage(message, cerr);

        zstring p = zstring(((int)(i / total * 1000)) / 10.0);
        if (!p.count('.'))
          p += ".0";

        message = p + "%";
        message.write(cerr);
      }

      result.push(spellCheck(wordSearch(removeSpaces(line.trim()))));
    }

    deleteMessage(message, cerr);

    cerr << "Done!" << endl;

    z::core::join(result, ',').writeln(cout);
  }

  cerr << endl;
}
