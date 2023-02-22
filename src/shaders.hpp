#pragma once

#include <glad/gl.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
   private:
    GLuint shaderId;
    GLuint mvp;

   public:
    const GLuint INVALID_SHADER = 0;

    Shader() : shaderId(INVALID_SHADER) {}
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept {
        shaderId = other.shaderId;
        other.shaderId = INVALID_SHADER;
    }
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept {
        if (glIsProgram(shaderId)) {
            glDeleteProgram(shaderId);
        }
        shaderId = other.shaderId;
        other.shaderId = INVALID_SHADER;
        return *this;
    }
    ~Shader();

    void LoadFromString(const char* vertexShaderCode, const char* fragmentShaderCode);
    void LoadFromFile(const char* vertexShaderFile, const char* fragmentShaderFile);
    GLuint getId() const { return shaderId; }

    int getUniformId(const std::string name);
    void updateUniformMat(int id, const glm::mat4x4& matrix);
    bool hasMVP() { return mvp >= 0; }
    void updateMVP(const glm::mat4x4& matrix);

    static void compileAllShaders();
    static Shader mainShader;
};