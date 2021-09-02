#include <set>
#include <string>
#include <tuple>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

namespace
{
    struct Person
    {
        std::string first_name;
        std::string last_name;
        int age;
    };

    bool operator==(const Person& lhs, const Person& rhs)
    {
        return true;
    }

    struct Contains : Catch::Matchers::Impl::MatcherBase<std::set<std::string>>
    {
        Contains(const std::set<std::string>& expectedValues)
            : m_expectedValues(expectedValues)
        {
        }

        bool match(const std::set<std::string>& v) const override
        {
            m_extraValues.clear();
            bool result = true;
            for (auto const& item : m_expectedValues)
            {
                if (v.count(item) == 0)
                {
                    m_extraValues.push_back(item);
                    result = false;
                }
            }
            return result;
        }

        virtual std::string describe() const override
        {
            return "\n\nDoes not contain :\n\n" + Catch::Detail::stringify(m_expectedValues) +
                   "\n\nThese are extra values:\n\n" + Catch::Detail::stringify(m_extraValues);
        }

        const std::set<std::string>& m_expectedValues;

        // The mutable keyword will let us mark match method as const, i.e same as
        // that of the base class.
        mutable std::vector<std::string> m_extraValues;
    };
} // namespace

TEST_CASE("Test the custom matcher")
{
    SECTION("The first set contains all values in the second set")
    {
        const std::set<std::string> results = {"one", "two", "three"};
        const std::set<std::string> expected_results = {"one", "two"};
        CHECK_THAT(results, Contains(expected_results));
    }

    SECTION("The first set does not contain the second set")
    {
        const std::set<std::string> results = {"one", "two", "three"};
        const std::set<std::string> expected_results = {"one", "four", "five"};
        CHECK_THAT(results, Contains(expected_results));
    }
}
