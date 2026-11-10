//
// Created by deakin on 11/7/26.
//

#include "Mesh.hpp"
#include "Renderable.hpp"

class Cube : public Renderable
{
    inline static const std::vector<Vertex> vertices = {
        // positions          // colors           // texture coords
        {{0.5f,  0.5f, 0.0f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // top right
        {{0.5f, -0.5f, 0.0f},   {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}}, // bottom right
        {{-0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}}, // bottom left
        {{-0.5f,  0.5f, 0.0f},  {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}  // top left
   };

    inline static const std::vector<uint32_t> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    static constexpr const char* vertexShaderSource = "/home/deakin/CLionProjects/Basel-Engine/Assets/Shaders/Vertex/1.0.vert";

    static constexpr const char* fragmentShaderSource = "/home/deakin/CLionProjects/Basel-Engine/Assets/Shaders/Fragment/1.0.frag";

    static constexpr const char* texturePath = "/home/deakin/CLionProjects/Basel-Engine/Assets/Textures/GigaChad.jpg";

public:
    Cube()
    : Renderable(Mesh(vertices, indices), vertexShaderSource,
        fragmentShaderSource, texturePath)
    {  }
};
