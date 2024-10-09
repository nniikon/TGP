cmake_minimum_required(VERSION 3.10)

project(containers VERSION 0.1)

add_library(containers INTERFACE)

target_include_directories(containers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/vector)
