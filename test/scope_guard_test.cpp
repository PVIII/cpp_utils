#include "cpp_utils/scope_guard.hpp"

#include "catch.hpp"

SCENARIO("Exit Guard")
{
    GIVEN("A guard that executes on every exit.")
    {
        WHEN("The scope is left normally.")
        {
            bool executed = false;
            {
                auto g = exit_guard([&]() { executed = true; });
            }
            REQUIRE(executed);
        }
    }
}
