#pragma once

#include <glad/gl.h>
#include <string>
#include <memory>

class Texture;
typedef std::shared_ptr<Texture> PTexture;

class Texture {
   private:
    int width;
    int height;
    GLuint handle;

   public:
    static const GLenum LoadMap = GL_TEXTURE5;
    static const GLenum DiffuseMap = GL_TEXTURE0;
    static const GLenum NormalMap = GL_TEXTURE1;

    Texture() : width{0}, height{0} {};
    ~Texture();
    void load(const std::string filename);
    void bind(GLenum map);
    void getSize(int& w, int& h) {
        w = width;
        h = height;
    }

    Texture(const Texture& prog) = delete;
    Texture& operator=(const Texture& prog) = delete;
    Texture(Texture&& prog);
    Texture& operator=(Texture&& prog);

    static PTexture loadFromFile(const std::string filename);
};