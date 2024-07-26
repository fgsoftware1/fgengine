#pragma once

#include "pch.hpp"

namespace math
{
    /**
     * @class Vector2
     * @brief A 2-dimensional vector.
     *
     * The Vector2 class represents a 2-dimensional vector with x and y coordinates.
     */
    class Vector2
    {
    public:
        /**
         * @brief Constructs a new Vector2 object.
         * @param x The x-coordinate of the vector (default: 0.0f).
         * @param y The y-coordinate of the vector (default: 0.0f).
         */
        Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
        
        /**
         * @brief Copy constructor.
         * @param other The vector to copy.
         */
        Vector2(const Vector2 &other) : x(other.x), y(other.y) {}
        
        /**
         * @brief Move constructor.
         * @param other The vector to move.
         */
        Vector2(Vector2 &&other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}
        
        /**
         * @brief Gets the x-coordinate of the vector.
         * @return The x-coordinate.
         */
        float getX() const { return x; }
        
        /**
         * @brief Sets the x-coordinate of the vector.
         * @param x The new x-coordinate.
         */
        void setX(float x) { this->x = x; }
        
        /**
         * @brief Gets the y-coordinate of the vector.
         * @return The y-coordinate.
         */
        float getY() const { return y; }
        
        /**
         * @brief Sets the y-coordinate of the vector.
         * @param y The new y-coordinate.
         */
        void setY(float y) { this->y = y; }

        /**
         * @brief Copy assignment operator.
         * @param other The vector to copy.
         * @return The copy of the vector.
         */
        Vector2 &operator=(const Vector2 &other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }
        
        /**
         * @brief Move assignment operator.
         * @param other The vector to move.
         * @return The moved vector.
         */
        Vector2 &operator=(Vector2 &&other) noexcept
        {
            std::swap(x, other.x);
            std::swap(y, other.y);
            if (&other != this)
            {
                other.x = 0.0f;
                other.y = 0.0f;
            }
            return *this;
        }
        
        /**
         * @brief Outputs the vector in the format "(x, y)".
         * @param os The output stream.
         * @param vector The vector to output.
         * @return The modified output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector)
        {
            os << "(" << vector.x << ", " << vector.y << ")";
            return os;
        }
    private:
        float x, y;
    };
} // namespace math
