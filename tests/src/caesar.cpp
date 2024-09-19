#include "catch.hpp"

#include "../../ciphers/caesar.cpp"

zstring caesarInputA = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
zstring caesarOutputA = "Sp ro rkn kxidrsxq myxpsnoxdskv dy cki, ro gbydo sd sx mszrob, drkd sc, li cy mrkxqsxq dro ybnob yp dro voddobc yp dro kvzrklod, drkd xyd k gybn myevn lo wkno yed.";

zstring caesarInputB = "Ifhehadanythingconfidentialtosayhewroteitincipherthatisbysochangingtheorderofthelettersofthealphabetthatnotawordcouldbemadeout";
zstring caesarOutputB = "Sprorknkxidrsxqmyxpsnoxdskvdyckirogbydosdsxmszrobdrkdsclicymrkxqsxqdroybnobypdrovoddobcypdrokvzrkloddrkdxydkgybnmyevnlowknoyed";

TEST_CASE("Testing Caesar Encode")
{
  REQUIRE(caesarEncode(caesarInputA, 10) == caesarOutputA);
  REQUIRE(caesarEncode(caesarInputB, 10) == caesarOutputB);
}

TEST_CASE("Testing Caesar Decode")
{
  REQUIRE(caesarDecode(caesarOutputA, 10) == caesarInputA);
  REQUIRE(caesarDecode(caesarOutputB, 10) == caesarInputB);
}

TEST_CASE("Testing Caesar Reciprocity")
{
  REQUIRE(caesarDecode(caesarEncode(caesarInputA, 10), 10) == caesarInputA);
  REQUIRE(caesarDecode(caesarEncode(caesarInputB, 10), 10) == caesarInputB);
}

TEST_CASE("Testing Caesar Crack")
{
  REQUIRE(caesarCrack(caesarOutputA)[0].text == caesarInputA);
}
