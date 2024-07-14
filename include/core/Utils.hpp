#pragma once

#include "pch.hpp"

bool ReadFile(std::string file, std::string& fileContents, bool addLineTerminator = false);
long GetFileModTime(std::string file);