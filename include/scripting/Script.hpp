#pragma once

#include "pch.hpp"

class Script {
public:
    virtual ~Script() {}

    virtual void start() {}
    virtual void update() {}
    virtual void destroy() {}
};

class MyGameScript : public Script {
public:
    void start() override {
        // Initialization code here
    }

    void update() override {
        // Game logic here
    }

    void destroy() override {
        // Cleanup code here
    }
};
