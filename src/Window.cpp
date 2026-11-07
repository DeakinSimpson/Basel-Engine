//
// Created by deakin on 11/7/26.
//

#include "../include/Window.hpp"

#include <iostream>
#include <memory>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "config.hpp"

static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
CreateWindowObject();
static void ConfigureGLFWWindow();
static void InitGlad();
void FramebuffferSizeCallback([[maybe_unused]] GLFWwindow* window,
    int width, int height);

Window::Window() : window_(nullptr, glfwDestroyWindow)
{
    glfwInit();
    ConfigureGLFWWindow();

    // create the window object
    window_.reset(CreateWindowObject().release());

    InitGlad();

    glViewport(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window_.get(), FramebuffferSizeCallback);
}

Window::~Window()
{
    glfwTerminate();
}

static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
CreateWindowObject()
{
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window {
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(
        glfwCreateWindow(
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT,
            Config::WINDOW_NAME,
            nullptr,
            nullptr),
        &glfwDestroyWindow)
    };

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        std::abort();
    }

    glfwMakeContextCurrent(window.get());

    return window;
}

static void ConfigureGLFWWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // for macos enable this:
    const bool MACOS { false };
    if (MACOS)
    {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
};

static void InitGlad()
{
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Failed to Initialize GLAD" << std::endl;
        std::abort();
    }
}

void FramebuffferSizeCallback([[maybe_unused]] GLFWwindow* window,
    int width, int height)
{
    glViewport(0, 0, width, height);
}

