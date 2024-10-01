#ifndef CIPHERS_H
#define CIPHERS_H

// Helpers
template <typename T>
void testEncode(zstring (*encode)(const zstring &input, T key), T key, zstring input, zstring output)
{
  INFO("key: " << key);
  INFO("input: " << input);
  REQUIRE(encode(input, key) == output);
}

template <typename T>
void testDecode(zstring (*decode)(const zstring &input, T key), T key, zstring input, zstring output)
{
  INFO("key: " << key);
  REQUIRE(decode(input, key) == output);
}

template <typename T>
void testReciprocity(zstring (*encode)(const zstring &input, T key), zstring (*decode)(const zstring &input, T key), T key, zstring input)
{
  INFO("key: " << key);
  REQUIRE(decode(encode(input, key), key) == input);
}

template <typename T>
void testCrack(T (*crack)(const zstring &input), zstring input, zstring output)
{
  REQUIRE(crack(output)[0].text == input);
}

#endif
