//
// Created by deakin on 11/7/26.
//

#include "../include/Renderable.hpp"

#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "glad/gl.h"

Renderable::Renderable(const Mesh & mesh, const char* vertexShaderSource,
                       const char* fragmentShaderSource)
    : Mesh(mesh)
    , shader_(vertexShaderSource, fragmentShaderSource)
{

}

void Renderable::Render()
{
    BindVAOBuffer();
    Mesh::Render();
}
