#pragma once

#include <cmath>

class Math
{
public:
    static constexpr float PI = 3.14159265358979323846;
    static constexpr float Deg2Rad = (PI * 2) / 360;
    static constexpr float Rad2Deg = 360 / (PI * 2);

    template <typename T>
    static T Abs(T value)
    {
        return std::abs(value);
    }
};