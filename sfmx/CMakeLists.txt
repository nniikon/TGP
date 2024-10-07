cmake_minimum_required(VERSION 3.10)

project(sfmx VERSION 0.1)

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
