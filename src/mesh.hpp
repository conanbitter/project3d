#pragma once

#include <vector>
#include <string>
#include <memory>
#include "geometry.hpp"
#include "renderer.hpp"

class Mesh;

typedef std::shared_ptr<Mesh> PMesh;

class Mesh {
    friend class Renderer;

   private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> faces;

   public:
    Mesh(){};
    void load(const std::string filename);
    Mesh(const std::string filename);

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    static PMesh LoadFromFile(const std::string filename);
};
