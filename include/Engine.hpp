//
// Created by deakin on 11/7/26.
//

#pragma once
#include "Controller.hpp"
#include "Window.hpp"


class Engine
{
    Window window_;
    Controller controller_;
public:
    Engine();
public:
    void Run();
};

