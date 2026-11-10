//
// Created by deakin on 11/7/26.
//

#include "../include/Mesh.hpp"
#include "glad/gl.h"

static void UnbindBuffers();
static void SetVertexAttribPointer();

/**
 * Starts by generating the buffers and then sends the vertices and indices to
 * the gpu
 *
 * @param vertices The vertices to be sent to the gpu
 * @param indices The indices to be sent to the gpu
 */
Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<uint32_t>& indices)
        : vertices_(vertices)
        , indices_(indices)
{
    GenerateBuffers();

    glBindVertexArray(VAO_);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        vertices.data(), GL_STATIC_DRAW);

    // bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
        indices.data(), GL_STATIC_DRAW);


    SetVertexAttribPointer();
    UnbindBuffers();
}

/**
 * Unbinds the buffers so they are not attached to arrays anymore
 */
static void UnbindBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 * Sets what the vertex should be, this is so that the vertex stride is correct
 */
static void SetVertexAttribPointer()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(1);
}

/**
 * Generates VAO, VBO and EBO buffers
 */
void Mesh::GenerateBuffers()
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
}

/**
 * Renders the mesh object (this does not work if there is not a shader (this
 * should mostly only be called via the child rendererable)
 */
void Mesh::Render()
{
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, nullptr);
}
