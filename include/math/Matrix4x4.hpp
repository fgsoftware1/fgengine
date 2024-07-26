#pragma once

#include "pch.hpp"

typedef float Matrix4x4[4][4];

class Matrix4x4
{
public:
    static Matrix4x4 Identity;
    static Matrix4x4 Zero;

    Matrix4x4();

    float get(int i, int j) const;
    void set(int i, int j, float value);

    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix);
private:
    float data[4][4];
};
