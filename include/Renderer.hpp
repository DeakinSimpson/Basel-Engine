//
// Created by deakin on 11/10/26.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Renderable.hpp"

class Renderer
{
    glm::mat4 projection_ { 1.0f };
    glm::mat4 view_ { 1.0f };

public:
    Renderer();
    void BeginFrame(Camera& camera, const float aspectRatio);
    void Render(Renderable& renderable);

};
