add_executable(test_ab test_ab.cpp)
target_link_libraries(test_ab mazelib)

add_test(test_ab test_ab)