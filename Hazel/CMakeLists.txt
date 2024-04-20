cmake_minimum_required(VERSION 3.17)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Build/bin)

add_definitions(-DHZ_PLATFROM_WINDOWS)

set(CMAKE_CXX_FLAGS "-g -Wall")

project(Demo)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Hazel)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Sandbox)