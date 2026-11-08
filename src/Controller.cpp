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

static void ProcessPKey(Window& window, bool& pKeyPressedLastFrame)
{
    if (window.KeyStatus(GLFW_KEY_P, GLFW_PRESS))
    {
        if (!pKeyPressedLastFrame)
        {
            window.ToggleWireframe();
            pKeyPressedLastFrame = true;
        }
    }
    else
    {
        pKeyPressedLastFrame = false;
    }
}

void Controller::ProcessInput(Window& window)
{
    ProcessEscapeKey(window);
    ProcessPKey(window, pPressedLastFrame);
}
