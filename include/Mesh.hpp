//
// Created by deakin on 11/7/26.
//

#pragma once
#include <cstdint>
#include <vector>

struct Vector3
{
    float x;
    float y;
    float z;
};

constexpr int VERTEX_VALUE_COUNT { 3 };
struct Vertex
{
    Vector3 position;
};

class Mesh
{
    uint32_t VAO_ { 0 };
    uint32_t VBO_ { 0 };
    uint32_t EBO_ { 0 };

    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;

public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);

    void BindVAOBuffer();
    void Render();

private:
    // void GenerateBuffers();
    // void BindBuffers();
    // void BufferData();
};
