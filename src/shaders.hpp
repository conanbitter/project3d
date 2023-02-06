#pragma once

#include <glad/gl.h>
#include <string>

GLuint compileShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode);