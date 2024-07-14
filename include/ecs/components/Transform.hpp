#pragma once

#include "imgui.h"
#include "glad/glad.h"

#include "pch.hpp"
#include "ecs/Component.hpp"
#include "math/Vector3.hpp"
#include "core/Logger.hpp"

using engine::core::LogChannel;
using engine::core::Logger;

class Transform : public Component
{
public:
	Transform(float x, float y, float z) : position(x, y, z), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {
        registerComponentName(name);
    }
	void draw() override {
		if (ImGui::TreeNode("Transform")) {
            ImGui::Columns(4, "##columns", false); 

            ImGui::Text("Position"); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
            ImGui::Button("X"); ImGui::SameLine(); ImGui::InputFloat("##PositionX", &position.x); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));
            ImGui::Button("Y"); ImGui::SameLine(); ImGui::InputFloat("##PositionY", &position.y); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 1, 1));
            ImGui::Button("Z"); ImGui::SameLine(); ImGui::InputFloat("##PositionZ", &position.z); ImGui::PopStyleColor(); ImGui::NextColumn();

            ImGui::Text("Rotation"); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
            ImGui::Button("X"); ImGui::SameLine(); ImGui::InputFloat("##RotationX", &rotation.x); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));
            ImGui::Button("Y"); ImGui::SameLine(); ImGui::InputFloat("##RotationY", &rotation.y); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 1, 1));
            ImGui::Button("Z"); ImGui::SameLine(); ImGui::InputFloat("##RotationZ", &rotation.z); ImGui::PopStyleColor(); ImGui::NextColumn();

            ImGui::Text("Scale"); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
            ImGui::Button("X"); ImGui::SameLine(); ImGui::InputFloat("##ScaleX", &scale.x); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));
            ImGui::Button("Y"); ImGui::SameLine(); ImGui::InputFloat("##ScaleY", &scale.y); ImGui::PopStyleColor(); ImGui::NextColumn();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 1, 1));
            ImGui::Button("Z"); ImGui::SameLine(); ImGui::InputFloat("##ScaleZ", &scale.z); ImGui::PopStyleColor(); ImGui::NextColumn();

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::TreePop();
		}
	}

    const std::string& getName() const override { return name; }

public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
private:
    static inline std::string name = "Transform";
};