//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Camera.hpp"
#include "Window.hpp"

class Controller
{
    bool pPressedLastFrame { false };
public:
    void ProcessInput(Window& window, Camera& camera, const float deltaTime);
};
