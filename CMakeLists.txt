cmake_policy(SET CMP0048 NEW)
project(
  cppidioms
  VERSION 0.1.0
  LANGUAGES CXX)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(POSITION_INDEPENDENT_CODE ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.1)
FetchContent_MakeAvailable(Catch2)

# cmake-scripts
FetchContent_Declare(
  cmake_scripts
  GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
  GIT_TAG main
  GIT_SHALLOW TRUE)

FetchContent_Populate(cmake_scripts)

set(CMAKE_MODULE_PATH "${cmake_scripts_SOURCE_DIR}/;")
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
include(dependency-graph)

# Add sub-directories
add_subdirectory(unittests)
add_subdirectory(benchmark)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS src/*.cpp src/*.h benchmark/*.cpp)
find_program(CLANG_FORMAT NAMES clang-format)
add_custom_command(
  OUTPUT .format_cpp_stamp
  DEPENDS ${SRCS_AND_HDRS}
  COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
  COMMAND touch .format_cpp_stamp
  COMMENT "Format C++ files with clang-format."
  VERBATIM)

file(GLOB CMAKE_FILES CMakeLists.txt src/CMakeLists.txt
     unittests/CMakeLists.txt)
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .format_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .format_cmake_stamp
    COMMENT "Skip formatting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .format_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-format -i ${CMAKE_FILES}
    COMMAND touch .format_cmake_stamp
    COMMENT "Format CMake files with cmake-format."
    VERBATIM)
endif()

add_custom_target(
  format
  DEPENDS .format_cpp_stamp .format_cmake_stamp
  COMMENT "Format C++ and CMake files.")

add_custom_command(
  OUTPUT .lint_cmake_stamp
  DEPENDS ${CMAKE_FILES}
  COMMAND cmake-lint ${CMAKE_FILES}
  COMMAND touch .lint_cmake_stamp
  COMMENT "Lint CMake files with cmake-lint.")

add_custom_target(
  lint ALL
  DEPENDS .lint_cmake_stamp
  COMMENT "Lint CMake files.")

enable_testing()
