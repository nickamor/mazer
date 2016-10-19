set(SOURCES maze.cpp generator.cpp solver.cpp mazer.cpp reader.cpp reader.h writer.cpp writer.h)
add_library(mazelib ${SOURCES})
target_include_directories (mazelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
