enable_testing()

# Add nanobench
FetchContent_Declare(
  nanobench
  GIT_REPOSITORY git@github.com:martinus/nanobench.git
  GIT_TAG master
  GIT_SHALLOW TRUE)
FetchContent_Populate(nanobench)

# Create the nanobench library
add_library(nanobench-lib STATIC nanobench.cpp)
target_include_directories(nanobench-lib
                           PUBLIC ${nanobench_SOURCE_DIR}/src/include)

set(TEST_EXECUTABLE map_vs_sort lookup)
foreach(test_executable ${TEST_EXECUTABLE})
  add_executable(${test_executable} ${test_executable}.cpp)
  target_link_libraries(${test_executable} Catch2::Catch2
                        Catch2::Catch2WithMain nanobench-lib)
  target_include_directories(
    ${test_executable} PRIVATE ${catch2_SOURCE_DIR}/src/
                               ${PROJECT_SOURCE_DIR}/src)
endforeach(test_executable)
