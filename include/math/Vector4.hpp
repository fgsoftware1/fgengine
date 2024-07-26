#pragma once

#include "pch.hpp"

namespace math
{
    /**
     * @brief A class representing a 4D vector with x, y, z, and w components.
     */
    class Vector4
    {
    private:
        float x, y, z, w;

    public:
        /**
         * @brief Constructs a Vector4 with the given components.
         *
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         * @param w The w component of the vector.
         */
        Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w) {}

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

        /**
         * @brief Returns the w component of the vector.
         *
         * @return The w component of the vector.
         */
        float getW() const { return w; }

        /**
         * @brief Sets the w component of the vector.
         *
         * @param w The new w component of the vector.
         */
        void setW(float w) { this->w = w; }
    };
} // namespace math
