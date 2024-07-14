#pragma once

#include "pch.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/SpriteRenderer.hpp"
#include "ecs/components/ScriptComponent.hpp"

class ComponentFactory {
public:
    static Component* create(const std::string& componentName) {
        if (componentName == "Transform") {
            return new Transform(0.0f, 0.0f, 0.0f);
        }
        else if (componentName == "Script") {
            return new ScriptComponent();
        }
        else {
            // Unknown component type
            return nullptr;
        }
};