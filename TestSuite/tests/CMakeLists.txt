#include_directories(${CMAKE_SOURCE_DIR}/kata2 ${CMAKE_SOURCE_DIR}/kata5 ${CMAKE_SOURCE_DIR}/data_structures)
#set(TEST_FILES kata2_test.cpp kata5_test.cpp vec_test.cpp)
project(test_suite)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Rasterizer/src/Public)
set(TEST_FILES Utils/Format.h Utils/Format.cpp sanity_check.cpp test_framebuffer.cpp test_color.cpp)
add_executable(test_suite ${TEST_FILES})
target_link_libraries(test_suite gtest gtest_main)
target_link_libraries(test_suite RasterizerLib)

#target_link_libraries(kata_test kata2 kata5)

