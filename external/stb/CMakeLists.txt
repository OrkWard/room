cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project(stb LANGUAGES CXX C)

include_directories(./)

add_library(
        stb_lib
        stb_image.cpp
        stb_image_write.cpp
        stb_image_resize.cpp
)