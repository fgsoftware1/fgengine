#pragma once 

#include "pch.hpp"
#include "ecs/Component.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

class SpriteRenderer : public Component{
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    void draw() override;

    const std::string& getName() const override { return name; }

private:
    void initRenderData();

private:
    static inline std::string name = "SpriteRenderer";

    Shader       shader;
    unsigned int quadVAO;
};