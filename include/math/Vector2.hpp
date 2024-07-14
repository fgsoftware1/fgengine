#pragma once

#include <cmath>
#include <iostream>

    /**
     * @brief Represents a 2D vector with x and y components.
     *
     * This class provides a convenient way to represent and manipulate 2D vectors
     * in your code. It offers constructors for initialization, member functions for
     * accessing and modifying components, and overloads for arithmetic operations
     * (addition, subtraction, negation, multiplication, division), comparison
     * operators (equality, inequality), and subscript operator overloads for
     * convenient component access and modification.
     */
    class Vector2
    {
    public:
        /**
         * @brief Default constructor that initializes all components to 0.0f.
         *
         * @return The newly constructed Vector2 object.
         *
         * Example:
         * @code
         * Vector2 v; // v = (0.0f, 0.0f)
         * @endcode
         */
        Vector2() : x(0.0f), y(0.0f) {}

        /**
         * @brief Constructor that initializes the vector with the given x and y components.
         *
         * @param x The initial value for the x component.
         * @param y The initial value for the y component.
         *
         * Example:
         * @code
         * Vector2 v(1.0f, 2.0f); // v = (1.0f, 2.0f)
         * @endcode
         */
        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        inline float getX() const { return x; }
        inline void setX(float value) { x = value; }
        inline float getY() const { return y; }
        inline void setY(float value) { y = value; }

        inline Vector2 getZero() { return zero; }
        inline Vector2 getOne() { return one; }
        inline Vector2 getUp() { return up; }
        inline Vector2 getRight() { return right; }

        /**
         * @brief Calculates and returns the length (magnitude) of the vector.
         *
         * @return The length (magnitude) of the vector.
         *
         * @throws None
         *
         * Example:
         * @code
         * Vector2 v(3.0f, 4.0f);
         * float mag = v.magnitude(); // mag = 5.0f
         * @endcode
         */
        inline float magnitude() const
        {
            // Check for NaN components to avoid undefined behavior
            if (std::isnan(x) || std::isnan(y))
            {
                throw std::invalid_argument("Vector2::magnitude: Cannot calculate magnitude with NaN components.");
            }
            // Calculate the square root of the sum of the squares of the x and y components
            return std::sqrt(x * x + y * y);
        }

        /**
         * @brief Overload of subscript operator to access components by index.
         *
         * Example:
         * @code
         * Vector2 v(1.0f, 2.0f);
         * float x = v[0]; // x = 1.0f
         * float y = v[1]; // y = 2.0f
         * @endcode
         *
         * @param index The index of the component to access (0 for x, 1 for y).
         * @return A reference to the component at the specified index.
         */
        float &operator[](int index)
        {
            return (&x)[index];
        }

        /**
         * @brief Overload of subscript operator to access components by index (const version).
         *
         * Example:
         * @code
         * const Vector2 v(1.0f, 2.0f);
         * float x = v[0]; // x = 1.0f
         * float y = v[1]; // y = 2.0f
         * @endcode
         *
         * @param index The index of the component to access (0 for x, 1 for y).
         * @return The value of the component at the specified index.
         */
        const float &operator[](int index) const
        {
            return (&x)[index];
        }

        Vector2 operator+(const Vector2 &other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        /**
         * @brief Overload of output stream operator to print the vector.
         *
         * Example:
         * @code
         * Vector2 v(1.0f, 2.0f);
         * std::cout << v; // prints "(1.0f, 2.0f)"
         * @endcode
         *
         * @param os The output stream to print to.
         * @param v The vector to print.
         * @return The modified output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector2 &v)
        {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }

    private:
        float x; ///< The x component of the vector.
        float y; ///< The y component of the vector.

        /**
         * @brief Constant vector with all components set to 0.
         *
         * Example:
         * @code
         * Vector2 v = Vector2::zero; // v = (0.0f, 0.0f)
         * @endcode
         */
        static Vector2 zero;
        /**
         * @brief Constant vector with all components set to 1.
         *
         * Example:
         * @code
         * Vector2 v = Vector2::one; // v = (1.0f, 1.0f)
         * @endcode
         */
        static Vector2 one;
        /**
         * @brief Constant unit vector pointing in the negative y-direction (downwards).
         *
         * Example:
         * @code
         * Vector2 v = Vector2::down; // v = (0.0f, -1.0f)
         * @endcode
         */
        static Vector2 down;

        /**
         * @brief Constant unit vector pointing in the positive y-direction (upwards).
         *
         * Example:
         * @code
         * Vector2 v = Vector2::up; // v = (0.0f, 1.0f)
         * @endcode
         */
        static Vector2 up;

        /**
         * @brief Constant unit vector pointing in the negative x-direction (left).
         *
         * Example:
         * @code
         * Vector2 v = Vector2::left; // v = (-1.0f, 0.0f)
         * @endcode
         */
        static Vector2 left;

        /**
         * @brief Constant unit vector pointing in the negative x-direction (left).
         *
         * Example:
         * @code
         * Vector2 v = Vector2::right; // v = (-1.0f, 0.0f)
         * @endcode
         */
        static Vector2 right;
    };