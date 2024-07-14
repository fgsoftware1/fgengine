#pragma once

#include "pch.hpp"

/**
 * @brief Base class for all components in the ECS.
 *
 * This class serves as a base for all components in the Entity Component System.
 * Any component added to an entity must derive from this class.
 *
 * @note All components must implement a virtual function called `draw`. This
 * function is used to draw the component in the ImGui interface.
 */
class Component
{
public:
    /**
     * @brief Virtual destructor for the Component class.
     */
    virtual ~Component() = default;

    /**
     * @brief Pure virtual function used to draw the component in the ImGui
     * interface.
     * 
     * @note This method must be implemented by derived classes.
     */
    virtual void draw() = 0;
    virtual const std::string& getName() const = 0;

    static void registerComponentName(const std::string& name) {
        componentNames.push_back(name);
    }

    static const std::vector<std::string>& getComponentNames() {
        return componentNames;
    }

private:
    static inline std::vector<std::string> componentNames;
};
