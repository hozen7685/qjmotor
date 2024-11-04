set (CMAKE_C_COMPILER "gcc")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl ${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lvgl/lib)
link_libraries(lvgl)
