#include "cpp_utils/ios.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

SCENARIO("class template deduction") { ostream_capture c(std::cout); }
