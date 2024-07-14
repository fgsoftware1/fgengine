#pragma once

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "pch.hpp"
#include "scripting/IParser.hpp"

namespace fs = boost::filesystem;

class WrenParser : public IParser, public std::enable_shared_from_this<WrenParser> {
public:
    WrenParser(const std::string& filename) : filePath(filename) {}

    Class parse() override {
        std::ifstream file(filePath.string());
        std::string line;
        Class currentClass;
        bool isPublic = true;
        int lineNumber = 0;

        while (std::getline(file, line)) {
            ++lineNumber;
            boost::trim(line);

            if (boost::starts_with(line, "class ")) {
                std::string className = line.substr(6);
                currentClass.name = className.substr(0, className.find("{"));
                isPublic = false;
            }
            else if (line == "public:") {
                isPublic = true;
            }
            else if (line == "private:" || line == "protected:") {
                isPublic = false;
            }
            else if (isPublic && boost::contains(line, ";")) {
                std::vector<std::string> parts;
                boost::split(parts, line, boost::is_any_of(" "));

                if (parts.size() >= 4) {
                    Field field;
                    field.type = parts[0];
                    field.name = parts[1];
                    field.value = parts[3];
                    field.line = lineNumber;
                    field.pos = line.find(field.value);
                    currentClass.fields.push_back(field);
                }
            }
        }

        return currentClass;
    }

private:
    fs::path filePath;
};
