//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Controller.hpp"
#include "Renderer.hpp"
#include "Window.hpp"


class Engine
{
    Window window_;
    Controller controller_;
    Renderer renderer_;
    Camera camera_;
    float deltaTime_ { 0.0f };
    float lastFrame_ { 0.0f };
public:
    Engine();
    void Run();

private:
    void UpdateTime();
};

