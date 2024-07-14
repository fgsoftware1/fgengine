#pragma once

#include <boost/filesystem.hpp>

#include "pch.hpp"

namespace fs = boost::filesystem;

class Project {
public:
    Project(const std::string& name) : name(name), projectPath(name) {
        createBaseFoldersAndFiles();
    }

    std::string getProjectPath() {
        return projectPath.string();
    }

private:
    std::string name;
    fs::path projectPath;

    void createBaseFoldersAndFiles() {
        if (!fs::exists(projectPath)) {
            fs::create_directory(projectPath);
        }

        fs::path assetsPath = projectPath / "Assets";
        if (!fs::exists(assetsPath)) {
            fs::create_directory(assetsPath);
        }

        fs::path scriptsPath = assetsPath / "Scripts";
        if (!fs::exists(scriptsPath)) {
            fs::create_directory(scriptsPath);
        }

        std::ofstream cmakeFile(getProjectPath() + "/CMakeLists.txt");
        if (!cmakeFile) {
            std::cerr << "Unable to create CMakeLists.txt file\n";
            return;
        }

        cmakeFile << "cmake_minimum_required(VERSION 3.120)\n";
        cmakeFile << "project(" << getProjectPath() << ")\n\n";
        cmakeFile << "set(CMAKE_CXX_STANDARD 14)\n\n";
        cmakeFile << "add_executable(${PROJECT_NAME} main.cpp)\n";

        cmakeFile.close();
    }
};