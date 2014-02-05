#include "util_random.hpp"

#include <random>

using std::string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

namespace aff {
  namespace util {
    namespace random {

std::string util::random::Generate32Chars()
{
  string result;
  random_device device;
  mt19937 generator(device());
  uniform_int_distribution<> distribution(0, standard_chars.length() - 1);
  
  for (int i = 0; i < 32; ++i) {
    result += standard_chars[distribution(generator)];
  }
  return result;
}

// aff::util::random::
}}}
