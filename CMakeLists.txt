cmake_minimum_required(VERSION 2.6)
project(RasterizerConfig)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${RasterizerConfig_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${RasterizerConfig_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=gnu++11 -lmingw32")

#if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
#elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
#    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
#        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#    else()
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#    endif()
#endif()

# Look up SDL2 and add the include directory to our include path
set(SDL2_PATH D:/Libs/SDL2-2.0.5-mingw/i686-w64-mingw32)
set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include/SDL)
#find_package(SDL2 REQUIRED)
set(SDL2_LIBRARY ${SDL2_PATH}/lib/libSDL2main.a ${SDL2_PATH}/lib/libSDL2.dll.a)
set(SDL2_INCLUDE_DIR D:/Libs/SDL2-2.0.5-mingw/i686-w64-mingw32/include/SDL2)
include_directories(${SDL2_INCLUDE_DIR})
# Look in the Lesson0 subdirectory to find its CMakeLists.txt so we can build the executable
add_subdirectory(src)