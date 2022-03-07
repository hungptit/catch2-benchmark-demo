project(cppidioms LANGUAGES CXX)
cmake_minimum_required(VERSION 3.15)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_ALL_WARNINGS ON)

# Only enable this option for non-Windows platforms.
if(NOT MSVC)
  add_compile_options(-ftime-report)
endif()

include(FetchContent)

# cmake-scripts
FetchContent_Declare(
  cmake_scripts
  GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
  GIT_TAG main)
FetchContent_Populate(cmake_scripts)
set(CMAKE_MODULE_PATH "${cmake_scripts_SOURCE_DIR}/;")
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
include(dependency-graph)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG devel)
FetchContent_MakeAvailable(Catch2)

# Add sub-directories
add_subdirectory(unittests)
add_subdirectory(benchmark)

# Format all CMake and C++ files
file(GLOB_RECURSE SRCS_AND_HDRS src/*.cpp src/*.h benchmark/*.cpp
     unittests/*.cpp)
find_program(CLANG_FORMAT NAMES clang-format)
if(${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .format_cpp_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .format_cpp_stamp
    COMMENT "Skip formatting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .format_cpp_stamp
    DEPENDS ${SRCS_AND_HDRS}
    COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
    COMMAND touch .format_cpp_stamp
    COMMENT "Format C++ files with clang-format."
    VERBATIM)
endif()

file(GLOB CMAKE_FILES CMakeLists.txt src/CMakeLists.txt
     benchmark/CMakeLists.txt unittests/CMakeLists.txt)
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

# Lint Bash scripts
file(GLOB SH_SRCS *.sh)
find_program(SHELLCHECK NAMES shellcheck)
if(${SHELLCHECK} STREQUAL "SHELLCHECK-NOTFOUND")
  add_custom_command(
    OUTPUT .lint_shellcheck_stamp
    DEPENDS ${SH_SRCS}
    COMMAND echo "Skip linting Bash scripts."
    COMMENT "Skip linting Bash scripts."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .lint_shellcheck_stamp
    DEPENDS ${SH_SRCS}
    COMMAND shellcheck ${SH_SRCS}
    COMMAND touch .lint_shellcheck_stamp
    COMMENT "Lint Bash files with shellcheck.")
endif()

# Lint all CMake files
find_program(CMAKE_LINT NAMES cmake-lint)
if(${CMAKE_LINT} STREQUAL "CMAKE_LINT-NOTFOUND")
  add_custom_command(
    OUTPUT .lint_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND echo "Could not find cmake-lint. Skip linting CMake files."
    COMMENT "Could not find cmake-lint. Skip linting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .lint_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-lint ${CMAKE_FILES}
    COMMAND touch .lint_cmake_stamp
    COMMENT "Lint CMake files with cmake-format."
    VERBATIM)
endif()

add_custom_target(
  lint ALL
  DEPENDS .lint_shellcheck_stamp .lint_cmake_stamp
  COMMENT "Lint Bash and CMake files.")
