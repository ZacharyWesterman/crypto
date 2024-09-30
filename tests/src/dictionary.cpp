#include "catch.hpp"

#include "../../libs/dictionary.h"
#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <z/core/split.hpp>
#include <z/file/lines.hpp>

#include <fstream>

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";
zstring alphabet10 = "klmnopqrstuvwxyzabcdefghij";

zstring testingText = "one two three";
zstring testingWrongText = "testingg onee twoo threee";
zstring voicePassport = "my voice is my passport verify me";

TEST_CASE("Random Alphabet", "[dict]")
{
  REQUIRE(randomAlphabet() != alphabet);
}

TEST_CASE("Shift Alphabet", "[dict]")
{
  REQUIRE(shiftAlphabet(0) == alphabet);
  REQUIRE(shiftAlphabet(26) == alphabet);
  REQUIRE(shiftAlphabet(-26) == alphabet);

  REQUIRE(shiftAlphabet(10) == alphabet10);
  REQUIRE(shiftAlphabet(36) == alphabet10);
  REQUIRE(shiftAlphabet(-16) == alphabet10);
}

TEST_CASE("Spell Check", "[dict]")
{
  REQUIRE(checkSpelling(testingText) == 100.0);
  REQUIRE(checkSpelling(testingWrongText) == 0.0);
}

TEST_CASE("Word Search", "[dict]")
{
  REQUIRE(wordSearch(removeSpaces(testingText)) == testingText);
  REQUIRE(wordSearch(removeSpaces(voicePassport)) == voicePassport);
}

// TODO: In general, come up with a toolset that allows us to analyze and manipulate
// our sample text as well as our dictionary to be able to figure out where our efficiencies,
// inefficiencies, and flaws occur. We should be able to add and remove words,
// and see score distributions for our input text.
TEST_CASE("Word Search 1 (large sample size)", "[.][.p1][dict]")
{
  for (auto line : z::file::lines("data/p1.txt"))
    REQUIRE(checkSpelling(wordSearch(removeSpaces(line.trim()))) > 50);
}

TEST_CASE("Word Search 2 (large sample size)", "[.][.p2][dict]")
{
  for (auto line : z::file::lines("data/p2.txt"))
    REQUIRE(checkSpelling(wordSearch(removeSpaces(line.trim()))) > 50);
}

TEST_CASE("Word Search 3 (large sample size)", "[.][.p3][dict]")
{
  for (auto line : z::file::lines("data/p3.txt"))
    REQUIRE(checkSpelling(wordSearch(removeSpaces(line.trim()))) > 50);
}
