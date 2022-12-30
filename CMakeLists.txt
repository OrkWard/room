cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project("room" LANGUAGES CXX C)

set(EXTERN_DIR "${CMAKE_CURRENT_LIST_DIR}/external")
set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
include_directories(
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${EXTERN_DIR}/glfw/include"
        "${EXTERN_DIR}/glm"
)

add_subdirectory("${EXTERN_DIR}/glfw")

set(TARGET_NAME room_lib)
add_library(
        ${TARGET_NAME}
        ${SOURCE_DIR}/camera.cpp
        ${SOURCE_DIR}/transform.cpp
        ${SOURCE_DIR}/glad.c
        ${SOURCE_DIR}/glsl_program.cpp
        ${SOURCE_DIR}/model.cpp
        ${SOURCE_DIR}/stb_image.cpp)

set(TARGET_NAME room)
add_executable(
        ${TARGET_NAME}
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/entity.cpp
        ${SOURCE_DIR}/utility.cpp
        ${SOURCE_DIR}/window.cpp)
target_link_libraries(
        ${TARGET_NAME}
        glfw
        room_lib
)