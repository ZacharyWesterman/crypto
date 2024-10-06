#include "catch.hpp"
#include "../../libs/argparse.h"
#include "../../src/helpers/parser.h"

#include <z/core/array.hpp>

bool tryParse(argparse::ArgumentParser &program, z::core::array<std::string> args)
{
  try
  {
    program.parse_args({"./crypto", "encode", "caesar", "testing one two three"});
    return true;
  }
  catch (const std::exception &err)
  {
    INFO("Something went wrong parsing the args")
    return false;
  }
}

// TODO: Make more tests
TEST_CASE("Testing good parser input", "[parse]")
{
  argparse::ArgumentParser program("crypto", "0.0.1");
  setupProgram(program);

  SECTION("Basic encode")
  {
    REQUIRE(tryParse(program, {"./crypto", "encode", "caesar", "testing one two three"}));
  }

  SECTION("Basic decode")
  {
    REQUIRE(tryParse(program, {"./crypto", "decode", "caesar", "testing one two three"}));
  }
}
