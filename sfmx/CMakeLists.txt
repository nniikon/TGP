cmake_minimum_required(VERSION 3.10)

project(sfmx VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_library(sfmx STATIC
    source/sfmx_event.cpp
    source/sfmx_keyboard.cpp
    source/sfmx_mouse.cpp
    source/sfmx_render_window.cpp
    source/sfmx_sprite.cpp
    source/sfmx_texture.cpp
)

target_include_directories(sfmx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sfmx PRIVATE sfml-graphics sfml-window sfml-system)
