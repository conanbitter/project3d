#pragma once

#include <glad/gl.h>
#include <stdint.h>
#include <vector>
#include "mesh.hpp"
#include "shaders.hpp"

class Mesh;

class Renderer {
   private:
    int width;
    int height;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

   public:
    Renderer() = default;
    ~Renderer();
    void init(int width, int height);
    void setShader(const Shader shader);
    void draw(const Mesh& mesh);
    void present();
    void setClearColor(uint8_t r, uint8_t g, uint8_t b);
    void clear();
};