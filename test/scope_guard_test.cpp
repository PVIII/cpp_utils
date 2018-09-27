#include "cpp_utils/scope_guard.hpp"

#include "catch.hpp"

SCENARIO("Exit Guard")
{
    GIVEN("A guard that executes on every exit.")
    {
        WHEN("The scope is left normally.")
        {
            bool executed = false;
            THEN("The action must not be executed while still in the scope.")
            {
                auto g = make_exit_guard([&]() { executed = true; });
                REQUIRE(not executed);
            }
            REQUIRE(executed);
        }
        WHEN("The scope is left via exception.")
        {
            bool executed = false;
            try
            {
                auto g = make_exit_guard([&]() { executed = true; });
                throw 0;
            }
            catch(...)
            {
                THEN(
                    "The action must be executed when the scope has been left.")
                {
                    REQUIRE(executed);
                }
            }
        }
        WHEN("The guard is moved from.")
        {
            unsigned executions = 0;
            THEN("The action must not be executed while still in the scope.")
            {
                auto g1 = make_exit_guard([&]() { ++executions; });
                auto g2 = std::move(g1);
                REQUIRE(executions == 0);
            }
            REQUIRE(executions == 1);
        }
    }
}
