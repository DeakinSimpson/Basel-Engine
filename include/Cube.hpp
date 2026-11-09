//
// Created by deakin on 11/7/26.
//

#include "Mesh.hpp"
#include "Renderable.hpp"

class Cube
{
    std::vector<Vertex> vertices = {
        // positions          // colors           // texture coords
        {{0.5f,  0.5f, 0.0f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // top right
        {{0.5f, -0.5f, 0.0f},   {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}}, // bottom right
        {{-0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}}, // bottom left
        {{-0.5f,  0.5f, 0.0f},  {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}  // top left
   };

    const std::vector<uint32_t> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    const char* vertexShaderSource = "/home/deakin/CLionProjects/Basel-Engine/Assets/Shaders/Vertex/1.0.vertex";

    const char* fragmentShaderSource = "/home/deakin/CLionProjects/Basel-Engine/Assets/Shaders/Fragment/1.0.fragment";

    const char* texturePath = "/home/deakin/CLionProjects/Basel-Engine/Assets/Textures/GigaChad.jpg";

    Renderable renderable_ { Mesh(vertices, indices),
        vertexShaderSource, fragmentShaderSource, texturePath };
public:
    void Render();
};
