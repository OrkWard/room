cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(fileDialog LANGUAGES C CXX)

include_directories(
        ./
        ../
)

add_library(
        imguiFileDialog
        ImGuiFileDialog.cpp
)