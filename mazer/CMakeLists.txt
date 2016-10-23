find_package(Boost 1.53.0 COMPONENTS REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(mazer main.cpp)

target_link_libraries(mazer mazelib)
target_link_libraries(mazer ${Boost_LIBRARIES})
