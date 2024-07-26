#pragma once

#include "pch.hpp"

/**
 * @class Math
 * @brief A collection of mathematical utility functions.
 *
 * This class provides static methods for common mathematical operations.
 */
class Math
{
public:
    /// @brief The value of pi.
    static constexpr float PI = 3.14159265358979323846f;
    /// @brief Positive infinity.
    static constexpr float INFINITY = std::numeric_limits<float>::infinity();
    /// @brief Negative infinity.
    static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
    /// @brief The smallest positive value that is significant in numeric operations.
    static constexpr float EPSILON = std::numeric_limits<float>::epsilon();

    /**
     * @brief Converts degrees to radians.
     *
     * @param degrees The angle in degrees.
     * @return The angle in radians.
     */
    static float deg2rad(float degrees)
    {
        return degrees * PI / 180.0f;
    }

    /**
     * @brief Converts radians to degrees.
     *
     * @param radians The angle in radians.
     * @return The angle in degrees.
     */
    static float rad2deg(float radians)
    {
        return radians * 180.0f / PI;
    }
};
