cmake_minimum_required(VERSION 3.17)

project(imgui)


file(GLOB SRC 
"imgui_demo.cpp"
"imgui_draw.cpp"
"imgui_tables.cpp"
"imgui_widgets.cpp"
"imgui.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})