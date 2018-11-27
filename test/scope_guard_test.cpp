#include "cpp_utils/scope_guard.hpp"

#include <vector>

#include "catch.hpp"

SCENARIO("Exit Guard")
{
    GIVEN("A guard that executes on every exit.")
    {
        WHEN("The scope is left normally.")
        {
            THEN("The action must not be executed while still in the scope.")
            {
                bool executed = false;
                {
                    auto g = make_exit_guard([&]() { executed = true; });
                    REQUIRE(not executed);
                }
                REQUIRE(executed);
            }

            THEN("The action is executed exactly once.")
            {
                unsigned n = 0;
                {
                    auto g = make_exit_guard([&]() { ++n; });
                }
                REQUIRE(n == 1);
            }
        }
        WHEN("The scope is left via exception.")
        {
            THEN("The action is executed exactly once when the scope has been "
                 "left.")
            {
                unsigned n = 0;
                try
                {
                    auto g = make_exit_guard([&]() { ++n; });
                    throw 0;
                }
                catch(...)
                {
                    REQUIRE(n == 1);
                }
            }
        }
    }
}

SCENARIO("return_guard")
{
    GIVEN("A guard that executes on non-exception exits.")
    {
        WHEN("The scope is left normally.")
        {
            THEN("The action must not be executed while still in the scope.")
            {
                bool executed = false;
                {
                    auto g = make_return_guard([&]() { executed = true; });
                    REQUIRE(not executed);
                }
                REQUIRE(executed);
            }

            THEN("The action is executed exactly once.")
            {
                unsigned n = 0;
                {
                    auto g = make_return_guard([&]() { ++n; });
                }
                REQUIRE(n == 1);
            }
        }
        WHEN("The scope is left via exception.")
        {
            THEN("The action is not executed.")
            {
                bool executed = false;
                try
                {
                    auto g = make_return_guard([&]() { executed = true; });
                    throw 0;
                }
                catch(...)
                {
                    REQUIRE(not executed);
                }
            }
        }
    }
}
