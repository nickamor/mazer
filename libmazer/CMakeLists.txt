cmake_minimum_required(VERSION 2.8)
project(mazer)

set(SOURCE_FILES src/maze.cc
        src/maze_builder.cc
        src/maze_generator.cc
        src/maze_reader.cc
        src/maze_svg_writer.cc
        src/maze_writer.cc
        src/strong_random.cc
        src/generators/aldousbroder_generator.cc
        src/generators/eller_generator.cc)

include_directories(include)

add_library(libmazer STATIC ${SOURCE_FILES})
