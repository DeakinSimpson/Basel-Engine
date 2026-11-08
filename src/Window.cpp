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

/**
 * Window initialization logic
 */
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

/**
 * Terminates the window when destructor is called
 */
Window::~Window()
{
    glfwTerminate();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window_.get());
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window_.get());
}

/**
 * Closes the window
 */
void Window::Close()
{
    glfwSetWindowShouldClose(window_.get(), true);
}

bool Window::KeyStatus(const int key, const int action)
{
    return glfwGetKey(window_.get(), key) == action;
}

void Window::SetBackground(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * This creates a GLFWwindow object and checks that it initialized correctly
 * as well as return a unique pointer to it
 *
 * @return A unique pointer to a window object
 */
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

/**
 * Sets the configurations for the window
 */
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

/**
 * Initializes GLAD and checks that it successfully started
 */
static void InitGlad()
{
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Failed to Initialize GLAD" << std::endl;
        std::abort();
    }
}

/**
 *
 * @param window the window that should be updates
 * @param width The new width of the window
 * @param height The new height of the window
 */
void FramebuffferSizeCallback([[maybe_unused]] GLFWwindow* window,
                              int width, int height)
{
    glViewport(0, 0, width, height);
}

