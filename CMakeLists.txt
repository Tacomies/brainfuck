cmake_minimum_required(VERSION 3.10)

project(Brainfuck_compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER /bin/gcc)
set(CMAKE_CXX_COMPILER /bin/g++)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(bfc ${SOURCES})
