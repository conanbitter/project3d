#pragma once

#include <glad/gl.h>
#include <string>

class Texture {
   private:
    int width;
    int height;
    GLuint handle;

   public:
    static const GLenum LoadMap = GL_TEXTURE5;
    static const GLenum DiffuseMap = GL_TEXTURE0;

    Texture() : width{0}, height{0} {};
    ~Texture();
    void load(std::string filename);
    void bind(GLenum map);
    void getSize(int& w, int& h) {
        w = width;
        h = height;
    }

    Texture(const Texture& prog) = delete;
    Texture& operator=(const Texture& prog) = delete;
    Texture(Texture&& prog);
    Texture& operator=(Texture&& prog);
};