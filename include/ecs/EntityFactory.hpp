#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "pch.hpp"
#include "ecs/Entity.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/SpriteRenderer.hpp"
#include "core/GameWindow.hpp"

class EntityFactory
{
public:
    /**
     * @brief Creates a new empty object entity.
     *
     * This function creates a new empty object entity by creating a new entity
     * object and adding a new transform component to it. The transform component
     * is initialized with the position (0.0f, 0.0f, 0.0f) and the entity is
     * assigned the name "Empty Object".
     *
     * @return Ref<Entity> A reference to the newly created entity.
     */
    static Ref<Entity> createEmptyObject()
    {
        // Create a new entity object with the name "Empty Object".
        Ref<Entity> entity = CreateRef<Entity>("Empty Object");

        // Create a new transform component with the position (0.0f, 0.0f, 0.0f)
        // and add it to the entity.
        entity->addComponent<Transform>("Transform", new Transform(0.0f, 0.0f, 0.0f));

        // Return the newly created entity.
        return entity;
    }

    /**
     * @brief Creates a new sprite object entity.
     *
     * This function creates a new sprite object entity by creating a new entity
     * object and adding two new components to it: a transform component and a sprite
     * renderer component. The transform component is initialized with the position
     * (0.0f, 0.0f, 0.0f), and the sprite renderer component is initialized with default
     * values. The entity is assigned the name "Sprite".
     *
     * @return Ref<Entity> A reference to the newly created entity.
     */
    static Ref<Entity> createSpriteObject()
    {
        // Create a new entity object with the name "Sprite".
        Ref<Entity> entity = CreateRef<Entity>("Sprite");
        // load shaders
        ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "sprite");
        // configure shaders
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(GameWindow::GetWidth()), static_cast<float>(GameWindow::GetHeight()), 0.0f, -1.0f, 1.0f);
        ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
        ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

        // Create a new transform component with the position (0.0f, 0.0f, 0.0f)
        // and add it to the entity.
        entity->addComponent<Transform>("Transform", new Transform(0.0f, 0.0f, 0.0f));

        // Create a new sprite renderer component and add it to the entity.
        entity->addComponent<SpriteRenderer>("Sprite Renderer", new SpriteRenderer(ResourceManager::GetShader("sprite")));

        // Return the newly created entity.
        return entity;
    }
};