#include "catch.hpp"

#include "../../src/ciphers/substitution.h"

zstring key1 = "zyxwvutsrqponmlkjihgfedcba";
zstring subInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring subOutput1 = "Ru sv szw zmbgsrmt xlmurwvmgrzo gl hzb, sv dilgv rg rm xrksvi, gszg rh, yb hl xszmtrmt gsv liwvi lu gsv ovggvih lu gsv zokszyvg, gszg mlg z dliw xlfow yv nzwv lfg.";

TEST_CASE("Substitution Encode", "[sub]")
{
  INFO("key: " << key1);
  INFO("input: " << subInput);
  REQUIRE(substitutionEncode(subInput, key1) == subOutput1);
}

TEST_CASE("Substitution Decode", "[sub]")
{
  INFO("key: " << key1);
  REQUIRE(substitutionEncode(subOutput1, key1) == subInput);
}

TEST_CASE("Substitution Reciprocity", "[sub]")
{
  INFO("key: " << key1);
  REQUIRE(substitutionDecode(substitutionEncode(subInput, key1), key1) == subInput);
}

// TEST_CASE("Substitution Crack")
// {
//   REQUIRE(substitutionCrack(subOutput)[0].text == subInput);
// }
