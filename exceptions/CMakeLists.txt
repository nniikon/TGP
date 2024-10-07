cmake_minimum_required(VERSION 3.10)

project(exceptions VERSION 0.1)

add_library(exceptions STATIC
    source/tgp_exceptions.cpp
)

target_include_directories(exceptions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
