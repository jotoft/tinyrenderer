add_library(wavefrontobjloader
        src/model.cpp)

target_include_directories(wavefrontobjloader PUBLIC
        inc)

target_link_libraries(wavefrontobjloader PUBLIC
        geometry)