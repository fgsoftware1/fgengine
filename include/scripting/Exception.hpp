#pragma once

#include "pch.hpp"

class Exception : public std::exception {
public:
    Exception() = default;

    explicit Exception(std::string msg) : msg(std::move(msg)) {}

    const char* what() const throw() override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class NotFound : public Exception {
public:
    NotFound() : Exception("Not found") {}
};

class BadCast : public Exception {
public:
    BadCast() : Exception("Bad cast") {}

    explicit BadCast(std::string msg) : Exception(std::move(msg)) {}
};

class RuntimeError : public Exception {
public:
    explicit RuntimeError(std::string msg) : Exception(std::move(msg)) {}
};

class CompileError : public Exception {
public:
    explicit CompileError(std::string msg) : Exception(std::move(msg)) {}
};