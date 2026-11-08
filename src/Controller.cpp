//
// Created by deakin on 11/7/26.
//

#include "../include/Controller.hpp"

#include "Window.hpp"

static void ProcessEscapeKey(Window& window)
{
    if (window.KeyStatus(GLFW_KEY_ESCAPE, GLFW_PRESS))
    {
        window.Close();
    }
}

void Controller::ProcessInput(Window& window)
{
    ProcessEscapeKey(window);
}
