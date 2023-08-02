#pragma once

#include "glm.hpp"

struct CameraComponent {
    glm::vec3 position;
    glm::vec3 target;
    float fov;
    float nearPlane;
    float farPlane;
};