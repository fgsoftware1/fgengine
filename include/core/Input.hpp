#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "pch.hpp"
#include "core/Window.hpp"

namespace engine
{
    namespace core
    {
        enum class KeyCodes
        {
            Unknown = GLFW_KEY_UNKNOWN,
            Space = GLFW_KEY_SPACE,
            Apostrophe = GLFW_KEY_APOSTROPHE,
            Comma = GLFW_KEY_COMMA,
            Minus = GLFW_KEY_MINUS,
            Period = GLFW_KEY_PERIOD,
            Slash = GLFW_KEY_SLASH,
            Key0 = GLFW_KEY_0,
            Key1 = GLFW_KEY_1,
            Key2 = GLFW_KEY_2,
            Key3 = GLFW_KEY_3,
            Key4 = GLFW_KEY_4,
            Key5 = GLFW_KEY_5,
            Key6 = GLFW_KEY_6,
            Key7 = GLFW_KEY_7,
            Key8 = GLFW_KEY_8,
            Key9 = GLFW_KEY_9,
            Semicolon = GLFW_KEY_SEMICOLON,
            Equal = GLFW_KEY_EQUAL,
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z
        };

        enum class MouseCodes
        {
            ButtonLeft = GLFW_MOUSE_BUTTON_LEFT,
            ButtonRight = GLFW_MOUSE_BUTTON_RIGHT,
            ButtonMiddle = GLFW_MOUSE_BUTTON_MIDDLE
        };

        class Input
        {
        public:
            static bool IsKeyPressed(KeyCodes key);
            static bool IsKeyReleased(KeyCodes key);
            static bool IsMouseButtonPressed(MouseCodes button);
            static bool IsMouseButtonReleased(MouseCodes button);

            static glm::vec2 GetMousePosition();

        private:
            inline static GLFWwindow *window = Window::getInstance().getWindow();
        };
    }
}