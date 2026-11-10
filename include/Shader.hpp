//
// Created by deakin on 11/7/26.
//

#pragma once
#include <cstdint>
#include <string>

#include "glm/fwd.hpp"

class Shader
{
    uint32_t vertexShader_;
    uint32_t fragmentShader_;
    uint32_t shaderProgram_;
    uint32_t texture_;

public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* texturePath);
    ~Shader();
    void UseShaderProgram();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, glm::mat4 value) const;
};
