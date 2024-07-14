#pragma once

#include <boost/filesystem.hpp>

#include "pch.hpp"
#include "core/Logger.hpp"
#include "scripting/CppParser.hpp"
#include "scripting/WrenParser.hpp"

namespace fs = boost::filesystem;

using engine::core::LogChannel;
using engine::core::Logger;

class ParserFactory {
public:
    static Ref<IParser> createParser(const std::string& scriptPath) {
        fs::path filePath(scriptPath);
        std::string extension = filePath.extension().string();

        if (extension == ".cpp") {
            return Ref<IParser>(new CppParser(scriptPath));
        }
        else if (extension == ".wren") {
            return Ref<IParser>(new WrenParser(scriptPath));
        }
        else {
            Logger::Error(LogChannel::Engine, "File type not supported!");
            return nullptr;
        }
    }
};