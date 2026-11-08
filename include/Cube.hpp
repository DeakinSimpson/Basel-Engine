//
// Created by deakin on 11/7/26.
//

#include "Mesh.hpp"
#include "Renderable.hpp"

class Cube
{
    const std::vector<Vertex> vertices = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}
    };

    const std::vector<uint32_t> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    Renderable renderable_ { Mesh(vertices, indices),
        vertexShaderSource, fragmentShaderSource };
public:
    void Render();
};
