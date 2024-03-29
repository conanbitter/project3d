#include "common.hpp"

std::string getShaderLog(GLuint shader) {
    if (glIsShader(shader)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;

        return message;
    } else {
        return "Wrong shader handle";
    }
}

std::string getProgramLog(GLuint shaderProgram) {
    if (glIsProgram(shaderProgram)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        glGetProgramInfoLog(shaderProgram, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;
        return message;
    } else {
        return "Wrong shader program handle";
    }
}

GLuint compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const GLchar* lines[] = {
        source};
    glShaderSource(shader, 1, lines, NULL);
    glCompileShader(shader);
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled != GL_TRUE) {
        std::string msg;
        if (shaderType == GL_VERTEX_SHADER) {
            msg = "Vertex shader compile error: ";
        } else if (shaderType == GL_FRAGMENT_SHADER) {
            msg = "Fragment shader compile error: ";
        } else {
            msg = "Shader compile error: ";
        }
        std::cout << msg << getShaderLog(shader) << std::endl;
        return 0;
    }
    return shader;
}

GLuint compileShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
    GLuint program = glCreateProgram();

    GLuint compiledVertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint compiledFragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    glAttachShader(program, compiledVertexShader);
    glAttachShader(program, compiledFragmentShader);
    glLinkProgram(program);
    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        std::cout << "Shader link error: " << getProgramLog(program) << std::endl;
        return 0;
    }
    glDeleteShader(compiledVertexShader);
    glDeleteShader(compiledFragmentShader);
    return program;
};

char* readFile(const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* result = new char[size + 1];
    file.read(result, size);
    file.close();
    result[size] = '\0';
    return result;
}

void Shader::loadFromString(const char* vertexShaderCode, const char* fragmentShaderCode) {
    shaderId = compileShaderProgram(vertexShaderCode, fragmentShaderCode);
    glUseProgram(shaderId);
    mvp = glGetUniformLocation(shaderId, "mvp");
    GLint diffMap = glGetUniformLocation(shaderId, "diffuseMap");
    if (diffMap >= 0) {
        glUniform1i(diffMap, Texture::DiffuseMap - GL_TEXTURE0);
        // std::cout << "set" << std::endl;
    }
    GLint normMap = glGetUniformLocation(shaderId, "normalMap");
    if (normMap >= 0) {
        glUniform1i(normMap, Texture::NormalMap - GL_TEXTURE0);
        // std::cout << "set" << std::endl;
    }
    // std::cout << mvp << " " << diffMap << " " << normMap << std::endl;
    std::cout << "Shader " << shaderId << " created" << std::endl;
}

PShader Shader::LoadFromFile(const char* vertexShaderFile, const char* fragmentShaderFile) {
    char* vertCode = readFile(vertexShaderFile);
    char* fragCode = readFile(fragmentShaderFile);
    PShader result = std::make_shared<Shader>();
    result->loadFromString(vertCode, fragCode);
    delete fragCode;
    delete vertCode;
    return result;
}

Shader::~Shader() {
    if (glIsProgram(shaderId)) {
        std::cout << "Shader " << shaderId << " deleted" << std::endl;
        glDeleteProgram(shaderId);
    }
}

int Shader::getUniformId(const std::string name) {
    return glGetUniformLocation(shaderId, name.c_str());
}

void Shader::updateUniformMat(int id, const glm::mat4x4& matrix) {
    glUseProgram(shaderId);
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::updateMVP(const glm::mat4x4& matrix) {
    if (mvp >= 0) {
        glUseProgram(shaderId);
        glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void Shader::setUniform(const std::string name, const glm::mat4x4& data) {
    glUseProgram(shaderId);
    glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::setUniform(const std::string name, const glm::mat3x3& data) {
    glUseProgram(shaderId);
    glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::setUniform(const std::string name, const glm::vec3& data) {
    glUseProgram(shaderId);
    glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(data));
}

void Shader::setUniform(const std::string name, float data) {
    glUseProgram(shaderId);
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), data);
}
