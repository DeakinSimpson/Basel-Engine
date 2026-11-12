//
// Created by deakin on 11/7/26.
//

#include "../include/Engine.hpp"

#include <iostream>

#include "Cube.hpp"

Engine::Engine() : gui_(window_)
{
    std::cout << "Starting Engine" << std::endl;
    Run();
}

// main engine loop
void Engine::Run()
{
    Cube cube;
    while (!window_.ShouldClose())
    {
        gui_.StartFrame();
        UpdateTime();
        controller_.ProcessInput(window_, camera_, deltaTime_);
        // TODO: Remove later
        window_.SetBackground(0.2, 0.3, 0.3, 1.0);

        renderer_.BeginFrame(camera_, 800.0f / 600.0f);
        renderer_.Render(cube);

        gui_.EndFrame();
        window_.SwapBuffers();
        glfwPollEvents();
    }
}

void Engine::UpdateTime()
{
    float currentFrame = glfwGetTime();
    deltaTime_ = currentFrame - lastFrame_;
    lastFrame_ = currentFrame;
}