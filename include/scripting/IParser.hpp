#pragma once

#include "pch.hpp"

class Field {
public:
    std::string type;
    std::string name;
    std::string value;
    int line;
    int pos;
};

class Class {
public:
    std::string name;
    std::vector<Field> fields;
};

class IParser {
public:
    virtual ~IParser() {}

    virtual Class parse() = 0;
};