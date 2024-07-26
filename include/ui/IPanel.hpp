#pragma once

#include "boost/filesystem.hpp"

#include "pch.hpp"

namespace fs = boost::filesystem;

class IPanel
{
public:
    virtual ~IPanel() = default;

    virtual void draw(const fs::path &path) = 0;
};