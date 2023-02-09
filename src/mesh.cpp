#include <iostream>
#include <fstream>
#include <glad/gl.h>
#include "mesh.hpp"

const uint32_t VERT_SIGNATURE = 0x54524556;  // VERT
const uint32_t TRIS_SIGNATURE = 0x53495254;  // TRIS

void Mesh::Load(const std::string filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Wrong File" << std::endl;
        return;
    }
    while (!file.eof()) {
        uint32_t signature;
        uint32_t size;
        uint32_t count;
        file.read((char *)&signature, 4);
        if (file.eof()) {
            break;
        }
        file.read((char *)&size, 4);
        switch (signature) {
            case VERT_SIGNATURE:
                file.read((char *)&count, 4);
                std::cout << "Vertices :" << count << std::endl;
                vertices.resize(count);
                file.read((char *)vertices.data(), sizeof(Vertex) * count);
                break;

            case TRIS_SIGNATURE:
                file.read((char *)&count, 4);
                std::cout << "Faces :" << count << std::endl;
                faces.resize(count);
                file.read((char *)faces.data(), sizeof(Triangle) * count);
                break;

            default:
                break;
        }
    }
}
Mesh::Mesh(const std::string filename) {
    Load(filename);
}

void Mesh::Draw(Renderer &renderer) {}