//
// Created by deakin on 11/7/26.
//

#include "../include/Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include "stb_image.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

static void CompileShader(uint32_t shader,
                          const std::string& shaderSource, const std::string& errorMessage);
static void LinkShaderProgram(uint32_t shaderProgram,
    uint32_t vertexShader, uint32_t fragmentShader);
static std::string GetShaderCode(const char* shaderPath);
static uint32_t CompileTexture(const char* texturePath);

/**
 * Compiles both shaders
 *
 * @param vertexShaderSource The vertex shader that will be used
 * @param fragmentShaderSource The fragment shader that will be used
 */
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* texturePath)
    : vertexShader_(glCreateShader(GL_VERTEX_SHADER))
    , fragmentShader_(glCreateShader(GL_FRAGMENT_SHADER))
    , texture_(CompileTexture(texturePath))
    , shaderProgram_(glCreateProgram())
{
    CompileShader(vertexShader_,GetShaderCode(vertexShaderSource) ,
        "Vertex Shader Failed to Compile");
    CompileShader(fragmentShader_, GetShaderCode(fragmentShaderSource),
        "Fragment Shader Failed to Compile");

    LinkShaderProgram(shaderProgram_, vertexShader_, fragmentShader_);

    UseShaderProgram();

    SetInt("texture1", 0);
}

/**
 * Delete the shaders when they are no longer used
 */
Shader::~Shader()
{
    glDeleteShader(vertexShader_);
    glDeleteShader(fragmentShader_);
}

/**
 * Wrapper for glUseProgram
 */
void Shader::UseShaderProgram()
{
    glUseProgram(shaderProgram_);
}

/**
 * Sets a bool in the shaderProgram
 *
 * @param name The name of the input in the shaderCode
 * @param value The value that will be passed into the shader
 */
void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(
        shaderProgram_, name.c_str()), static_cast<int>(value));
}

/**
 * Sets a int in the shaderProgram
 *
 * @param name The name of the input in the shaderCode
 * @param value The value that will be passed into the shader
 */
void Shader::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), value);
}

/**
 * Sets a float in the shaderProgram
 *
 * @param name The name of the input in the shaderCode
 * @param value The value that will be passed into the shader
 */
void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), value);
}

/**
 * Sets a 4x4 matrix in the shaderProgram
 *
 * @param name The name of the input in the shaderCode
 * @param value The value that will be passed into the shader
 */
void Shader::SetMat4(const std::string &name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, glm::value_ptr((value)));
}

/**
 * Gets the shaders code from the shaderPath and returns a std::string of the
 * code
 *
 * @param shaderPath Gets the code that is needed for the shaderProgram
 * @return returns a std::string of the shader from a file
 */
static std::string GetShaderCode(const char* shaderPath)
{
    std::ifstream shaderFile;

    // ensure the ifstream emits exceptions
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open the file at the path
        shaderFile.open(shaderPath);

        // read file to string stream
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        // convert the stream to a string and return it
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath
                  << " " << e.what() << std::endl;
        return {};
    }
}

/**
 * Opens a texture at texturePath then compiles the texture and returns the
 * textureID
 *
 * @param texturePath The texture that wil be opened
 * @return The texture id
 */
static uint32_t CompileTexture(const char* texturePath)
{
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return texture;
}

/**
 *
 * @param shader The shader that will be compiles
 * @param shaderSource The shader source that will be used
 * @param errorMessage What error message to print if the shader fails to compile
 */
static void CompileShader(uint32_t shader,
    const std::string& shaderSource, const std::string& errorMessage)
{
    const char* source = shaderSource.c_str();
    glShaderSource(shader, 1, &source, nullptr);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << errorMessage << infoLog << std::endl;
    }
}

/**
 *
 * @param shaderProgram Shader program that will have vert and frag shaders linked
 * @param vertexShader The vertex shader to be linked to the shader program
 * @param fragmentShader The fragment shader to be linked to the shader program
 */
static void LinkShaderProgram(uint32_t shaderProgram,
                              uint32_t vertexShader, uint32_t fragmentShader)
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