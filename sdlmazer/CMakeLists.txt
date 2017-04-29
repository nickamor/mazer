find_package(Sdl2 REQUIRED)

# Find SDL2_image
find_file(SDL2_IMAGE_INCLUDE_DIRS NAMES SDL_image.h HINT SDL2)
find_library(SDL2_IMAGE_LIBRARIES NAMES SDL2_image SDL2-image HINT SDL2)

# Find SDL2_mixer
find_file(SDL2_MIXER_INCLUDE_DIRS NAMES SDL_mixer.h HINT SDL2)
find_library(SDL2_MIXER_LIBRARIES NAMES SDL2_mixer SDL2-mixer HINT SDL2)

# Find SDL2_ttf
find_file(SDL2_TTF_INCLUDE_DIRS NAMES SDL_ttf.h HINT SDL2)
find_library(SDL2_TTF_LIBRARIES NAMES SDL2_ttf SDL2-ttf HINT SDL2)

# Find SDL2_net
find_file(SDL2_NET_INCLUDE_DIRS NAMES SDL_net.h HINT SDL2)
find_library(SDL2_NET_LIBRARIES NAMES SDL2_net SDL2-net HINT SDL2)

set(SDL2_INCLUDE_DIRS 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS} 
    ${SDL2_NET_INCLUDE_DIRS})

set(SDL2_LIBRARIES 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_NET_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sdlmazer main.cpp)
target_link_libraries(sdlmazer mazelib)

target_link_libraries(sdlmazer ${SDL2_LIBRARIES})
