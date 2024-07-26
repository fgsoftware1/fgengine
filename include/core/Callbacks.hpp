#pragma once

#include "GLFW/glfw3.h"

#include "pch.hpp"
#include "core/Logger.hpp"

namespace engine
{
    namespace core
    {
        class Callbacks
        {
        public:
            // GLFW callbacks
            static void ErrorCallback(int error, const char *description);
            static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
        };
    }
}