cmake_minimum_required(VERSION 3.10)
project(matrix)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/test.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

include_directories(include)

add_executable(test ${SOURCES} ${HEADERS})
