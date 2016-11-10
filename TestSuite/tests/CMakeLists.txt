#include_directories(${CMAKE_SOURCE_DIR}/kata2 ${CMAKE_SOURCE_DIR}/kata5 ${CMAKE_SOURCE_DIR}/data_structures)
#set(TEST_FILES kata2_test.cpp kata5_test.cpp vec_test.cpp)
project(test_suite)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_FILES sanity_check.cpp)
add_executable(test_suite ${TEST_FILES})
target_link_libraries(test_suite gtest gtest_main)

#target_link_libraries(kata_test kata2 kata5)

