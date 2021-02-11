#include <algorithm>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define BENCHMARK_ADVANCED
#include "catch2/catch.hpp"

#include "random_string.hpp"
#include <cstdint>
#include <set>
#include <unordered_set>

namespace {}

SCENARIO(
    "Performance comparison for different approach for looking up an item.") {
  utils::RandomStringGenerator rgn;
  constexpr std::uint32_t number_of_elements = 10;
  constexpr std::uint32_t len = 32;
  std::vector<std::string> data(number_of_elements);
  for (std::uint32_t idx = 0; idx < number_of_elements; ++idx) {
    data[idx] = rgn(len);
  }

  const std::set<std::string> lookup_set(data.cbegin(), data.cend());
  const std::unordered_set<std::string> lookup_hash(data.cbegin(), data.cend());

  const auto needle = data[number_of_elements - 1];
  BENCHMARK("O(n) algorithm") {
    return std::any_of(data.cbegin(), data.cend(),
                       [&needle](auto &val) { return val == needle; });
  };

  BENCHMARK("O(1) algorithm") { return lookup_hash.count(needle); };

  BENCHMARK("O(log(n)) algorithm") { return lookup_set.count(needle); };
}
