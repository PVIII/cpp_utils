#include "cpp_utils/ios.hpp"

#include "catch2/catch.hpp"

#include <iostream>

#ifdef __cpp_deduction_guides
SCENARIO("ios types") { ostream_capture c(std::cout); }
#endif
