cmake_minimum_required(VERSION 3.17)

project(glad)

file(GLOB_RECURSE SRC 
"src/*.c"
)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)