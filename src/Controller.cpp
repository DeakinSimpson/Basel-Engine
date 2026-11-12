//
// Created by deakin on 11/7/26.
//

#include "../include/Controller.hpp"

#include "Window.hpp"

/**
 * Initialises the controller and captures the mouse input
 *
 * @param window The window that the input will be derived from
 */
Controller::Controller()
{  }


template <typename F>
static void ProcessToggleKeyPress(Window& window, const int key, F function, bool& isPressedLastFrame)
{
    if (window.KeyStatus(key, GLFW_PRESS))
    {
        if (!isPressedLastFrame)
        {
            function();
            isPressedLastFrame = true;
        }
    }
    else
    {
        isPressedLastFrame = false;
    }
}

/**
 * Gets the mouse input, compares it to the last frame and sends the offset to
 * the camera class to process the view vectors.
 *
 * @param window The window that will capture the input
 * @param camera The Camera that will have its position updated
 */
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

/**
 * This function will update the cameras physical position based on which key is
 * pressed
 *
 * @param camera The camera that will have its position updates
 * @param window The window that will capture the input
 * @param deltaTime The time that has passed since the last frame
 */
static void ProcessMovement(Camera& camera, Window& window, const float deltaTime)
{
    if (window.KeyStatus(GLFW_KEY_W, GLFW_PRESS)) { camera.MoveForward(deltaTime); }
    if (window.KeyStatus(GLFW_KEY_S, GLFW_PRESS)) { camera.MoveBack(deltaTime);    }
    if (window.KeyStatus(GLFW_KEY_A, GLFW_PRESS)) { camera.MoveLeft(deltaTime);    }
    if (window.KeyStatus(GLFW_KEY_D, GLFW_PRESS)) { camera.MoveRight(deltaTime);   }
}

/**
 * This is a wrapper function that simply calls each other function, this is to
 * reduce the amount of functions required in the engine main loop
 *
 * @param window The window that will capture the input
 * @param camera The camera that will be updated
 * @param deltaTime The time that has passed since the last frame
 */
void Controller::ProcessInput(Window& window, Camera& camera, const float deltaTime)
{
    ProcessToggleKeyPress(window, GLFW_KEY_P, [&window]() { window.ToggleWireframe(); }, pressedLastFrame.p);
    ProcessToggleKeyPress(window, GLFW_KEY_ESCAPE, [&window]() { window.ToggleCaptureCursor(); }, pressedLastFrame.esc);
    ProcessMovement(camera, window, deltaTime);
    ProcessMouse(window, camera);
}
