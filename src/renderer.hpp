#pragma once

#include <glad/gl.h>
#include <stdint.h>

class Renderer {
   private:
    int width;
    int height;
    GLuint vao;
    GLuint vbo;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

   public:
    Renderer() = default;
    ~Renderer();
    void init(int width, int height);
    void present();
    void setClearColor(uint8_t r, uint8_t g, uint8_t b);
    void clear();
};