cmake_minimum_required(VERSION 3.10)

project(tgp VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_subdirectory(sfmx)

add_library(tgp STATIC
    source/tgp_button.cpp
    source/tgp_application.cpp
    source/tgp_window.cpp
)

target_link_libraries(tgp PRIVATE sfmx sfml-graphics sfml-window sfml-system)

target_include_directories(tgp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tgp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sfmx/include)
