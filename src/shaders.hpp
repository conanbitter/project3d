#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
   private:
    GLuint shaderId;

   public:
    const GLuint INVALID_SHADER = 0;

    Shader() : shaderId(INVALID_SHADER) {}
    Shader(const char* vertexShaderCode, const char* fragmentShaderCode);
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept {
        shaderId = other.shaderId;
        other.shaderId = INVALID_SHADER;
    }
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept {
        shaderId = other.shaderId;
        other.shaderId = INVALID_SHADER;
        return *this;
    }
    ~Shader();
    GLuint getId() const { return shaderId; }

    int getUniformId(const std::string name);

    static void compileAllShaders();
    static Shader mainShader;
};