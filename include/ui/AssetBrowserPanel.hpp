#pragma once

#include "boost/filesystem.hpp"
#include "glad/glad.h"

#include "pch.hpp"
#include "ui/IPanel.hpp"
#include "utils/TextureFileHandler.hpp"
#include "assets/Project.hpp"

namespace fs = boost::filesystem;

enum class ItemType
{
    File,
    Folder
};

enum class FileExtension {
    CPP,
    WREN,
    CHAI,
    CMAKELISTS,
    OTHER
};

ItemType getItemType(const fs::path &path);

FileExtension getFileExtension(const fs::path& path);

class AssetBrowserPanel : public IPanel
{
public:
    AssetBrowserPanel();
    ~AssetBrowserPanel();

    void setup();
    void drawItem(const fs::path &path);

    void draw(const fs::path &path = "") override;

private:
    static fs::path currentPath;
    static Ref<Project> s_Project;
    static Ref<TextureFileHandler> s_FileHandler;

    GLuint folderTex;
    GLuint fileTex;
    GLuint cmakeTex;
    GLuint cppTex;
    GLuint wrenTex;
    GLuint chaiTex;
};
