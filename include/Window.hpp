//
// Created by deakin on 11/7/26.
//

#pragma once
#include <memory>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Window
{
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window_;
public:
    Window();
    ~Window();

    void SwapBuffers();
    bool ShouldClose();

private:

};
