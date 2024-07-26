#pragma once

#include "pch.hpp"

class TextureFileHandler
{
public:
    static TextureFileHandler& getInstance()
    {
        static TextureFileHandler instance;
        return instance;
    }

    GLuint loadTextureFromFile(const std::string& textureName);

private:
    TextureFileHandler() = default;
    TextureFileHandler(const TextureFileHandler&) = delete;
    TextureFileHandler& operator=(const TextureFileHandler&) = delete;
};
