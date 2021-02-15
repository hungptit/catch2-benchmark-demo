# Why [Catch2](https://github.com/catchorg/Catch2) #

* Is simple and natural. Tests auto-register them self with any identifer, assertions look like normal C++ code, and sections offer a nice way to share set-up and tear-down test code.
* Provide simple micro-benchmarking features and simple BDD macros.

# A very short introduction to Catch2 features #


## Assertions ##

**REQUIRE**

Abort the test executable if the condition is false. This is very handy assertion which makes sure that we do not go too far if our expectation is not met (e.g cannot load the workbook).


``` c++
REQUIRE(isAvailable());
```


**CHECK**

**CHECK_THAT**



**CHECK_THROWS**

**TEST_CASE or TAB_TEST_CASE**

**SECTION**

**SCENARIO**

**GIVEN**

**WHEN**

**BENCHMARK**

# Howto #

## How to build Catch2 demos on Linux/macOS  ##

``` shell
cmake . -DCMAKE_BUILD_TYPE=Release
make -j9
```

**Run all tests**

``` shell
make test -j2
```

**Run a demo benchmark**

``` shell
./benchmark/map_vs_sort --benchmark-no-analysis --benchmark-warmup-time 100
```

Below is the sample results

``` text
(venv) hungdang-ltm:catch2-benchmark-demo hung.dang$ ./benchmark/map_vs_sort --benchmark-no-analysis --benchmark-warmup-time 100

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
map_vs_sort is a Catch v2.13.1 host application.
Run with -? for options

-------------------------------------------------------------------------------
Compare map and sort performance
-------------------------------------------------------------------------------
/Users/hung.dang/working/catch2-benchmark-demo/benchmark/map_vs_sort.cpp:26
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
map 10 elements                                100             6    3.71861 us
sort 10 elements                               100            26    1.36257 us
map 100 elements                               100             1    49.9425 us
sort 100 elements                              100             3    26.8724 us
map 1000 elements                              100             1    462.453 us
sort 1000 elements                             100             1    219.375 us

===============================================================================
test cases: 1 | 1 passed
assertions: - none -
```

## How to build Catch2 demos on Windows  ##

``` powershell
cmake -G "Visual Studio 14 2015"  -A x64 .
cmake --build . --config Release -- /maxcpucount
```

**Run all tests**

``` powershell
ctest -j3
```

**Run benchmarks**

``` powershell
benchmark\Release\lookup.exe --benchmark-no-analysis
```

Below is the sample results collected using my Windows machine

``` text
tsi\hdang@NTRAN2 D:\experiments\catch2-benchmark-demo>benchmark\Release\map_vs_sort.exe --benchmark-no-analysis

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
map_vs_sort.exe is a Catch v2.13.1 host application.
Run with -? for options

-------------------------------------------------------------------------------
Compare map and sort performance
-------------------------------------------------------------------------------
D:\experiments\catch2-benchmark-demo\benchmark\map_vs_sort.cpp(27)
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
map 10 elements                                100            18    3.75472 us
sort 10 elements                               100            40     1.6397 us
map 100 elements                               100             2     43.879 us
sort 100 elements                              100             3    22.4593 us
map 1000 elements                              100             1     613.04 us
sort 1000 elements                             100             1    309.522 us
advanced                                       100             1    305.267 us

===============================================================================
test cases: 1 | 1 passed
assertions: - none -

```

# Writing test/benchmark using BDD style #

Consider this simple benchmark code that analyses the effect of cache locality on the performance of diferent lookup algorithms

``` c++
SCENARIO(
    "Performance comparison for different approach for looking up a std::string item.") {
  GIVEN("There are 10 items and the size of each item is 32.") {
      run_string_perf(10, 32);
  }

  GIVEN("There are 10 items and the size of each item is 16.") {
      run_string_perf(10, 16);
  }

  GIVEN("There are 50 items and the size of each item is 32.") {
      run_string_perf(50, 32);
  }

  GIVEN("There are 50 items and the size of each item is 16.") {
     run_string_perf(50, 16);
  }
}
```

**What does the above code do?**

* Create a performance benchmark scenario for looking up a string using std::vector, std::set, and std::unordered_set.
* For each studied look up table size run the benchmark with different type of look-up keys.

Compare with other benchmarking framework suche as Google benchmark, Celero, and nonious etc this syntax look more natural and below is the parital output of the benchmark.
It is obvious that Catch2 automates all of the registration work us and it also provides very descriptive output. Most of the existing testing frameworks (except [doctest](https://github.com/onqtam/doctest)) do not
provide this functionality.

``` c++
./benchmark/lookup --benchmark-no-analysis
...

-------------------------------------------------------------------------------
Scenario: Performance comparison for different approach for looking up a std::
          string item.
      Given: There are 10 items and the size of each item is 16.
       When: The matched item is at the end of the vector
-------------------------------------------------------------------------------
/Users/hung.dang/working/catch2-benchmark-demo/benchmark/lookup.cpp:23
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
O(n) algorithm                                 100          2333    16.9626 ns
O(1) algorithm                                 100          1259    20.6444 ns
O(log(n)) algorithm                            100          1400    28.5404 ns

-------------------------------------------------------------------------------
Scenario: Performance comparison for different approach for looking up a std::
          string item.
      Given: There are 10 items and the size of each item is 16.
       When: The matched item is at the middle of the vector
-------------------------------------------------------------------------------
/Users/hung.dang/working/catch2-benchmark-demo/benchmark/lookup.cpp:36
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
O(n) algorithm                                 100          2216    16.6652 ns
O(1) algorithm                                 100          1697     21.426 ns
O(log(n)) algorithm                            100          2409    14.3842 ns

-------------------------------------------------------------------------------
Scenario: Performance comparison for different approach for looking up a std::
          string item.
      Given: There are 10 items and the size of each item is 16.
       When: The matched item is at the beginning of the vector
-------------------------------------------------------------------------------
/Users/hung.dang/working/catch2-benchmark-demo/benchmark/lookup.cpp:49
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
O(n) algorithm                                 100          5562    7.32783 ns
O(1) algorithm                                 100          1691    21.4104 ns
O(log(n)) algorithm                            100          1318     28.365 ns
```

# How to run Tableau's Catch2 tests #


