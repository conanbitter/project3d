#include "renderer.hpp"
#include "geometry.hpp"
#include <iostream>
#include <SDL.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

const GLuint VERTEX_POSITION_LOCATION = 0;
const GLuint VERTEX_NORMAL_LOCATION = 1;
const GLuint VERTEX_TANGENT_LOCATION = 2;
const GLuint VERTEX_UV_LOCATION = 3;

void Renderer::init(int width, int height) {
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    std::cout << "OpenGL version " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
    glVertexAttribPointer(VERTEX_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)sizeof(Vector3D));
    glEnableVertexAttribArray(VERTEX_TANGENT_LOCATION);
    glVertexAttribPointer(VERTEX_TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(sizeof(Vector3D) * 2));
    glEnableVertexAttribArray(VERTEX_UV_LOCATION);
    glVertexAttribPointer(VERTEX_UV_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(sizeof(Vector3D) * 3));
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

Renderer::~Renderer() {
    if (glIsBuffer(ebo)) {
        glDeleteBuffers(1, &ebo);
    }
    if (glIsBuffer(vbo)) {
        glDeleteBuffers(1, &vbo);
    }
    if (glIsVertexArray(vao)) {
        glDeleteVertexArrays(1, &vao);
    }
}

void Renderer::draw(const Mesh &mesh) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.size() * sizeof(Triangle), mesh.faces.data(), GL_DYNAMIC_DRAW);
    glDrawElements(GL_TRIANGLES, mesh.faces.size() * 3, GL_UNSIGNED_INT, NULL);
}

void Renderer::present() {}

void Renderer::setClearColor(uint8_t r, uint8_t g, uint8_t b) {
    glClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setShader(const Shader &shader) {
    glUseProgram(shader.getId());
}