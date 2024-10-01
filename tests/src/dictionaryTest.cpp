#include "catch.hpp"

#include "../../src/helpers/dictionary.h"

#include <z/core/string.hpp>
#include <z/core/array.hpp>
#include <z/core/split.hpp>
#include <z/file/lines.hpp>

zstring alphabet = "abcdefghijklmnopqrstuvwxyz";
zstring alphabet10 = "klmnopqrstuvwxyzabcdefghij";

zstring testingText = "one two three";
zstring puncText = "one1 .two. -three";
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
  REQUIRE(shiftAlphabet(10 + 26) == alphabet10);
  REQUIRE(shiftAlphabet(10 - 26) == alphabet10);
  REQUIRE(shiftAlphabet(10 - 2 * 26) == alphabet10);
}

TEST_CASE("Spell Check", "[dict]")
{
  REQUIRE(spellCheck(testingText) == 100.0);
  REQUIRE(spellCheck(puncText) == 100.0);
  REQUIRE(spellCheck(testingWrongText) == 0.0);
}

TEST_CASE("Word Search", "[dict]")
{
  REQUIRE(wordSearch(removeSpaces(testingText)) == testingText);
  REQUIRE(wordSearch(removeSpaces(voicePassport)) == voicePassport);
}

// TODO: Add some tools to add and remove data from both our dictionary and wiki files

void testFile(zstring filename, float scoreThreshold = 0)
{
  for (auto line : z::file::lines(filename))
  {
    zstring input = line.trim();
    zstring output = wordSearch(removeSpaces(input));
    float score = spellCheck(output);

    INFO("input: " << input << "\n");
    INFO("output: " << output << "\n");
    INFO("score: " << score << "\n");

    REQUIRE(score > scoreThreshold);
  }
}

TEST_CASE("Word Search 1 (large sample size)", "[.][.wiki1][dict]")
{
  testFile("src/data/wiki/wiki1.txt");
}

TEST_CASE("Word Search 2 (large sample size)", "[.][.wiki2][dict]")
{
  testFile("src/data/wiki/wiki2.txt");
}

TEST_CASE("Word Search 3 (large sample size)", "[.][.wiki3][dict]")
{
  testFile("src/data/wiki/wiki3.txt");
}

TEST_CASE("Word Search 4 (large sample size)", "[.][.wiki4][dict]")
{
  testFile("src/data/wiki/wiki4.txt");
}
