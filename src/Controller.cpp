//
// Created by deakin on 11/7/26.
//

#include "../include/Controller.hpp"

#include "Window.hpp"

Controller::Controller(Window& window)
{
    window.CaptureCursor();
}

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

void Controller::ProcessMouse(Window &window, Camera &camera)
{
    const glm::vec2 mouse { window.GetMousePosition() };

    if (firstMouse_)
    {
        lastMouse_ = mouse;
        firstMouse_ = false;
    }

    const float xOffset { mouse.x - lastMouse_.x };
    const float yOffset { lastMouse_.y - mouse.y };

    lastMouse_ = mouse;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

static void ProcessMovement(Camera& camera, Window& window, const float deltaTime)
{
    if (window.KeyStatus(GLFW_KEY_W, GLFW_PRESS)) { camera.MoveForward(deltaTime); }
    if (window.KeyStatus(GLFW_KEY_S, GLFW_PRESS)) { camera.MoveBack(deltaTime);    }
    if (window.KeyStatus(GLFW_KEY_A, GLFW_PRESS)) { camera.MoveLeft(deltaTime);    }
    if (window.KeyStatus(GLFW_KEY_D, GLFW_PRESS)) { camera.MoveRight(deltaTime);   }
}

void Controller::ProcessInput(Window& window, Camera& camera, const float deltaTime)
{
    ProcessEscapeKey(window);
    ProcessPKey(window, pPressedLastFrame);
    ProcessMovement(camera, window, deltaTime);
    ProcessMouse(window, camera);
}
