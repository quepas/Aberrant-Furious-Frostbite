#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/win32/win32_input.hpp"

using std::string;
using CppUnit::TestFixture;
using namespace aff::win32;

class Win32InputTest : public TestFixture
{
  CPPUNIT_TEST_SUITE(Win32InputTest);
    CPPUNIT_TEST(TestMouseRetriveInput);
  CPPUNIT_TEST_SUITE_END();

private:
  MSG MoveMouseTo(int x, int y) {
    MSG msg;
    msg.message = WM_MOUSEMOVE;
    msg.lParam = MAKELONG(x, y);
    return msg;
  }

public:
  void TestMouseRetriveInput() {
    Input input;

    input.RetriveInput(MoveMouseTo(123, 101));    
    auto mouse_current = input.mouse_current();
    CPPUNIT_ASSERT(mouse_current.x == 123);
    CPPUNIT_ASSERT(mouse_current.y == 101);
    
    input.RetriveInput(MoveMouseTo(130, 90));
    auto mouse_last = input.mouse_last();
    CPPUNIT_ASSERT(mouse_last.x == 123);
    CPPUNIT_ASSERT(mouse_last.y == 101);
    mouse_current = input.mouse_current();
    CPPUNIT_ASSERT(mouse_current.x == 130);
    CPPUNIT_ASSERT(mouse_current.y == 90);
    auto mouse_diff = input.mouse_diff();
    CPPUNIT_ASSERT(mouse_diff.x == -7);
    CPPUNIT_ASSERT(mouse_diff.y == 11);
  }
};