enable_testing()

set(TEST_EXECUTABLE map_vs_sort lookup)
foreach(test_executable ${TEST_EXECUTABLE})
  add_executable(${test_executable} ${test_executable}.cpp)
  target_include_directories(
    ${test_executable} PRIVATE ${catch2_SOURCE_DIR}/single_include/
    ${ROOT_DIR}/src)
endforeach(test_executable)
