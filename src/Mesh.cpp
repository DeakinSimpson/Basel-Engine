//
// Created by deakin on 11/7/26.
//

#include "../include/Mesh.hpp"
#include "glad/gl.h"

static void UnbindBuffers();
static void SetVertexAttribPointer();

Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<uint32_t>& indices)
        : vertices_(vertices)
        , indices_(indices)
{
    GenerateBuffers();

    glBindVertexArray(VAO_);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);


    SetVertexAttribPointer();
    UnbindBuffers();
}

static void UnbindBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void SetVertexAttribPointer()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Mesh::GenerateBuffers()
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
}

void Mesh::BindVAOBuffer()
{
    glBindVertexArray(VAO_);
}

void Mesh::Render()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
