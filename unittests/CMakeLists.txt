set(TEST_EXECUTABLES algorithm_test bdd_test objects_test matcher_test
                     exception_test)
foreach(test_executable ${TEST_EXECUTABLES})
  add_executable(${test_executable} ${test_executable}.cpp)
  target_link_libraries(${test_executable} Catch2::Catch2
                        Catch2::Catch2WithMain)
  target_include_directories(
    ${test_executable} PRIVATE ${catch2_SOURCE_DIR}/src/
                               ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR})
  add_test(${test_executable} ./${test_executable})
endforeach(test_executable)

enable_testing()
