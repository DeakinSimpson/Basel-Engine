//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"

struct Transform
{
    glm::vec3 position { 0.0f };
    glm::vec3 rotation { 0.0f };
    glm::vec3 scale    { 1.0f };

    /**
     *
     * @return A 4x4 matrix based on the Transform values
     */
    glm::mat4 GetMatrix() const
    {
        glm::mat4 model { 1.0f };
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }
};

class Renderable : public Mesh
{
    Shader shader_;
    Transform transform_;
public:
    Renderable(const Mesh & mesh, const char* vertexShaderSource,
        const char* fragmentShaderSource, const char* texturePath);

    void Render();
    Shader& GetShader();
    Transform& GetTransform() { return transform_; }
};


