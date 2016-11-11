project(Rasterizer)

file(GLOB Rasterizer_SRC
        Private/*
        Public/*
)

include_directories(Public)
add_library(LRasterizer STATIC ${Rasterizer_SRC})
add_executable(Rasterizer EntryPoint.cpp)
target_link_libraries(Rasterizer LRasterizer ${SDL2_LIBRARY})
install(TARGETS Rasterizer RUNTIME DESTINATION ${BIN_DIR})
