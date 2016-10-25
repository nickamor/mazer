set(SOURCES src/maze.cpp
        src/generator.cpp
        src/solver.cpp
        src/mazer.cpp
        src/reader.cpp
        src/writer.cpp
        src/generators/aldousbroder.cpp
        src/generators/eller.cpp
        src/writers/svgwriter.cpp
        src/writers/binwriter.cpp src/solvers/bfs_solver.cpp src/solvers/dfs_solver.cpp src/solvers/dijkstra_solver.cpp)
add_library(mazelib ${SOURCES})
target_include_directories (mazelib PUBLIC include)
