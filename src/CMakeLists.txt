project(Rasterizer)
file(GLOB Rasterizer_SRC
        Private/*
        Public/*
        )
include_directories(Public)
add_executable(Rasterizer ${Rasterizer_SRC})
target_link_libraries(Rasterizer ${SDL2_LIBRARY})
install(TARGETS Rasterizer RUNTIME DESTINATION ${BIN_DIR})