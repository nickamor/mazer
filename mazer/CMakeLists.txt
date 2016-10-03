cmake_minimum_required(VERSION 2.8)
project(mazer)

#set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-4/root/usr/bin/g++" )

find_package(Boost 1.53.0 COMPONENTS REQUIRED program_options)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(include)

set(SOURCE_FILES src/arguments_parser.cc
        src/main.cc)
add_executable(mazer ${SOURCE_FILES})

target_link_libraries(mazer ${Boost_LIBRARIES})
target_link_libraries(mazer libmazer)
