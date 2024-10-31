cmake_minimum_required(VERSION 3.10)
set (CMAKE_C_COMPILER "/usr/bin/gcc")
project(qjmotor LANGUAGES C)
set(CMAKE_SYSROOT "/")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl ${CMAKE_CURRENT_SOURCE_DIR}/src /usr/local/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl/mac_lib /usr/local/lib)
link_libraries(lvgl SDL2)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(qjmotor ${SRCS})
