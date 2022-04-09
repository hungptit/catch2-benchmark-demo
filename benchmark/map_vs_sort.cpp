#include <algorithm>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/benchmark/catch_benchmark.hpp"
#include "catch2/catch_test_macros.hpp"
#include "nanobench.h"

#include "map_vs_hash.hpp"
#include "random_string.hpp"
#include <cstdint>
#include <fstream>

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

    void gen(
        std::string const& typeName,
        char const* mustacheTemplate,
        ankerl::nanobench::Bench const& bench)
    {
        std::ofstream templateOut("mustache.template." + typeName);
        templateOut << mustacheTemplate;

        std::ofstream renderOut("mustache.render." + typeName);
        ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
    }

} // namespace

TEST_CASE("Compare map and sort performance")
{
    const auto results = algorithm::get_sorted_strings_using_map(vec_100);
    REQUIRE(std::is_sorted(results.cbegin(), results.cend()));

    SECTION("Catch2 built-int benchmark")
    {
        BENCHMARK("map 10 elements using std::map")
        {
            return algorithm::get_sorted_strings_using_map(vec_10);
        };

        BENCHMARK("sort 10 elements using std::sort")
        {
            return algorithm::get_sorted_strings_using_sort(vec_10);
        };

        BENCHMARK("map 100 elements using std::map")
        {
            return algorithm::get_sorted_strings_using_map(vec_100);
        };

        BENCHMARK("sort 100 elements using std::sort")
        {
            return algorithm::get_sorted_strings_using_sort(vec_100);
        };

        BENCHMARK("map 1000 elements using std::map")
        {
            return algorithm::get_sorted_strings_using_map(vec_1000);
        };

        BENCHMARK("sort 1000 elements using std::sort")
        {
            return algorithm::get_sorted_strings_using_sort(vec_1000);
        };
    }

    SECTION("Use nanobench")
    {
        constexpr int warmupTimes = 3;
        SECTION("10 elements")
        {
            auto bench = ankerl::nanobench::Bench()
                             .title("10 elements")
                             .warmup(warmupTimes)
                             .relative(true)
                             .performanceCounters(true);

            bench.run(
                "Using std::map",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_map(vec_10));
                });

            bench.run(
                "Using std::sort",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_sort(vec_10));
                });

            gen("csv", ankerl::nanobench::templates::csv(), bench);
        }

        SECTION("100 elements")
        {
            auto bench = ankerl::nanobench::Bench()
                             .title("100 elements")
                             .warmup(warmupTimes)
                             .relative(true)
                             .performanceCounters(true);
            bench.run(
                "Using std::map",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_map(vec_100));
                });

            bench.run(
                "Using std::sort",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_sort(vec_100));
                });

            gen("csv", ankerl::nanobench::templates::csv(), bench);
        }

        SECTION("1000 elements")
        {
            auto bench = ankerl::nanobench::Bench()
                             .title("1000 elements")
                             .warmup(warmupTimes)
                             .relative(true)
                             .performanceCounters(true);
            bench.run(
                "Using std::map",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_map(vec_1000));
                });

            bench.run(
                "Using std::sort",
                []()
                {
                    ankerl::nanobench::doNotOptimizeAway(
                        algorithm::get_sorted_strings_using_sort(vec_1000));
                });

            gen("csv", ankerl::nanobench::templates::csv(), bench);
        }
    }
}
