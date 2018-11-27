#include "cpp_utils/scope_guard.hpp"

#include "catch.hpp"

#ifdef __cpp_deduction_guides
SCENARIO("scope_guard types.")
{
    exit_guard   g1([] {});
    return_guard g2([] {});
}
#endif
