#include <imgui.h>

#include "ui/AssetBrowserPanel.hpp"
#include "assets/Project.hpp"

fs::path AssetBrowserPanel::currentPath;
Ref<Project> AssetBrowserPanel::s_Project;
Ref<TextureFileHandler> AssetBrowserPanel::s_FileHandler;

ItemType getItemType(const fs::path &path)
{
    if (fs::is_directory(path))
    {
        return ItemType::Folder;
    }
    else
    {
        return ItemType::File;
    }
}

FileExtension getFileExtension(const fs::path &path)
{
    std::string extension = path.extension().string();
    if (extension == ".cpp")
    {
        return FileExtension::CPP;
    }
    else if (extension == ".wren")
    {
        return FileExtension::WREN;
    }
    else if (extension == ".chai")
    {
        return FileExtension::CHAI;
    }
    else if (path.filename() == "CMakeLists")
    {
        return FileExtension::CMAKELISTS;
    }
    else
    {
        return FileExtension::OTHER;
    }
}

AssetBrowserPanel::AssetBrowserPanel() {}

AssetBrowserPanel::~AssetBrowserPanel() {}

void AssetBrowserPanel::setup()
{
    this->folderTex = s_FileHandler->loadTextureFromFile("assets/textures/folder.png");
    if (folderTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load default folder texture!");
    }
    this->fileTex = s_FileHandler->loadTextureFromFile("assets/textures/file.png");
    if (fileTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load default file texture!");
    }
    this->cmakeTex = s_FileHandler->loadTextureFromFile("assets/textures/cmake.png");
    if (cmakeTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load cmake texture! Falling back to default!");
        this->cmakeTex = this->fileTex;
    }
    this->cppTex = s_FileHandler->loadTextureFromFile("assets/textures/cpp.png");
    if (cppTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load cpp texture! Falling back to default!");
        this->cppTex = this->fileTex;
    }
    this->chaiTex = s_FileHandler->loadTextureFromFile("assets/textures/chai.png");
    if (chaiTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load chai texture! Falling back to default!");
        this->chaiTex = this->fileTex;
    }
    this->wrenTex = s_FileHandler->loadTextureFromFile("assets/textures/wren.png");
    if (wrenTex == NULL)
    {
        Logger::Error(LogChannel::App, "Failed to load wren texture! Falling back to default!");
        this->wrenTex = this->fileTex;
    }
}

void AssetBrowserPanel::drawItem(const fs::path &path)
{
    int counter = 0;
    ItemType type = getItemType(path);
    std::string name = path.stem().string();
    FileExtension extension = getFileExtension(path.string());

    if (type == ItemType::File && name == "CMakeLists")
    {
        if (ImGui::ImageButton((void *)(intptr_t)this->cmakeTex, ImVec2(32, 32)))
        {
            this->currentPath = path;
            draw(this->currentPath);
        }
        ImGui::Text("%s", name.c_str());
    }
    switch (type)
    {
    case ItemType::Folder:
        if (ImGui::ImageButton((void *)(intptr_t)this->folderTex, ImVec2(32, 32)))
        {
            this->currentPath = path;
            draw(this->currentPath);
        }
        ImGui::Text("%s", name.c_str());
        break;
    case ItemType::File:
        switch (extension)
        {
        case FileExtension::CPP:
            if (ImGui::ImageButton((void *)(intptr_t)this->cppTex, ImVec2(32, 32)))
            {
                this->currentPath = path;
                draw(this->currentPath);
            }
            ImGui::Text("%s", name.c_str());
            break;
        case FileExtension::CHAI:
            if (ImGui::ImageButton((void *)(intptr_t)this->chaiTex, ImVec2(32, 32)))
            {
                this->currentPath = path;
                draw(this->currentPath);
            }
            ImGui::Text("%s", name.c_str());
            break;
        case FileExtension::WREN:
            if (ImGui::ImageButton((void *)(intptr_t)this->wrenTex, ImVec2(32, 32)))
            {
                this->currentPath = path;
                draw(this->currentPath);
            }
            ImGui::Text("%s", name.c_str());
            break;
        }
        break;

    default:
        Logger::Warn(LogChannel::App, "Unknown item type!: " + name + "\nFalling back to default!");
        if (ImGui::ImageButton((void *)(intptr_t)this->folderTex, ImVec2(32, 32)))
        {
            this->currentPath = path;
            draw(this->currentPath);
        }
        ImGui::Text("%s", name.c_str());
        break;
    }
}

void AssetBrowserPanel::draw(const fs::path &path)
{
    if (ImGui::BeginTabItem("AssetBrowser"))
    {
        try{
            ImGui::Columns(8, "mycolumns");
            for (const auto &entry : fs::directory_iterator(path))
            {
                drawItem(entry.path());
            }
            ImGui::Columns(1);
        }catch(fs::filesystem_error &e){
            Logger::Error(LogChannel::App, e.what());
        }
    }
    ImGui::EndTabItem();
}