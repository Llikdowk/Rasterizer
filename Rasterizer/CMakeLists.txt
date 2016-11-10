#project(RasterizerConfig)

set(SDL2_PATH D:/Libs/SDL2-2.0.5-mingw/i686-w64-mingw32)
#find_package(SDL2 REQUIRED)
set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include/)
set(SDL2_LIBRARY ${SDL2_PATH}/lib/libSDL2main.a ${SDL2_PATH}/lib/libSDL2.dll.a)

include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(src)