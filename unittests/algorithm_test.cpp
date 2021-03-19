#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "random_string.hpp"

namespace {
    int Factorial( int number ) {
        return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
    }    
}

TEST_CASE( "Factorial" ) {
    SECTION("Factorial of 0 is 1 (fail)") {
        REQUIRE( Factorial(0) == 1 );
    }

    SECTION("Factorials of 1 and higher are computed (pass)") {
        REQUIRE( Factorial(1) == 1 );
        REQUIRE( Factorial(2) == 2 );
        REQUIRE( Factorial(3) == 6 );
        REQUIRE( Factorial(10) == 3628800 );
    }
}

TEST_CASE("Random string") {
    utils::RandomStringGenerator rgn;
    constexpr size_t len = 32;
    auto str = rgn(len);
    REQUIRE(str.length() == len);
}
