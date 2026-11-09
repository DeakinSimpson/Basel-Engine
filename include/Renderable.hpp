//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"

class Renderable : Mesh
{
    Shader shader_;
public:
    Renderable(const Mesh & mesh, const char* vertexShaderSource,
        const char* fragmentShaderSource, const char* texturePath);

    void Render();
};


