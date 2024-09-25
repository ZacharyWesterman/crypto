#include "catch.hpp"

#include "../../libs/file.cpp"

std::string foxText = "the quick brown fox jumps over the lazy dog";

TEST_CASE("Testing Load File", "[file]")
{
  REQUIRE(loadFile("data/fox.txt") == foxText);
}

TEST_CASE("Testing Write File", "[file]")
{
  writeFile(foxText, "data/testOutput.txt");

  REQUIRE(loadFile("data/testOutput.txt") == foxText);

  remove("data/testOutput.txt");
}
