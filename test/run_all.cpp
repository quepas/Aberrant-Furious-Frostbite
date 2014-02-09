#include <iostream>
#include <cppunit/ui/text/TestRunner.h>

// unit tests
#include "util/util_random_test.hpp"

int main()
{
  std::cout << "Running AFF Unit Tests..." << std::endl;

  CppUnit::TextUi::TestRunner runner;
  runner.addTest(UtilRandomTest::suite());
  runner.run();

  getchar();
}