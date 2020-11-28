cmake_minimum_required(VERSION 3.17)

project(tinyrenderer)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/googletest)

add_subdirectory(lib/tgaimage)
add_subdirectory(lib/geometry)
add_subdirectory(lib/wavefrontobjloader)

add_executable(tinyrenderer
        src/main.cpp)

target_link_libraries(tinyrenderer PRIVATE
        tgaimage
        geometry
        wavefrontobjloader)