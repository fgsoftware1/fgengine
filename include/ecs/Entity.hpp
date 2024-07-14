#pragma once 

#include <imgui.h>

#include "pch.hpp"
#include "core/Logger.hpp"
#include "ecs/Component.hpp"
#include "ecs/ComponentFactory.hpp"

using namespace engine::core;

/**
 * @class Entity
 * @brief Entity class represents an entity in the Entity-Component-System architecture.
 *
 * An Entity is a collection of Components. It has a name and can have children entities.
 */
class Entity : public std::enable_shared_from_this<Entity> {
public:
    /**
     * @brief Constructs a new Entity object.
     *
     * @param name The name of the entity.
     */
    Entity(const std::string& name) : name(name) {}

    /**
     * @brief Get the selected entity.
     *
     * @return The selected entity.
     */
    static Ref<Entity> getSelectedEntity() {
        return selectedEntity;
    }

    /**
     * @brief Set the selected entity.
     *
     * @param entity The entity to be selected.
     */
    static void setSelectedEntity(Ref<Entity> entity) {
        selectedEntity = entity;
    }

    /**
     * @brief Add a component to the entity.
     *
     * @tparam T The type of the component.
     * @param componentName The name of the component.
     * @param component The pointer to the component.
     * @throws std::logic_error If the type of the component is not derived from Component.
     */
    template<typename T>
    void addComponent(const std::string& componentName, T* component) {
        if (components.find(componentName) == components.end()) {
            Scope<T> componentScope(component);
            components[componentName] = std::move(componentScope);
#ifndef NDEBUG
            Logger::Debug(LogChannel::Engine, "Added component: " + componentName + " to entity: " + name);
#endif
        }
    }

    /**
     * @brief Get a component from the entity.
     *
     * @tparam T The type of the component.
     * @param componentName The name of the component.
     * @return The pointer to the component, or nullptr if the component is not found.
     */
    template<typename T>
    T* getComponent(const std::string& componentName) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        auto it = components.find(componentName);
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        else {
            return nullptr;
        }
    }

    void addComponentByName(const std::string& componentName) {
        if (components.find(componentName) == components.end()) {
            // Create the component using a factory function
            Component* component = ComponentFactory::create(componentName);
            if (component != nullptr) {
                Scope<Component> componentScope(component);
                components[componentName] = std::move(componentScope);
#ifndef NDEBUG
                Logger::Debug(LogChannel::Engine, "Added component: " + componentName + " to entity: " + name);
#endif
            }
        }
    }


    /**
     * @brief Get the names of the components of the entity.
     *
     * @return A vector of component names.
     */
    std::vector<std::string> getComponentNames() {
        std::vector<std::string> componentNames;
        for (const auto& pair : components) {
            componentNames.push_back(pair.first);
        }
        return componentNames;
    }


    /**
     * @brief Add a child entity to the entity.
     *
     * @param child The child entity.
     */
    void addChild(Ref<Entity> child) {
        children.push_back(std::move(child));
    }

    /**
     * @brief Draw the entities and their components in the ImGui interface.
     *
     * @param entity The current entity.
     */
    void drawEntities(Ref<Entity> entity) {
        if (ImGui::TreeNode(name.c_str())) {
            if (ImGui::IsItemClicked()) {
                Entity::selectedEntity = shared_from_this();
            }
            for (auto& child : children) {
                child->drawEntities(child);
            }
            ImGui::TreePop();
        }
    }

    /**
     * @brief Draw the components of the entity in the ImGui interface.
     */
    void drawComponents() {
        for (auto& pair : components) {
            pair.second->draw();
        }
    }

private:
    /**
     * @brief The selected entity.
     */
    static Ref<Entity> selectedEntity;

    /**
     * @brief The name of the entity.
     */
    std::string name;

    /**
     * @brief The components of the entity.
     */
    std::unordered_map<std::string, Scope<Component>> components;

    /**
     * @brief The children entities.
     */
    std::vector<Ref<Entity>> children;
};
