#pragma once

#include "pch.hpp"

class Asset{
public:
    virtual ~Asset() = default;

    virtual void draw() = 0;
};