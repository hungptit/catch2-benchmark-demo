# Why [Catch2](https://github.com/catchorg/Catch2) #

* Is simple and natural. Tests auto-register them self with any identifer, assertions look like normal C++ code, and sections offer a nice way to share set-up and tear-down test code.
* Provide simple micro-benchmarking features and simple BDD macros.

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

