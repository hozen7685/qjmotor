cmake_minimum_required(VERSION 3.30)
if(MAC)
include(${CMAKE_CURRENT_LIST_DIR}/env_cmake/mac.cmake)
endif()
project(qjmotor LANGUAGES C)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(qjmotor ${SRCS})
