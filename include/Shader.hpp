//
// Created by deakin on 11/7/26.
//

#pragma once
#include <cstdint>

class Shader
{
    uint32_t vertexShader_;
    uint32_t fragmentShader_;
    uint32_t shaderProgram_;

public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~Shader();
    void UseShaderProgram();
};
