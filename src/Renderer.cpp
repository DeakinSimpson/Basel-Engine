//
// Created by deakin on 11/10/26.
//

#include "../include/Renderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderable.hpp"
#include "glad/gl.h"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::BeginFrame(Camera& camera, const float aspectRatio)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view_ = camera.GetView();
    projection_ = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Renderer::Render(Renderable& renderable)
{
    Shader& shader { renderable.GetShader() };
    shader.UseShaderProgram();
    shader.SetMat4("projection", projection_);
    shader.SetMat4("view", view_);
    shader.SetMat4("model", renderable.GetTransform().GetMatrix());
    renderable.Render();
}
