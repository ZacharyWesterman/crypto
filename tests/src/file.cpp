// FIXME: We can have this back when we fix the linker issue

// #include "catch.hpp"

// #include "../../libs/file.cpp"

// std::string foxText = "the quick brown fox jumps over the lazy dog";
// std::string multilineText = "my voice is my passport\nverify me";

// TEST_CASE("Testing Load File", "[file]")
// {
//   REQUIRE(loadFile("data/fox.txt") == foxText);
// }

// TEST_CASE("Testing Write File", "[file]")
// {
//   writeFile(foxText, "data/testOutput.txt");

//   REQUIRE(loadFile("data/testOutput.txt") == foxText);

//   remove("data/testOutput.txt");
// }

// TEST_CASE("Testing Multi-line Read File", "[file]")
// {
//   REQUIRE(loadFile("data/multiline.txt") == multilineText);
// }

// TEST_CASE("Testing Multi-line write File", "[file]")
// {
//   writeFile(multilineText, "data/testOutput.txt");

//   REQUIRE(loadFile("data/testOutput.txt") == multilineText);

//   remove("data/testOutput.txt");
// }