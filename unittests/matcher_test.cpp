#include <ostream>
#include <set>
#include <string>
#include <tuple>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "unittests/catch2_helper.h"

namespace
{
    struct Contains : Catch::Matchers::Impl::MatcherBase<std::set<std::string>>
    {
        Contains(const std::set<std::string>& expectedValues)
            : m_expectedValues(expectedValues)
        {
        }

        bool match(const std::set<std::string>& v) const override
        {
            m_missingValues.clear();
            bool result = true;
            for (auto const& item : m_expectedValues)
            {
                if (v.count(item) == 0)
                {
                    m_missingValues.push_back(item);
                    result = false;
                }
            }
            return result;
        }

        virtual std::string describe() const override
        {
            return "\n\nDoes not contain :\n\n" + Catch::Detail::stringify(m_expectedValues) +
                   "\n\nThese are missing values:\n\n" + Catch::Detail::stringify(m_missingValues);
        }

        const std::set<std::string>& m_expectedValues;

        // The mutable keyword will let us mark match method as const, i.e same as
        // that of the base class.
        mutable std::vector<std::string> m_missingValues;
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
        CHECK_THAT(results, Contains(expected_results)); // This is expect to pass
    }

    SECTION("The first set does not contain the second set")
    {
        const std::set<std::string> results = {"one", "two", "three"};
        const std::set<std::string> expected_results = {"one", "four", "five"};
        CHECK_THAT(results, Contains(expected_results)); // This is expect to fail
    }
}
