cmake_minimum_required(VERSION 3.10)
set (CMAKE_C_COMPILER "gcc.exe")
project(qjmotor LANGUAGES C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl/lib)
link_libraries(lvgl)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(qjmotor ${SRCS})
