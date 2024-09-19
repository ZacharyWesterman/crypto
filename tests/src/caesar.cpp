#include "catch.hpp"

#include "../../ciphers/caesar.cpp"

zstring longInput = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring longOutput = "Sp ro rkn kxidrsxq myxpsnoxdskv dy cki, ro gbydo sd sx mszrob, drkd sc, li cy mrkxqsxq dro ybnob yp dro voddobc yp dro kvzrklod, drkd xyd k gybn myevn lo wkno yed.";

TEST_CASE("Testing Caesar Encode")
{
  REQUIRE(caesarEncode("bbbbb", 1) == "ccccc");
  REQUIRE(caesarEncode(longInput, 10) == longOutput);
}

TEST_CASE("Testing Caesar Decode")
{
  REQUIRE(caesarDecode("ccccc", 1) == "bbbbb");
  REQUIRE(caesarDecode(longOutput, 10) == longInput);
}

TEST_CASE("Testing Caesar Reciprocity")
{
  REQUIRE(caesarDecode(caesarEncode("bbbbb", 1), 1) == "bbbbb");
  REQUIRE(caesarDecode(caesarEncode(longInput, 10), 10) == longInput);
}

TEST_CASE("Testing Caesar Crack")
{
  REQUIRE(caesarCrack(longOutput)[0].text == longInput);
}
