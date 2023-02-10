#pragma once

#include <vector>
#include <string>
#include "geometry.hpp"
#include "renderer.hpp"

class Mesh {
    friend class Renderer;

   private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;

   public:
    Mesh(){};
    void Load(const std::string filename);
    Mesh(const std::string filename);
    void Draw(Renderer &renderer);
};