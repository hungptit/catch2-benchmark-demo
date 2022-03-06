#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

SCENARIO("vectors can be sized and resized", "[vector]")
{
    GIVEN("A vector with some items")
    {
        std::vector<int> v(5);

        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 5);

        WHEN("the size is increased")
        {
            v.resize(10);

            THEN("the size and capacity change")
            {
                REQUIRE(v.size() == 12);     // This is expect to fail
                REQUIRE(v.capacity() >= 10); // This is expect to fail
            }
        }

        WHEN("the size is reduced")
        {
            v.resize(0);

            THEN("the size changes but not capacity")
            {
                REQUIRE(v.size() == 0);     // This is expect to fail
                REQUIRE(v.capacity() >= 5); // This is expect to fail
            }
        }
    }
}
