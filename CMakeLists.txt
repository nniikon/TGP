cmake_minimum_required(VERSION 3.10)

project(tgp VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(tgp STATIC
    source/tgp_button.cpp
    source/tgp_button_manager.cpp
    source/tgp_image.cpp
    source/tgp_image_manager.cpp
    source/tgp_pixel_area.cpp
    source/tgp_pixel_area_manager.cpp
    source/tgp_vectors.tpp
    source/tgp_window.cpp
)

target_include_directories(tgp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
