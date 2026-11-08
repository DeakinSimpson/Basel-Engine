//
// Created by deakin on 11/7/26.
//

#include "../include/Shader.hpp"

#include <iostream>

#include "glad/gl.h"

static void CompileShader(const uint32_t& shader,
    const char* shaderSource, const std::string& errorMessage);
static void LinkShaderProgram(const uint32_t& shaderProgram,
    const uint32_t& vertexShader, const uint32_t& fragmentShader);

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
    : vertexShader_(glCreateShader(GL_VERTEX_SHADER))
    , fragmentShader_(glCreateShader(GL_FRAGMENT_SHADER))
    , shaderProgram_(glCreateProgram())
{
    CompileShader(vertexShader_, vertexShaderSource, "Vertex Shader Failed to Compile");
    CompileShader(fragmentShader_, fragmentShaderSource, "Fragment Shader Failed to Compile");
    LinkShaderProgram(shaderProgram_, vertexShader_, fragmentShader_);
    glUseProgram(shaderProgram_);
}

Shader::~Shader()
{
    glDeleteShader(vertexShader_);
    glDeleteShader(fragmentShader_);
}

static void CompileShader(const uint32_t& shader,
                          const char* shaderSource, const std::string& errorMessage)
{
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << errorMessage << infoLog << std::endl;
    }
}

static void LinkShaderProgram(const uint32_t& shaderProgram,
    const uint32_t& vertexShader, const uint32_t& fragmentShader)
{
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ShaderProgram Failed to Compile" << infoLog << std::endl;
    }
}