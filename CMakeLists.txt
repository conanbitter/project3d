cmake_minimum_required(VERSION 3.16)

project(pr3d VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(pr3d
    src/main.cpp
    src/appwindow.hpp
    src/appwindow.cpp
    src/renderer.hpp
    src/renderer.cpp
    src/shaders.hpp
    src/shaders.cpp
    src/geometry.hpp
    src/mesh.hpp
    src/mesh.cpp
)

target_include_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/include
        D:/Projects_C/Libs/glad/include
)

target_link_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/lib/x64
)

target_link_libraries(pr3d
    SDL2
    opengl32
)
