//
// Created by deakin on 11/7/26.
//

#include "../include/Engine.hpp"

#include <iostream>

#include "Cube.hpp"

static void Run();

Engine::Engine()
{
    std::cout << "Engine run" << std::endl;
    Run();
}

// main engine loop
void Engine::Run()
{
    Cube cube;
    while (!window_.ShouldClose())
    {
        controller_.ProcessInput(window_);
        // TODO: Remove later
        window_.SetBackground(0.2, 0.3, 0.3, 1.0);

        cube.Render();

        window_.SwapBuffers();
        glfwPollEvents();
    }
}
