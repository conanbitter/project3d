#include "renderer.hpp"
#include <iostream>
#include <SDL.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

void Renderer::init(int width, int height) {
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    std::cout << "OpenGL version " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    glViewport(0, 0, width, height);
}

void Renderer::present() {}

void Renderer::setClearColor(uint8_t r, uint8_t g, uint8_t b) {
    glClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}