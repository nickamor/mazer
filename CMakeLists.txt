cmake_minimum_required(VERSION 3.6)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -I/usr/local/include")
set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -lboost_program_options -g -L/usr/local/lib")

set(SOURCE_FILES mazer.cpp Maze.cpp ArgHandler.cpp FileReader.cpp)
add_executable(mazer ${SOURCE_FILES})