//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Camera.hpp"
#include "Window.hpp"

class Controller
{
    struct PressedLastFrame
    {
        bool p { false };
        bool esc { false };
    };
    PressedLastFrame pressedLastFrame;
    bool pPressedLastFrame { false };
    bool firstMouse_ { true };
    glm::vec2 lastMouse_ { 0.0f };

public:
    Controller();
    void ProcessInput(Window& window, Camera& camera, const float deltaTime);

private:
    void ProcessMouse(Window& window, Camera& camera);
};
