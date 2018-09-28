#include "cpp_utils/ios.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#ifdef __cpp_deduction_guides
SCENARIO("class template deduction") { ostream_capture c(std::cout); }
#endif
