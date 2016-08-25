cmake_minimum_required(VERSION 2.8)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
#set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-4/root/usr/bin/g++" )

find_package(Boost 1.53.0 COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(include)

    set(SOURCE_FILES src/main.cpp src/Maze.cpp src/ArgHandler.cpp src/FileReader.cpp src/FileWriter.cpp src/VectorWriter.cpp src/Generator.cpp)
    add_executable(mazer ${SOURCE_FILES})

    target_link_libraries(mazer ${Boost_LIBRARIES})
endif()
