project(LMath)

file(GLOB LMath_SRC
        Private/*
        Public/*
)

include_directories(Public)
add_library(LMath STATIC ${LMath_SRC})
