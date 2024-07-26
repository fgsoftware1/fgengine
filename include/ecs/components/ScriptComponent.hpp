#pragma once

#include "imgui.h"

#include "pch.hpp"
#include "ecs/Component.hpp"
#include "scripting/IParser.hpp"
#include "scripting/ParserFactory.hpp"

/**
 * @class ScriptComponent
 * @brief ScriptComponent is a component that can execute scripts.
 *
 * The ScriptComponent class allows the user to load and execute scripts.
 * It uses the ParserFactory to create a parser for the script based on its extension.
 * The script can be loaded from a file, and the values of its fields can be modified in the ImGui interface.
 */
class ScriptComponent : public Component {
public:
    /**
     * @brief Constructs a new ScriptComponent object.
     * @param scriptPath The path to the script file.
     */
    ScriptComponent(const std::string& scriptPath = "") : scriptPath(scriptPath) {
        registerComponentName(name);
        if (!scriptPath.empty()) {
            Ref<IParser> parser = ParserFactory::createParser(scriptPath);
            if (parser) {
                scriptClass = parser->parse();
            }
        }
    }

    /**
     * @brief Draws the script component in the ImGui interface.
     */
    void draw() override {
        ImGui::Columns(2);
        for (const auto& field : scriptClass.fields) {
            ImGui::Text(field.name.c_str());
            ImGui::NextColumn();
            if (field.type == "int") {
                int value = std::stoi(field.value);
                ImGui::InputInt("##", &value);
            }
            else if (field.type == "float") {
                float value = std::stof(field.value);
                ImGui::InputFloat("##", &value);
            }
            else if (field.type == "std::string" || field.type == "string") {
                char buffer[256] = "";
                std::string newValue = field.value;
                newValue.erase(std::remove(newValue.begin(), newValue.end(), '\"'), newValue.end());
                newValue.erase(std::remove(newValue.begin(), newValue.end(), ';'), newValue.end());
                strncpy(buffer, newValue.c_str(), sizeof(buffer));
                buffer[sizeof(buffer) - 1] = 0;
                ImGui::InputText("##", buffer, sizeof(buffer));
            }
            ImGui::NextColumn();
        }
        ImGui::Columns(1); 
    }

    /**
     * @brief Returns the name of the component.
     * @return The name of the component.
     */
    const std::string& getName() const override { return name; }

private:
    static inline std::string name = "Script";
    
    std::string scriptPath;
    Class scriptClass;
};

