#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

#include "random_string.hpp"

namespace
{
    int Factorial(size_t number)
    {
        return number <= 1 ? number : Factorial(number - 1) * number;
    }
}

TEST_CASE("Factorial")
{
    SECTION("Factorial of 0 is 0")
    {
        REQUIRE(Factorial(0) == 1); // This is expect to fail.
    }

    SECTION("Factorials of 1 and higher are computed (pass)")
    {
        REQUIRE(Factorial(1) == 1);        // This is expect to pass
        REQUIRE(Factorial(2) == 2);        // This is expect to pass
        REQUIRE(Factorial(3) == 6);        // This is expect to pass
        REQUIRE(Factorial(10) == 3628800); // This is expect to pass
    }
}

TEST_CASE("Random string")
{
    utils::RandomStringGenerator rgn;
    constexpr size_t len = 32;
    auto str = rgn(len);
    REQUIRE(str.length() == len);
}
