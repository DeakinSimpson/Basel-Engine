//
// Created by deakin on 11/7/26.
//

#include "../include/Engine.hpp"

#include <iostream>

static void Run();

Engine::Engine()
{
    std::cout << "Engine run" << std::endl;
    Run();
}

// main engine loop
void Engine::Run()
{
    while (!window_.ShouldClose())
    {
        window_.SwapBuffers();
        glfwPollEvents();
    }
}
