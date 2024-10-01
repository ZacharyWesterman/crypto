#include "catch.hpp"

#include "../../src/ciphers/caesar.h"
#include "../../src/dictionary.h"

// TODO: can tests be generalized between caesar and sub?

zstring caesarInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring caesarOutput = "Sp ro rkn kxidrsxq myxpsnoxdskv dy cki, ro gbydo sd sx mszrob, drkd sc, li cy mrkxqsxq dro ybnob yp dro voddobc yp dro kvzrklod, drkd xyd k gybn myevn lo wkno yed.";

TEST_CASE("Caesar Encode", "[caesar]")
{
  INFO("key: " << 10);
  INFO("input: " << caesarInput);
  REQUIRE(caesarEncode(caesarInput, 10) == caesarOutput);
}

TEST_CASE("Caesar Decode", "[caesar]")
{
  INFO("key: " << 10);
  REQUIRE(caesarDecode(caesarOutput, 10) == caesarInput);
}

TEST_CASE("Caesar Reciprocity", "[caesar]")
{
  INFO("key: " << 10);
  REQUIRE(caesarDecode(caesarEncode(caesarInput, 10), 10) == caesarInput);
}

TEST_CASE("Caesar Crack", "[caesar]")
{
  REQUIRE(caesarCrack(caesarOutput)[0].text == caesarInput);
}
