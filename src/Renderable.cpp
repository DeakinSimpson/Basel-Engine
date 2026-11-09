//
// Created by deakin on 11/7/26.
//

#include "../include/Renderable.hpp"

#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "glad/gl.h"

Renderable::Renderable(const Mesh & mesh, const char* vertexShaderSource,
                       const char* fragmentShaderSource, const char* texturePath)
    : Mesh(mesh)
    , shader_(vertexShaderSource, fragmentShaderSource, texturePath)
{  }

/**
 * Uses the shader assigned to the renderable then calls the mesh to be rendered
 * with the shader program.
 */
void Renderable::Render()
{
    shader_.UseShaderProgram();
    Mesh::Render();
}
