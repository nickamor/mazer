cmake_minimum_required(VERSION 2.8)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
#set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-4/root/usr/bin/g++" )

find_package(Boost 1.53.0 COMPONENTS REQUIRED program_options)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(include)

set(SOURCE_FILES src/arguments_parser.cc src/main.cc src/maze.cc src/maze_builder.cc src/maze_generator.cc src/maze_reader.cc src/maze_svg_writer.cc src/maze_writer.cc src/strong_random.cc)
add_executable(mazer ${SOURCE_FILES})

target_link_libraries(mazer ${Boost_LIBRARIES})

