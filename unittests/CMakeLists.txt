enable_testing()

set(TEST_EXECUTABLE algorithm_test bdd_test)
foreach(test_executable ${TEST_EXECUTABLE})
  add_executable(${test_executable} ${test_executable}.cpp)
  target_include_directories(
    ${test_executable} PRIVATE ${catch2_SOURCE_DIR}/single_include/
                               ${ROOT_DIR}/src)
  add_test(${test_executable} ./${test_executable})
endforeach(test_executable)
