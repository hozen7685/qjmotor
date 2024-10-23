cmake_minimum_required(VERSION 3.10)
set (CMAKE_C_COMPILER "gcc")
project(qjmotor LANGUAGES C)
set(CMAKE_SYSROOT "/")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl/mac_lib)
link_libraries(lvgl sdl2)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(qjmotor ${SRCS})
