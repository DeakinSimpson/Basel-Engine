//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Camera.hpp"
#include "Window.hpp"

class Controller
{
    bool pPressedLastFrame { false };
    bool firstMouse_ { true };
    glm::vec2 lastMouse_ { 0.0f };

public:
    Controller(Window& window);
    void ProcessInput(Window& window, Camera& camera, const float deltaTime);

private:
    void ProcessMouse(Window& window, Camera& camera);
};
