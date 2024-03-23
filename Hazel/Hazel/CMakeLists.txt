cmake_minimum_required(VERSION 3.17)

add_definitions(-DHZ_BUILD_DLL)

project(Hazel)

set(OUTPUT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/export/
                   ${CMAKE_CURRENT_SOURCE_DIR}/src/Hazel/include
                   ${CMAKE_CURRENT_SOURCE_DIR}/3rd/spdlog/include)

file(GLOB_RECURSE SRC
"src/Hazel/src/*.cpp"
"src/Hazel/src/*.c"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Hazel/include)


add_library(${PROJECT_NAME} SHARED ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${OUTPUT_INCLUDE})