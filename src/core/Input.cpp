#include "core/Input.hpp"

bool engine::core::Input::IsKeyPressed(KeyCodes key) {
    return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
}

bool engine::core::Input::IsKeyReleased(KeyCodes key) {
    return glfwGetKey(window, static_cast<int>(key)) == GLFW_RELEASE;
}


bool engine::core::Input::IsMouseButtonPressed(MouseCodes button) {
    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
}

bool engine::core::Input::IsMouseButtonReleased(MouseCodes button) {
    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_RELEASE;
}

glm::vec2 engine::core::Input::GetMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
}
