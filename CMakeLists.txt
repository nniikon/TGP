cmake_minimum_required(VERSION 3.10)

project(tgp VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_subdirectory(sfmx)
add_subdirectory(exceptions)
add_subdirectory(containers)

add_library(tgp STATIC
    source/tgp_action.cpp
    source/tgp_button.cpp
    source/tgp_application.cpp
    source/tgp_window.cpp
)

target_link_libraries(tgp PRIVATE exceptions sfmx containers)

target_include_directories(tgp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $<TARGET_PROPERTY:containers,INTERFACE_INCLUDE_DIRECTORIES>
)
