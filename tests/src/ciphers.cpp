#include "catch.hpp"

#include "../../src/dictionary.h"

#include "ciphers.h"
#include "../../src/ciphers/caesar.h"
#include "../../src/ciphers/substitution.h"

zstring cipherInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";

int caesarKey = 10;
zstring caesarOutput = "Sp ro rkn kxidrsxq myxpsnoxdskv dy cki, ro gbydo sd sx mszrob, drkd sc, li cy mrkxqsxq dro ybnob yp dro voddobc yp dro kvzrklod, drkd xyd k gybn myevn lo wkno yed.";

zstring subKey = "zyxwvutsrqponmlkjihgfedcba";
zstring subOutput = "Ru sv szw zmbgsrmt xlmurwvmgrzo gl hzb, sv dilgv rg rm xrksvi, gszg rh, yb hl xszmtrmt gsv liwvi lu gsv ovggvih lu gsv zokszyvg, gszg mlg z dliw xlfow yv nzwv lfg.";

// Caesar
TEST_CASE("Caesar Encode", "[caesar]")
{
  testEncode<int>(caesarEncode, caesarKey, cipherInput, caesarOutput);
}

TEST_CASE("Caesar Decode", "[caesar]")
{
  testDecode<int>(caesarEncode, caesarKey, cipherInput, caesarOutput);
}

TEST_CASE("Caesar Reciprocity", "[caesar]")
{
  testReciprocity<int>(caesarEncode, caesarDecode, caesarKey, cipherInput);
}

TEST_CASE("Caesar Crack", "[caesar]")
{
  testCrack(caesarCrack, cipherInput, caesarOutput);
}

// Substitution
TEST_CASE("Substitution Encode", "[sub]")
{
  testEncode<zstring>(substitutionEncode, subKey, cipherInput, subOutput);
}

TEST_CASE("Substitution Decode", "[sub]")
{
  testReciprocity<zstring>(substitutionEncode, substitutionDecode, caesarKey, cipherInput);
}

TEST_CASE("Substitution Reciprocity", "[sub]")
{
  INFO("key: " << subKey);
  testReciprocity<zstring>(substitutionEncode, substitutionDecode, subKey, cipherInput);
}

// TEST_CASE("Substitution Crack")
// {
//   testCrack(substitutionCrack, cipherInput, subOutput);
// }
