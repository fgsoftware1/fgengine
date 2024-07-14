#pragma once

#include "pch.hpp"
#include "ecs/Entity.hpp"
#include "ecs/components/Transform.hpp"

class EntityFactory
{
public:
    static Ref<Entity> createEmptyObject()
    {
        Ref<Entity> entity = CreateRef<Entity>("Empty Object");
        entity->addComponent<Transform>("Transform", new Transform(0.0f, 0.0f, 0.0f));
        return entity;
    }
};