//
// Created by deakin on 11/7/26.
//

#pragma once
#include <memory>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

class Window
{
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window_;
    bool isWireframeMode { false };
public:
    Window();
    ~Window();

    void SwapBuffers();
    bool ShouldClose();
    void Close();
    bool KeyStatus(const int key, const int action);
    void SetBackground(const float r, const float g, const float b, const float a);
    void ToggleWireframe();
    void CaptureCursor();
    glm::vec2 GetMousePosition();

private:

};
