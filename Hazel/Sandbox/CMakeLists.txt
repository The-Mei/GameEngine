cmake_minimum_required(VERSION 3.17)

project(Sandbox)

file(GLOB_RECURSE SANDBOX_SRC
"./*.cpp"
"./*.c")


add_executable(${PROJECT_NAME} ${SANDBOX_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC Hazel)