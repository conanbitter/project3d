#pragma once
#include <array>

struct Vector3D {
    float x;
    float y;
    float z;
};

struct Vector2D {
    float x;
    float y;
};

struct Vertex {
    Vector3D pos;
    Vector3D norm;
    Vector2D uv;
};

typedef std::array<uint32_t, 3> Triangle;