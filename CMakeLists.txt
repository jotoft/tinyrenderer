project(tinyrenderer)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/tgaimage)

add_executable(tinyrenderer
        src/main.cpp)

target_link_libraries(tinyrenderer PRIVATE
        tgaimage)