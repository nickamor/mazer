set(SOURCES main.cpp argumentparser.cpp task.cpp timer.cpp)
add_executable(mazer ${SOURCES})

target_link_libraries(mazer mazelib)
