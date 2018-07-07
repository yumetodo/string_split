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
project(sample)

#
# Source files
#
set(sample_src
    "./sample.cpp"
)

#
# Compile
#
add_executable(sample ${sample_src})

#
# add Run task
#
add_custom_target(run_sample
    COMMAND sample
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS sample
    COMMENT "Execute produced executable."
)
