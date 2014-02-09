#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/util/util_random.hpp"

using std::string;
using CppUnit::TestFixture;
using namespace aff::util;

class UtilRandomTest : public TestFixture
{
  CPPUNIT_TEST_SUITE(UtilRandomTest);
    CPPUNIT_TEST(testGenerate32Chars);  
  CPPUNIT_TEST_SUITE_END();

private:
public:
  void testGenerate32Chars() {
    string generated_chars = random::Generate32Chars();
    CPPUNIT_ASSERT(generated_chars.length() == 32);

    for (char& c : generated_chars) {
      if (random::standard_chars.find_first_of(c) == string::npos)
        CPPUNIT_FAIL(string("Bad char: ") + c);
    }
  }
};