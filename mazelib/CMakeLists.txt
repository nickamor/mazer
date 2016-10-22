set(SOURCES maze.cpp 
    generator.cpp 
    solver.cpp 
    mazer.cpp 
    reader.cpp 
    writer.cpp
    generators/aldousbroder.cpp
    generators/eller.cpp)
add_library(mazelib ${SOURCES})
target_include_directories (mazelib PUBLIC include)
