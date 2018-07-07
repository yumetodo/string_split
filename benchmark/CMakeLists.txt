cmake_minimum_required(VERSION 3.7)
enable_language(CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake/modules)

#
# C++ version
#
include(DecideCXXStanderd)
DECIDE_CXX_STANDERD()
message("CMAKE_CXX_STANDARD:${CMAKE_CXX_STANDARD}")

set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

#
# Set our project name
#
project(benchmark)

#
# Source files
#
set(benchmark_src
    "./benchmark.cpp"
)

#
# Compile
#
add_executable(benchmark ${benchmark_src})
