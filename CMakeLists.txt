cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project("room" LANGUAGES CXX C)

set(EXTERN_DIR "${CMAKE_CURRENT_LIST_DIR}/external")
set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${EXTERN_DIR}/glfw/include
        ${EXTERN_DIR}/glm
        ${EXTERN_DIR}/imgui
        ${EXTERN_DIR}
)

add_subdirectory(${EXTERN_DIR}/glfw)
add_subdirectory(${EXTERN_DIR}/imgui)
add_subdirectory(${EXTERN_DIR}/stb)
add_subdirectory(${EXTERN_DIR}/imguiFileDialog)

set(TARGET_NAME room)
add_executable(
        ${TARGET_NAME}
        ${SOURCE_DIR}/camera.cpp
        ${SOURCE_DIR}/glad.c
        ${SOURCE_DIR}/glsl_program.cpp
        ${SOURCE_DIR}/model.cpp
        ${SOURCE_DIR}/texture.cpp
        ${SOURCE_DIR}/texture2d.cpp
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/entity.cpp
        ${SOURCE_DIR}/utility.cpp
        ${SOURCE_DIR}/window.cpp
)
target_link_libraries(
        ${TARGET_NAME}
        glfw
        imgui
        imguiFileDialog
        stb_lib
)