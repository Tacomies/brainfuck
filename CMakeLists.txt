cmake_minimum_required(VERSION 3.10)

project(Brainfuck_compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER /bin/g++)

find_program(GPP_EXECUTABLE NAMES g++)

if(GPP_EXECUTABLE)
    message(STATUS "Found g++ compiler: ${GPP_EXECUTABLE}")
else()
    message(FATAL_ERROR "g++ compiler not found! Make sure it is installed or adjust CMake configuration.")
endif()

set(CMAKE_CXX_COMPILER ${GPP_EXECUTABLE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(bfc ${SOURCES})
