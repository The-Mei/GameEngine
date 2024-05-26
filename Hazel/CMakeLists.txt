cmake_minimum_required(VERSION 3.17)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin)

add_definitions(-DHZ_PLATFROM_WINDOWS)
set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS "-O3 -w")

add_definitions(-DRESROOT="${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/")

project(Demo)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Hazel)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)