cmake_minimum_required(VERSION 3.23)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

set(GOOGLETEST_VERSION 1.14.0)
add_subdirectory(googletest/googletest)
enable_testing()

add_executable(lab1 main.cpp  FlatMap.cpp)

target_link_libraries(lab1 gtest_main)
