#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define BENCHMARK_ADVANCED
#include "catch2/catch.hpp"

#include "random_string.hpp"
#include <algorithm>
#include <cstdint>
#include <set>
#include <unordered_set>

namespace
{
    void run_string_perf(const std::uint32_t number_of_elements, const std::uint32_t len)
    {
        utils::RandomStringGenerator rgn;
        std::vector<std::string> data(number_of_elements);
        for (std::uint32_t idx = 0; idx < number_of_elements; ++idx)
        {
            data[idx] = rgn(len);
        }

        std::set<std::string> lookup_set(data.cbegin(), data.cend());
        std::unordered_set<std::string> lookup_hash(data.cbegin(), data.cend());

        WHEN("The matched item is at the end of the vector")
        {
            const auto needle = data[number_of_elements - 1];

            BENCHMARK("O(n) algorithm")
            {
                return std::any_of(data.cbegin(), data.cend(), [&needle](auto& val) { return val == needle; });
            };

            BENCHMARK("O(1) algorithm")
            {
                return lookup_hash.count(needle);
            };

            BENCHMARK("O(log(n)) algorithm")
            {
                return lookup_set.count(needle);
            };
        }

        WHEN("The matched item is at the middle of the vector")
        {
            const auto needle = data[number_of_elements / 2];

            BENCHMARK("O(n) algorithm")
            {
                return std::any_of(data.cbegin(), data.cend(), [&needle](auto& val) { return val == needle; });
            };

            BENCHMARK("O(1) algorithm")
            {
                return lookup_hash.count(needle);
            };

            BENCHMARK("O(log(n)) algorithm")
            {
                return lookup_set.count(needle);
            };
        }

        WHEN("The matched item is at the beginning of the vector")
        {
            const auto needle = data[0];

            BENCHMARK("O(n) algorithm")
            {
                return std::any_of(data.cbegin(), data.cend(), [&needle](auto& val) { return val == needle; });
            };

            BENCHMARK("O(1) algorithm")
            {
                return lookup_hash.count(needle);
            };

            BENCHMARK("O(log(n)) algorithm")
            {
                return lookup_set.count(needle);
            };
        }
    }
} // namespace

SCENARIO("micro-benchmark for different search algorithms for std::string")
{
    GIVEN("There are 10 items and the size of each item is 32.")
    {
        run_string_perf(10, 32);
    }

    GIVEN("There are 10 items and the size of each item is 16.")
    {
        run_string_perf(10, 16);
    }

    GIVEN("There are 50 items and the size of each item is 32.")
    {
        run_string_perf(50, 32);
    }

    GIVEN("There are 50 items and the size of each item is 16.")
    {
        run_string_perf(50, 16);
    }
}
