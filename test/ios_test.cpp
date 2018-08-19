#include "cpp_utils/ios.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

SCENARIO("cout capture")
{
    auto capture = make_ostream_capture(std::cout);
    WHEN("nothing is written") { REQUIRE(capture.str().empty()); }
    WHEN("text is written")
    {
        std::cout << "test";
        THEN("the text must be captured") { REQUIRE(capture.str() == "test"); }
    }
    WHEN("multiple lines are written")
    {
        std::cout << "test" << std::endl;
        std::cout << "test2" << std::endl;
        THEN("all lines must be captured")
        {
            REQUIRE(capture.str() == "test\ntest2\n");
        }
    }

    GIVEN("another capture")
    {
        auto second_capture = make_ostream_capture(std::cout);

        WHEN("text is written")
        {
            std::cout << "test";
            THEN("the text is only captured by the second capture")
            {
                REQUIRE(second_capture.str() == "test");
                REQUIRE(capture.str().empty());
            }
        }
    }

    GIVEN("a scoped capture that goes out of scope")
    {
        {
            auto scoped_capture = make_ostream_capture(std::cout);
            std::cout << "this must be lost";
        }

        THEN("the old ostream target is restored")
        {
            std::cout << "test";
            REQUIRE(capture.str() == "test");
        }
    }
}
