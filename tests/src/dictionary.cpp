#include "catch.hpp"

#include "../../libs/dictionary.cpp"
#include "../../libs/file.cpp"
#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <z/core/split.hpp>

TEST_CASE("Testing Random Alphabet", "[dict]")
{
  REQUIRE(randomAlphabet() != "abcdefghijklmnopqrstuvwxyz");
}

TEST_CASE("Testing Shift Alphabet", "[dict]")
{
  REQUIRE(shiftAlphabet(0) == "abcdefghijklmnopqrstuvwxyz");
  REQUIRE(shiftAlphabet(26) == "abcdefghijklmnopqrstuvwxyz");
  REQUIRE(shiftAlphabet(-26) == "abcdefghijklmnopqrstuvwxyz");

  REQUIRE(shiftAlphabet(5) == "fghijklmnopqrstuvwxyzabcde");

  REQUIRE(shiftAlphabet(10) == "klmnopqrstuvwxyzabcdefghij");
  REQUIRE(shiftAlphabet(36) == "klmnopqrstuvwxyzabcdefghij");
  REQUIRE(shiftAlphabet(-16) == "klmnopqrstuvwxyzabcdefghij");
}

TEST_CASE("Testing Spell Check", "[dict]")
{
  REQUIRE(checkSpelling("testing one two three") == 100.0);
  REQUIRE(checkSpelling("testingg onee twoo threee") == 0.0);
}

TEST_CASE("Testing Word Search", "[dict]")
{
  REQUIRE(wordSearch("testingonetwothree") == "testing one two three");
  REQUIRE(wordSearch("myvoiceismypassportverifyme") == "my voice is my passport verify me");
}

TEST_CASE("Testing Word Search (large sample size)", "[.][dict]")
{
  std::ifstream file;
  zstring contents = "";
  std::string buffer = "";

  file.open("data/paragraphs.txt");

  if (!file)
    throw FileReadError();

  int i = 0;
  while (std::getline(file, buffer) && i < 10)
  {
    if (i++ <= 1)
      continue;

    zstring p = zstring(buffer);
    zstring q = p;

    REQUIRE(wordSearch(q.replace(" ", "")) == p);
  }
}
