#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_exception.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

TEST_CASE("Exception demo")
{
    const std::string errmsg = "This is my error message";

    SECTION("Use CHECK_THROW and CHECK_NOTHROW for simple validation")
    {
        CHECK_THROWS(throw std::logic_error(errmsg));  // This is expect to pass
        CHECK_NOTHROW(throw std::logic_error(errmsg)); // This is expect to fail
    }

    SECTION("Use CHECK_THROW_AS to verify the exception type")
    {
        CHECK_THROWS_AS(
            throw std::logic_error(errmsg),
            std::logic_error); // This is expect to pass
        CHECK_THROWS_AS(
            throw std::logic_error(errmsg),
            std::runtime_error); // This is expect to fail
    }

    SECTION("Use CHECK_THROW_WITH to verify the exception message")
    {
        CHECK_THROWS_WITH(
            throw std::logic_error(errmsg),
            Catch::Matchers::ContainsSubstring(
                errmsg)); // This is expect to pass
        CHECK_THROWS_WITH(
            throw std::logic_error(errmsg),
            Catch::Matchers::ContainsSubstring(
                "exception")); // This is expect to fail
    }

    SECTION("Use CHECK_THROW_MATCHES by default if you can")
    {
        const auto ex = std::logic_error(errmsg);
        CHECK_THROWS_MATCHES(
            throw std::logic_error(errmsg), std::logic_error,
            Catch::Matchers::ExceptionMessageMatcher(
                errmsg)); // This is expect to pass
        CHECK_THROWS_MATCHES(
            throw std::runtime_error(errmsg), std::logic_error,
            Catch::Matchers::ExceptionMessageMatcher(
                errmsg)); // This is expect to fail
    }
}
