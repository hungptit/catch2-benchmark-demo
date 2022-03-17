#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/benchmark/catch_benchmark.hpp"
#include "catch2/catch_test_macros.hpp"

#include "map_vs_hash.hpp"
#include "random_string.hpp"
#include <cstdint>

namespace
{
    std::vector<std::string> generate_test_vector(
        const uint32_t array_size, const uint32_t strlen)
    {
        utils::RandomStringGenerator rgn;
        std::vector<std::string> results(array_size);
        for (uint32_t idx = 0; idx < array_size; ++idx)
        {
            results[idx] = rgn(strlen);
        }
        return results;
    }

    const auto vec_10 = generate_test_vector(10, 32);
    const auto vec_100 = generate_test_vector(100, 32);
    const auto vec_1000 = generate_test_vector(1000, 32);

} // namespace

TEST_CASE("Compare map and sort performance")
{
    BENCHMARK("map 10 elements")
    {
        return algorithm::get_sorted_strings_using_map(vec_10);
    };

    BENCHMARK("sort 10 elements")
    {
        return algorithm::get_sorted_strings_using_sort(vec_10);
    };

    BENCHMARK("map 100 elements")
    {
        return algorithm::get_sorted_strings_using_map(vec_100);
    };

    BENCHMARK("sort 100 elements")
    {
        return algorithm::get_sorted_strings_using_sort(vec_100);
    };

    BENCHMARK("map 1000 elements")
    {
        return algorithm::get_sorted_strings_using_map(vec_1000);
    };

    BENCHMARK("sort 1000 elements")
    {
        return algorithm::get_sorted_strings_using_sort(vec_1000);
    };
}
