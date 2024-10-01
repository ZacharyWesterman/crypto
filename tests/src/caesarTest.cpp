#include "catch.hpp"

#include "../../src/ciphers/caesar.h"

// TODO: can tests be generalized between caesar and sub?

zstring caesarInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring caesarOutput = "Sp ro rkn kxidrsxq myxpsnoxdskv dy cki, ro gbydo sd sx mszrob, drkd sc, li cy mrkxqsxq dro ybnob yp dro voddobc yp dro kvzrklod, drkd xyd k gybn myevn lo wkno yed.";

zstring caesarInputCharsOnly = caesarInput.replace(" ", "");
zstring caesarOutputCharsOnly = caesarOutput.replace(" ", "");

TEST_CASE("Caesar Encode", "[caesar]")
{
  REQUIRE(caesarEncode(caesarInput, 10) == caesarOutput);
  REQUIRE(caesarEncode(caesarInputCharsOnly, 10) == caesarOutputCharsOnly);
}

TEST_CASE("Caesar Decode", "[caesar]")
{
  REQUIRE(caesarDecode(caesarOutput, 10) == caesarInput);
  REQUIRE(caesarDecode(caesarOutputCharsOnly, 10) == caesarInputCharsOnly);
}

TEST_CASE("Caesar Reciprocity", "[caesar]")
{
  REQUIRE(caesarDecode(caesarEncode(caesarInput, 10), 10) == caesarInput);
  REQUIRE(caesarDecode(caesarEncode(caesarInputCharsOnly, 10), 10) == caesarInputCharsOnly);
}

TEST_CASE("Caesar Crack", "[caesar]")
{
  REQUIRE(caesarCrack(caesarOutput)[0].text == caesarInput);
}
