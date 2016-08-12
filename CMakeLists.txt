cmake_minimum_required(VERSION 2.8)
project(mazer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -I/usr/local/include")
#set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-4/root/usr/bin/g++" )

#set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -lboost_program_options -g -L/usr/local/lib")
find_package(Boost 1.53.0 COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    set(SOURCE_FILES mazer.cpp Maze.cpp ArgHandler.cpp FileReader.cpp)
    add_executable(mazer ${SOURCE_FILES})

    target_link_libraries(mazer ${Boost_LIBRARIES})
endif()