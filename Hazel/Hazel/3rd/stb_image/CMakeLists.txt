cmake_minimum_required(VERSION 3.17)

project(stb_image)


file(GLOB SRC 
"src/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)