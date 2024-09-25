#include "catch.hpp"

#include "../../ciphers/substitution.cpp"

zstring key1 = "zyxwvutsrqponmlkjihgfedcba";
zstring subInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring subOutput1 = "Ru sv szw zmbgsrmt xlmurwvmgrzo gl hzb, sv dilgv rg rm xrksvi, gszg rh, yb hl xszmtrmt gsv liwvi lu gsv ovggvih lu gsv zokszyvg, gszg mlg z dliw xlfow yv nzwv lfg.";

TEST_CASE("Testing Substitution Encode", "[sub]")
{
  REQUIRE(substitutionEncode(subInput, key1) == subOutput1);
}

TEST_CASE("Testing Substitution Decode", "[sub]")
{
  REQUIRE(substitutionEncode(subOutput1, key1) == subInput);
}

TEST_CASE("Testing Substitution Reciprocity", "[sub]")
{
  REQUIRE(substitutionDecode(substitutionEncode(subInput, key1), key1) == subInput);
}

// TEST_CASE("Testing Substitution Crack")
// {
//   REQUIRE(substitutionCrack(subOutput)[0].text == subInput);
// }
