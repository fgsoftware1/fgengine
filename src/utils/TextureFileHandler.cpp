#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "utils/TextureFileHandler.hpp"
#include "core/Logger.hpp"

using namespace engine::core;

GLuint TextureFileHandler::loadTextureFromFile(const std::string &textureName)
{
    int width, height, channels;
    unsigned char *data = stbi_load(textureName.c_str(), &width, &height, &channels, 0);

    if (data)
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (channels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (channels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        return texture;
    }
    else
    {
        Logger::Error(LogChannel::Engine, "Failed to load image: " + textureName);
        return 0;
    }
}