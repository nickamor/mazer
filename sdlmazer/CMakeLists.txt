find_package(Sdl2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_mixer REQUIRED)
# find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_net REQUIRED)
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sdlmazer main.cpp)
target_link_libraries(sdlmazer mazelib)

target_link_libraries(sdlmazer ${SDL2_LIBRARIES})
