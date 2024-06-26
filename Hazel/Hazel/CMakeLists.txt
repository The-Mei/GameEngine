cmake_minimum_required(VERSION 3.17)

add_definitions(-DHZ_BUILD_DLL -DGLFW_BUILD_WIN32 -DGLM_BUILD_LIBRARY -DVERSION_DEBUG)

project(Hazel)

set(OUTPUT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/export/
                   ${CMAKE_CURRENT_SOURCE_DIR}/precompile/
                   ${CMAKE_CURRENT_SOURCE_DIR}/src/Hazel/include
                   ${CMAKE_CURRENT_SOURCE_DIR}/3rd/spdlog/include
                   ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows
                   ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Opengl)

#set_source_files_properties(precompile/Hzpch.cpp
#                            PROPERTIES
#                            COMPILE_FLAGS "/Hzpch.h")

file(GLOB_RECURSE SRC
"src/Hazel/src/*.cpp"
"src/Hazel/src/*.c"
"src/Platform/*.cpp"
"src/Platform/*.c"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/imgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/stb_image)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw opengl32 glad imgui glm stb_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${OUTPUT_INCLUDE})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/precompile/Hzpch.h)