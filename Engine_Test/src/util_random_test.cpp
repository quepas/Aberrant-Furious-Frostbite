#include <catch.hpp>

#include "util_random.hpp"

using std::string;
using namespace aff::util;

TEST_CASE("Random chars generation test") {
  SECTION("32 random chars") {
    string generated_chars = random::Generate32Chars();
    REQUIRE(generated_chars.length() == 32);

    for (char& c : generated_chars) {
      if (random::standard_chars.find_first_of(c) == string::npos)
        FAIL(string("Bad char: ") + c);
    }
  }
}
