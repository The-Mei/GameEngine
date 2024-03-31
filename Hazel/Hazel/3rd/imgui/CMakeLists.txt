cmake_minimum_required(VERSION 3.17)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Build/bin)

project(imgui)


file(GLOB_RECURSE SRC 
"src/*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)