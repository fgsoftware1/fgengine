#pragma once

#include "GLFW/glfw3.h"

#include "pch.hpp"
#include "core/Logger.hpp"

using namespace engine::core;

class Window
{
public:
    static Window &getInstance()
    {
        static Window instance;
        return instance;
    }

    GLFWwindow *getWindow()
    {
        return window;
    }

    void Init(int width = 640, int height = 480, const char *title = "Hello World")
    {
        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Logger::Error(LogChannel::Engine, "Failed to initialize GLAD, can't continue! :(\n" + glad_glGetError());
            glfwTerminate();
        }
    }

    void Shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    Window() {}
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Window(Window &&) = delete;
    Window &operator=(Window &&) = delete;

    GLFWwindow *window;
};
