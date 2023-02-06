#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
   private:
    GLuint shaderId;

   public:
    Shader(const std::string vertexShaderCode, const std::string fragmentShaderCode);
    ~Shader();
    GLuint getId() { return shaderId; }

    int getUniformId(const std::string name);
};