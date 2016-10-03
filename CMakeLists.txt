cmake_minimum_required(VERSION 2.8)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

add_subdirectory(libmazer)
add_subdirectory(mazer)
add_subdirectory(mazer_tests)
