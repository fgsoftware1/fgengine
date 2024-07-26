#include "core/Callbacks.hpp"

namespace engine
{
    namespace core
    {
        void Callbacks::ErrorCallback(int error, const char *description)
        {
            Logger::Error(LogChannel::Engine, "GLFW Error (" + std::to_string(error) + "): " + description);
        }

        void Callbacks::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    }
}