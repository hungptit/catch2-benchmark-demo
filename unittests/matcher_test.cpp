#include <algorithm>
#include <iterator>
#include <ostream>
#include <set>
#include <string>
#include <tuple>

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_templated.hpp"

#include "unittests/catch2_helper.h"

namespace
{
    struct Contains : Catch::Matchers::MatcherBase<std::set<std::string>>
    {
        Contains(
            const std::set<std::string>& expectedValues,
            const std::set<std::string>& values)
            : m_expectedValues(expectedValues)
            , m_values(values)
        {
        }

        bool match(const std::set<std::string>& v) const override
        {
            for (auto const& item : m_expectedValues)
            {
                if (m_values.count(item) == 0)
                {
                    return false;
                }
            }
            return true;
        }

        virtual std::string describe() const override
        {
            std::vector<std::string> m_missingValues;
            for (auto const& item : m_expectedValues)
            {
                if (m_values.count(item) == 0)
                {
                    m_missingValues.push_back(item);
                }
            }
            return "\n\nDoes not contain :\n\n" +
                   Catch::Detail::stringify(m_expectedValues) +
                   "\n\nThese are missing values:\n\n" +
                   Catch::Detail::stringify(m_missingValues);
        }

        const std::set<std::string>& m_expectedValues;
        const std::set<std::string> m_values;
    };
} // namespace

TEST_CASE("User defined == and << operators")
{
    unittests::Person a = {"John", "Doe", 30};
    unittests::Person b = {"Alan", "Smith", 40};
    CHECK(a == b);
    CHECK(a == a);
}

TEST_CASE("Test the custom matcher")
{
    SECTION("The first set contains all values in the second set")
    {
        const std::set<std::string> results = {"one", "two", "three"};
        const std::set<std::string> expected_results = {"one", "two"};
        CHECK_THAT(
            results, Contains(expected_results, results)); // This is expect
                                                           // to pass
    }

    SECTION("The first set does not contain the second set")
    {
        const std::set<std::string> results = {"one", "two", "three"};
        const std::set<std::string> expected_results = {"one", "four", "five"};
        CHECK_THAT(
            results, Contains(expected_results, results)); // This is expect
                                                           // to fail
    }
}
