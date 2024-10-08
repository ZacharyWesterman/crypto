#include <z/all.hpp>

z::util::dictionary dict;

int main(int argc, char *argv[])
{
  dict.read("src/data/words.txt");

  zstring newWord = argv[1];

  dict.addWord(newWord);

  // dict.filter([](auto i){ return i[0] == 'a'; }); // Only keep words that start with A

  dict.write("src/data/words2.txt");
}
