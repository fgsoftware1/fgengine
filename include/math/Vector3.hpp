#pragma once

#include "pch.hpp"

namespace math
{
    /**
     * @brief A class representing a 3D vector with x, y, and z components.
     */
    class Vector3
    {
    private:
        float x, y, z;

    public:
        /**
         * @brief Constructs a Vector3 with the given components.
         *
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         */
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

        /**
         * @brief Returns the x component of the vector.
         *
         * @return The x component of the vector.
         */
        float getX() const { return x; }

        /**
         * @brief Sets the x component of the vector.
         *
         * @param x The new x component of the vector.
         */
        void setX(float x) { this->x = x; }

        /**
         * @brief Returns the y component of the vector.
         *
         * @return The y component of the vector.
         */
        float getY() const { return y; }

        /**
         * @brief Sets the y component of the vector.
         *
         * @param y The new y component of the vector.
         */
        void setY(float y) { this->y = y; }

        /**
         * @brief Returns the z component of the vector.
         *
         * @return The z component of the vector.
         */
        float getZ() const { return z; }

        /**
         * @brief Sets the z component of the vector.
         *
         * @param z The new z component of the vector.
         */
        void setZ(float z) { this->z = z; }
    };
} // namespace math
