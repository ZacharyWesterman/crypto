#include "catch.hpp"

#include "../../libs/dictionary.cpp"
#include "../../libs/file.cpp"
#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <z/core/split.hpp>

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";
zstring alphabet10 = "klmnopqrstuvwxyzabcdefghij";

zstring testingText = "testing one two three";
zstring testingWrongText = "testingg onee twoo threee";
zstring voicePassport = "my voice is my passport verify me";

TEST_CASE("Testing Random Alphabet", "[dict]")
{
  REQUIRE(randomAlphabet() != alphabet);
}

TEST_CASE("Testing Shift Alphabet", "[dict]")
{
  REQUIRE(shiftAlphabet(0) == alphabet);
  REQUIRE(shiftAlphabet(26) == alphabet);
  REQUIRE(shiftAlphabet(-26) == alphabet);

  REQUIRE(shiftAlphabet(10) == alphabet10);
  REQUIRE(shiftAlphabet(36) == alphabet10);
  REQUIRE(shiftAlphabet(-16) == alphabet10);
}

TEST_CASE("Testing Spell Check", "[dict]")
{
  REQUIRE(checkSpelling(testingText) == 100.0);
  REQUIRE(checkSpelling(testingWrongText) == 0.0);
}

TEST_CASE("Testing Word Search", "[dict]")
{
  REQUIRE(wordSearch(removeSpaces(testingText)) == testingText);
  REQUIRE(wordSearch(removeSpaces(voicePassport)) == voicePassport);
}

// TODO: We need a ruleset to filter out arbitrarily difficult inputs
// For example, the second input contains non-words like InsideAR,
// metaio and GmbH, which will not (and should not) pass. Therefore,
// some test data must be excluded as inapplicable. This does not have an
// overly large effect (I think) on either success or readability.

// TODO: We may want a script that will allow us to do that more easily
TEST_CASE("Testing Word Search (large sample size)", "[.][dict]")
{
  std::ifstream file;
  zstring contents = "";
  std::string buffer = "";

  file.open("data/paragraphs.txt");

  if (!file)
    throw FileReadError();

  int i = 0;
  while (std::getline(file, buffer) && i++ < 10)
  {
    if (i <= 0)
      continue;

    zstring p = zstring(buffer);
    REQUIRE(wordSearch(removeSpaces(p)) == p);
  }
}
