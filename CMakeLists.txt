cmake_minimum_required(VERSION 3.16)

project(pr3d VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(pr3d
    src/main.cpp
    src/app.hpp
    src/app.cpp
)

target_include_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/include
)

target_link_directories(pr3d
    PUBLIC
        D:/Projects_C/Libs/sdl2vc/lib/x64
)

target_link_libraries(pr3d
    SDL2
    opengl32
)
