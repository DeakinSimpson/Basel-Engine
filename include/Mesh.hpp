//
// Created by deakin on 11/7/26.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdint>
#include <vector>

struct Vector3
{
    float x;
    float y;
    float z;
};

struct Vector2
{
    float u;
    float v;
};

constexpr int VERTEX_VALUE_COUNT { 3 };
struct Vertex
{
    Vector3 position;
    Vector3 color;
    Vector2 texture;
};

class Mesh
{
    uint32_t VAO_ { 0 };
    uint32_t VBO_ { 0 };
    uint32_t EBO_ { 0 };

    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
    glm::mat4 model_ { glm::mat4(1.0f) };

public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices);

    void BindVAOBuffer();
    void Render();

private:
    void GenerateBuffers();
};
