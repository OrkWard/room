cmake_minimum_required(VERSION 3.10)

project(imgui LANGUAGES CXX)

aux_source_directory(. IMGUI_SRC)

add_library(imgui ${IMGUI_SRC})
