#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
   private:
    GLuint shaderId;

   public:
    Shader() {}
    Shader(const char* vertexShaderCode, const char* fragmentShaderCode);
    ~Shader();
    GLuint getId() const { return shaderId; }

    int getUniformId(const std::string name);

    static void compileAllShaders();
    static Shader mainShader;
};