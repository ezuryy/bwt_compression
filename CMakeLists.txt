cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")

# libraries
add_library(common_files STATIC
		${CMAKE_CURRENT_SOURCE_DIR}/source/functions.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/BWT.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/source/LZW.cpp
		)
target_include_directories(common_files PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)

# main
add_executable(main
		${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
target_include_directories(main PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main common_files)

# gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_compression
		${CMAKE_CURRENT_SOURCE_DIR}/source/test.cpp)
target_include_directories(test_compression PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_compression gtest_main common_files)

include(GoogleTest)
gtest_discover_tests(test_compression)

enable_testing()
