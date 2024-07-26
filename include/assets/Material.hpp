#pragma once

#include "glm/glm.hpp"

#include "pch.hpp"
#include "utils/MaterialFileHandler.hpp"

class Material
{
public:
    Material(const glm::vec4 &color = glm::vec4(1.0f), const glm::vec2 &tiling = glm::vec2(1.0f), const glm::vec2 &offset = glm::vec2(0.0f)) : m_Color(color), m_Tiling(tiling), m_Offset(offset) {}

    static std::shared_ptr<Material> getSelectedMaterial() { return selectedMaterial; }
    const glm::vec4 &GetColor() const { return m_Color; }
    const glm::vec2 &GetTiling() const { return m_Tiling; }
    const glm::vec2 &GetOffset() const { return m_Offset; }

    static void setSelectedMaterial(const Material &material) { selectedMaterial = std::make_shared<Material>(material); }
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTiling(const glm::vec2 &tiling) { m_Tiling = tiling; }
    void SetOffset(const glm::vec2 &offset) { m_Offset = offset; }

    std::shared_ptr<Material> loadMaterial(const std::string &filename) { return fileHandler.Load(filename); }
    void overwriteSelectedFile(const std::string &path) { fileHandler.Save(path, *selectedMaterial); }

    void draw()
    {
        ImGui::Text("Material");
        ImGui::Columns(2, "mycolumns");
        ImGui::Separator();
        ImGui::Text("Diffuse Texture");
        ImGui::NextColumn();
        ImGui::Image((void *)(intptr_t)m_DiffuseTexture, ImVec2(64, 64));
        ImGui::NextColumn();
        ImGui::Text("Color");
        ImGui::NextColumn();
        if (ImGui::ColorEdit4("##Color", &m_Color[0]) && ImGui::IsItemEdited())
        {
            overwriteSelectedFile(editFile);
        }
        ImGui::NextColumn();
        ImGui::Text("Tiling");
        ImGui::NextColumn();
        if (ImGui::SliderFloat2("##Tiling", &m_Tiling[0], 0.0f, 10.0f) && ImGui::IsItemDeactivatedAfterEdit())
        {
            overwriteSelectedFile(editFile);
        }
        ImGui::NextColumn();
        ImGui::Text("Offset");
        ImGui::NextColumn();
        if (ImGui::SliderFloat2("##Offset", &m_Offset[0], -10.0f, 10.0f) && ImGui::IsItemDeactivatedAfterEdit())
        {
            overwriteSelectedFile(editFile);
        }
        ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
    }

    static Ref<Material> selectedMaterial;

private:
    static std::string editFile;

    Texture2D *m_DiffuseTexture;
    glm::vec4 m_Color;
    glm::vec2 m_Tiling;
    glm::vec2 m_Offset;

    MaterialFileHandler fileHandler;
};
