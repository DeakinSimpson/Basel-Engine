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
Controller::Controller(Window& window)
{
    window.CaptureCursor();
}

/**
 * Checks if the escape key was pressed, if so close the program
 *
 * TODO: Move escape key to bring up gui rather then close
 *
 * @param window The window that will capture the input
 */
static void ProcessEscapeKey(Window& window)
{
    if (window.KeyStatus(GLFW_KEY_ESCAPE, GLFW_PRESS))
    {
        window.Close();
    }
}

/**
 * Checks if the p key was pressed last frame, if it was not and it is this frame
 * then toggle the wire frame.
 *
 * This last frame check needs to be done so that the when clicking the key the
 * window does not send thousands of p presses and thus wireframe toggles, this
 * means that holding the p key will not toggle on and off and requires the user
 * to stop pressing before clicking again to activate the toggle.
 *
 * @param window The window that will capture the input
 * @param pKeyPressedLastFrame Was the P key pressed last frame
 */
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
    ProcessEscapeKey(window);
    ProcessPKey(window, pPressedLastFrame);
    ProcessMovement(camera, window, deltaTime);
    ProcessMouse(window, camera);
}
