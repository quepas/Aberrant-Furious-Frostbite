#include <catch.hpp>
#include "win32_input.hpp"

using namespace aff::win32;

MSG MoveMouseTo(int x, int y) {
  MSG msg;
  msg.message = WM_MOUSEMOVE;
  msg.lParam = MAKELONG(x, y);
  return msg;
}

TEST_CASE("Mouse movement and retriving") {
  SECTION("Retriving input") {
    Input input;

    input.RetriveInput(MoveMouseTo(123, 101));
    auto mouse_current = input.mouse_current();
    REQUIRE(mouse_current.x == 123);
    REQUIRE(mouse_current.y == 101);

    input.RetriveInput(MoveMouseTo(130, 90));
    auto mouse_last = input.mouse_last();
    REQUIRE(mouse_last.x == 123);
    REQUIRE(mouse_last.y == 101);
    mouse_current = input.mouse_current();
    REQUIRE(mouse_current.x == 130);
    REQUIRE(mouse_current.y == 90);
    auto mouse_diff = input.mouse_diff();
    REQUIRE(mouse_diff.x == -7);
    REQUIRE(mouse_diff.y == 11);
  }
}
