#pragma once

#include "yaml-cpp/yaml.h"
#include "glm/glm.hpp"

#include "pch.hpp"
#include "utils/IFileHandler.hpp"
#include "assets/Material.hpp"

class MaterialFileHandler : public IFileHandler<Material>
{
public:
    Ref<Material> Load(const std::string &filename) override
    {
        YAML::Node data = YAML::LoadFile(filename);

        glm::vec4 color = data["Color"].as<glm::vec4>();
        glm::vec2 tiling = data["Tiling"].as<glm::vec2>();
        glm::vec2 offset = data["Offset"].as<glm::vec2>();

        return std::make_shared<Material>(color, tiling, offset);
    }

    void Save(const std::string &path, const Material &material) override
    {
        YAML::Node data = YAML::LoadFile(path);

        glm::vec4 m_Color = material.GetColor();
        glm::vec2 m_Tiling = material.GetTiling();
        glm::vec2 m_Offset = material.GetOffset();

        YAML::Node colorNode(std::vector<float>{m_Color.r, m_Color.g, m_Color.b, m_Color.a});
        colorNode.SetStyle(YAML::EmitterStyle::Flow);
        data["Color"] = colorNode;

        YAML::Node tilingNode(std::vector<float>{m_Tiling.x, m_Tiling.y});
        tilingNode.SetStyle(YAML::EmitterStyle::Flow);
        data["Tiling"] = tilingNode;

        YAML::Node offsetNode(std::vector<float>{m_Offset.x, m_Offset.y});
        offsetNode.SetStyle(YAML::EmitterStyle::Flow);
        data["Offset"] = offsetNode;

        std::ofstream fout(path);
        fout << data;
    }
};