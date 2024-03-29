cmake_minimum_required(VERSION 3.16)

project(pr3d VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(pr3d
    src/common.hpp
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
    src/textures.hpp
    src/textures.cpp
    src/camera.hpp
    src/camera.cpp
    src/debug.cpp
    src/debug.hpp
)

target_include_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/include
        D:/Projects_C/Libs/glad/include
        D:/Projects_C/Libs/glm
        D:/Projects_C/Libs/stb
)

target_link_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/lib/x64
)

target_link_libraries(pr3d
    SDL2
    opengl32
)
