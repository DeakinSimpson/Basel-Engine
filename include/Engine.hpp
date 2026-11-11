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
public:
    Engine();
public:
    void Run();
};

