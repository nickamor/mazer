cmake_minimum_required(VERSION 2.8)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
#set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-4/root/usr/bin/g++" )

find_package(Boost 1.53.0 COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(include)

    set(SOURCE_FILES src/main.cpp src/maze.cpp src/arguments_parser.cpp src/reader.cpp src/writer.cpp src/svg_writer.cpp src/generator.cpp src/strong_random.cpp include/strong_random.h)
    add_executable(mazer ${SOURCE_FILES})

    target_link_libraries(mazer ${Boost_LIBRARIES})
endif()
