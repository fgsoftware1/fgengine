#pragma once

#include <boost/filesystem.hpp>

#include "pch.hpp"
#include "core/Logger.hpp"

using namespace engine::core;

namespace fs = boost::filesystem;

class Project
{
public:
    explicit Project(const std::string &name) : name_(std::make_shared<std::string>(name)), projectPath_(std::make_shared<fs::path>(name))
    {
        createBaseFoldersAndFiles();
    }

    std::string getProjectPath() const
    {
        return projectPath_->string();
    }

private:
    Ref<std::string> name_;
    Ref<fs::path> projectPath_;

    void createBaseFoldersAndFiles()
    {
        if (projectPath_ && !projectPath_->empty())
        {
            if (!projectPath_->empty())
            {
                if (!fs::exists(*projectPath_))
                {
                    fs::create_directory(*projectPath_);
                }

                fs::path assetsPath = *projectPath_ / "Assets";
                if (!fs::exists(assetsPath))
                {
                    fs::create_directory(assetsPath);
                }

                fs::path scriptsPath = assetsPath / "Scripts";
                if (!fs::exists(scriptsPath))
                {
                    fs::create_directory(scriptsPath);
                }

                fs::path cmakePath = *projectPath_ / "CMakeLists.txt";
                std::ofstream cmakeFile(cmakePath.string());
                if (cmakeFile.is_open())
                {
                    cmakeFile << "cmake_minimum_required(VERSION 3.20)\n"
                              << "project(" << *name_ << " CXX)\n\n"
                              << "set(CMAKE_CXX_STANDARD 17)\n\n"
                              << "include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/include)\n"
                              << "link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib" << ")\n\n"
                              << "file(GLOB_RECURSE SOURCES \"Assets/Scripts/*.cpp\")\n\n"
                              << "add_executable(${PROJECT_NAME} ${SOURCES})\n"
                              << "target_link_libraries(${PROJECT_NAME} fge)\n";

                    cmakeFile.close();
                }
                else
                {
                    Logger::Error(LogChannel::App, "Unable to create CMakeLists.txt!");
                }
            }
            else
            {
                std::cerr << "Project path is empty\n";
            }
        }
    }
};
