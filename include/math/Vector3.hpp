#pragma once

#include <cmath>
#include <ostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>

#include "math/Math.hpp"

/**
 * @brief Represents a 3D vector with x, y, and z components.
 *
 * This class provides a convenient way to represent and manipulate 3D vectors
 * in your code. It offers constructors for initialization, member functions for
 * accessing and modifying components, overloads for arithmetic operations
 * (addition, subtraction, negation, multiplication, division), comparison
 * operators (equality, inequality), and subscript operator overloads for
 * convenient component access and modification.
 */
class Vector3
{
public:
    /**
     * @brief Default constructor that initializes all components to 0.
     */
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    /**
     * @brief Constructor that initializes the vector with the given x, y, and z components.
     *
     * @param x The initial value for the x component.
     * @param y The initial value for the y component.
     * @param z The initial value for the z component.
     */
    Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /** @brief Copy constructor
     *
     * Creates a new, independent Vector3 object that is a complete copy of an existing one.
     *
     * @param other The Vector3 object to copy from.
     */
    Vector3(const Vector3 &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    /**
     * @brief Destructor.
     */
    ~Vector3() {}

    /**
     * @brief Constant unit vector pointing in the negative z-direction (backwards).
     */
    static const Vector3 back;

    /**
     * @brief Constant unit vector pointing in the negative y-direction (downwards).
     */
    static const Vector3 down;

    /**
     * @brief Constant unit vector pointing in the positive z-direction (forwards).
     */
    static const Vector3 forward;

    /**
     * @brief Constant unit vector pointing in the negative x-direction (left).
     */
    static const Vector3 left;

    /**
     * @brief Constant vector with all components set to 1.
     */
    static const Vector3 one;

    /**
     * @brief Constant unit vector pointing in the positive x-direction (right).
     */
    static const Vector3 right;

    /**
     * @brief Constant unit vector pointing in the positive y-direction (upwards).
     */
    static const Vector3 up;

    /**
     * @brief Constant vector with all components set to 0.
     */
    static const Vector3 zero;

    /**
     * @brief Calculates and returns the length (magnitude) of the vector.
     *
     * @return The length (magnitude) of the vector.
     *
     * @throws std::invalid_argument if any component of the vector is NaN (Not a Number).
     */
    float magnitude() const
    {
        // Check for NaN components to avoid undefined behavior
        if (std::isnan(x) || std::isnan(y) || std::isnan(z))
        {
            throw std::invalid_argument("Vector3: Cannot calculate magnitude with NaN components.");
        }
        return std::sqrt(x * x + y * y + z * z);
    }

    /**
     * @brief Calculates and returns a new Vector3 object with the same direction as this vector,
     * but with a magnitude of 1.
     *
     * This function calculates the magnitude of this vector and checks if it is very small
     * (less than a minimum positive value). If the magnitude is very small, the function
     * returns a zero vector (0, 0, 0).
     *
     * If the magnitude is not very small, the function divides each component of this vector
     * by the magnitude to achieve a new vector with the same direction, but with a magnitude
     * of 1.
     *
     * @return A new Vector3 object with the same direction as this vector, but with a magnitude
     * of 1. If the magnitude of this vector is very small, returns a zero vector (0, 0, 0).
     */
    Vector3 normalized() const
    {
        // Calculate the magnitude of this vector
        float magnitude = this->magnitude();

        // Check if the magnitude is very small
        if (magnitude < std::numeric_limits<float>::epsilon())
        {
            // Return a zero vector if magnitude is very small
            return Vector3().zero;
        }

        // Divide each component of this vector by the magnitude to achieve a vector with magnitude 1
        return Vector3(x / magnitude, y / magnitude, z / magnitude);
    }

    /**
     * @brief Calculates the dot product of two vectors.
     *
     * @param lhs The first vector (left-hand side).
     * @param rhs The second vector (right-hand side).
     * @return The dot product of the two vectors.
     *
     * @throws std::invalid_argument if either vector has a NaN (Not a Number) component.
     */
    static float Dot(const Vector3 &lhs, const Vector3 &rhs)
    {
        // Check for NaN components
        if (std::isnan(lhs.x) || std::isnan(lhs.y) || std::isnan(lhs.z) ||
            std::isnan(rhs.x) || std::isnan(rhs.y) || std::isnan(rhs.z))
        {
            throw std::invalid_argument("Dot: Cannot calculate dot product with NaN components.");
        }

        // Calculate dot product using component-wise multiplication and summation
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    /**
     * @brief Calculates the cross product of two vectors.
     *
     * The cross product of two vectors (lhs and rhs) results in a new vector that is perpendicular to both input vectors.
     * The magnitude of the resulting vector is related to the magnitudes of the input vectors and the angle between them.
     *
     * @param lhs The first vector (left-hand side).
     * @param rhs The second vector (right-hand side).
     * @return A new Vector3 object representing the cross product.
     */
    static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs)
    {
        float x = lhs.y * rhs.z - lhs.z * rhs.y;
        float y = lhs.z * rhs.x - lhs.x * rhs.z;
        float z = lhs.x * rhs.y - lhs.y * rhs.x;
        return Vector3(x, y, z);
    }

    /**
     * @brief Calculates the angle in degrees between two vectors.
     *
     * @param from The first vector (reference point).
     * @param to The second vector (target point).
     * @return The angle in degrees (between 0 and 180) between the two vectors.
     *
     * @throws std::invalid_argument if either vector has a NaN (Not a Number) component
     * or if the magnitude of either vector is too small (effectively zero).
     *
     * This function calculates the angle between two 3D vectors `from` and `to`. The angle
     * is the angle of rotation from `from` to `to`, treating them as directions. The returned angle
     * will always be between 0 and 180 degrees because the function calculates the smallest
     * angle between the vectors (not a reflex angle).
     */
    static float Angle(const Vector3 &from, const Vector3 &to)
    {
        // Check for NaN components
        if (std::isnan(from.x) || std::isnan(from.y) || std::isnan(from.z) ||
            std::isnan(to.x) || std::isnan(to.y) || std::isnan(to.z))
        {
            throw std::invalid_argument("Angle: Cannot calculate angle with NaN components.");
        }

        // Check for zero vectors (avoid division by zero)
        float fromMag = from.magnitude(); // Assuming GetMagnitude exists
        float toMag = to.magnitude();
        if (fromMag <= std::numeric_limits<float>::epsilon() ||
            toMag <= std::numeric_limits<float>::epsilon())
        {
            throw std::invalid_argument("Angle: Cannot calculate angle with zero vectors.");
        }

        // Calculate dot product and normalize magnitudes
        float dot = Dot(from, to) / (fromMag * toMag);

        // Clamp dot product to avoid errors due to floating-point precision issues~
        dot = std::clamp(dot, -1.0f, 1.0f);

        // Calculate angle in radians and convert to degrees
        float angleRad = std::acos(dot);
        float angleDeg = angleRad * 180.0f / Math::PI;

        return angleDeg;
    }

    /**
     * @brief Clamps the magnitude of a vector to a specified maximum value.
     *
     * This static function creates and returns a new Vector3 object with the same direction as the input vector,
     * but with its magnitude limited to the provided maxLength.
     *
     * @param vector The Vector3 object to clamp the magnitude of.
     * @param maxLength The maximum allowed magnitude for the returned vector.
     * @return A new Vector3 object with the clamped magnitude.
     */
    static Vector3 ClampMagnitude(const Vector3 &vector, float maxLength)
    {
        float currentMagnitude = vector.magnitude();
        if (currentMagnitude <= maxLength)
        {
            return vector; // No clamping needed if magnitude is already less than or equal to maxLength
        }

        // Normalize the vector (avoiding division by zero)
        Vector3 normalized = vector.normalized();
        if (normalized.x == 0.0f && normalized.y == 0.0f && normalized.z == 0.0f)
        {
            return Vector3(0.0f, 0.0f, 0.0f); // Return zero vector if original is zero
        }

        // Scale the normalized vector by maxLength to achieve the clamped magnitude
        return normalized * maxLength;
    }

    /**
     * @brief Calculates the distance between two Vector3 objects.
     *
     * This static method calculates the Euclidean distance between two
     * 3D vectors using the Euclidean norm of the difference vector.
     *
     * @param a The first Vector3 object.
     * @param b The second Vector3 object.
     * @return The Euclidean distance between the two vectors.
     * @throws std::invalid_argument If any component of either vector is NaN.
     */
    static float Distance(const Vector3 &a, const Vector3 &b)
    {
        // Check for NaN components
        if (std::isnan(a.x) || std::isnan(a.y) || std::isnan(a.z) ||
            std::isnan(b.x) || std::isnan(b.y) || std::isnan(b.z))
        {
            throw std::invalid_argument("Vector3::Distance: Cannot calculate distance with NaN components.");
        }

        // Calculate difference vector
        Vector3 diff = a - b;

        // Use member function to get magnitude of difference vector
        return diff.magnitude();
    }

    /**
     * @brief Performs linear interpolation between two Vector3 objects.
     *
     * This static method calculates a new Vector3 object representing a point
     * along the line segment connecting two given Vector3 objects (`a` and `b`).
     * The interpolation value (`t`) determines the position between `a` and `b`.
     *
     * @param a The starting Vector3 object.
     * @param b The ending Vector3 object.
     * @param t The interpolation value (typically between 0 and 1).
     * @return A new Vector3 object representing the interpolated value.
     */
    static Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t)
    {
        // Clamp t to the range [0, 1]
        t = std::clamp(t, 0.0f, 1.0f);

        // Calculate the interpolated value
        return (1 - t) * a + t * b;
    }

    static Vector3 Project(const Vector3 &vector, const Vector3 &onNormal)
    {
        float sqrMagnitude = Dot(onNormal, onNormal);
        if (sqrMagnitude <= std::numeric_limits<float>::epsilon())
        {
            throw std::invalid_argument("Vector3::Project: Cannot project vector on zero vector.");
        }
        float d = Dot(vector, onNormal) / sqrMagnitude;
        return onNormal * d;
    }

    /**
     * @brief Unary negation operator. Returns a new Vector3 with all components negated.
     *
     * @return A new Vector3 object with all components negated.
     */
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    /**
     * @brief Subtraction operator. Subtracts the corresponding components of another vector from this vector.
     *
     * @param other The other Vector3 object to subtract from this vector.
     * @return A new Vector3 object containing the difference of corresponding components.
     */
    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Addition operator. Adds the corresponding components of this vector and another vector.
     *
     * @param other The other Vector3 object to add with.
     * @return A new Vector3 object containing the sum of corresponding components.
     */
    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Scales the current vector by a scalar value.
     *
     * This operator performs component-wise multiplication between the current vector and a scalar value.
     * The resulting vector has the same direction as the original vector, but with a magnitude scaled by the scalar.
     *
     * @param scale The scalar value to multiply by (float).
     * @return A new Vector3 object representing the scaled vector.
     */
    // Scalar multiplication operator
    Vector3 operator*(float scale) const
    {
        return Vector3(x * scale, y * scale, z * scale);
    }

    /**
     * @brief Multiplication operator. Multiplies the corresponding components of this vector and another vector.
     *
     * @param other The other Vector3 object to multiply with.
     * @return A new Vector3 object containing the product of corresponding components.
     */
    Vector3 operator*(const Vector3 &other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    /**
     * @brief Division operator. Divides the corresponding components of this vector by another vector.
     *
     * @param other The other Vector3 object to divide this vector by.
     * @return A new Vector3 object containing the quotient of corresponding components.
     *
     * @throws std::invalid_argument if any component of the other vector is zero.
     */
    Vector3 operator/(const Vector3 &other) const
    {
        if (other.x == 0 || other.y == 0 || other.z == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    /** @brief Copy assignment operator
     *
     * Allows copying an existing Vector3 object using the assignment operator (=).
     *
     * @param other The Vector3 object to copy from.
     * @return A reference to the current object (*this) for chaining assignments.
     */
    Vector3 &operator=(const Vector3 &other)
    {
        if (this != &other)
        {
            // Perform deep copy of member variables
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    /**
     * @brief Equality operator. Checks if this vector is equal to another vector.
     *
     * @param other The other Vector3 object to compare with.
     * @return true if all corresponding components are equal, false otherwise.
     */
    bool operator==(const Vector3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    /**
     * @brief Inequality operator. Checks if this vector is not equal to another vector.
     *
     * @param other The other Vector3 object to compare with.
     * @return true if any corresponding components are not equal, false otherwise.
     */
    bool operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Subscript operator for non-const Vector3 objects. Returns a reference to the component at the given index.
     *
     * @param i The index of the component to return (0 for x, 1 for y, 2 for z).
     * @return A reference to the component at the given index.
     *
     * @throws std::out_of_range if the index is not 0, 1, or 2.
     */
    float &operator[](int i)
    {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else
            throw std::out_of_range("Index out of range for Vector3");
    }

    /**
     * @brief Overloads the << operator for std::ostream for the Vector3 class.
     *
     * This function allows a Vector3 object to be inserted into an output stream.
     * It inserts a string representation of the Vector3 object into the stream.
     *
     * @param os The output stream to insert the Vector3 object into.
     * @param vec The Vector3 object to insert into the output stream.
     * @return The output stream with the Vector3 object inserted.
     */
    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec)
    {
        os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

    /**
     * @brief Performs scalar multiplication of a Vector3 object with a scalar value.
     *
     * This friend function overloads the multiplication operator (`*`) to allow for scalar multiplication of a Vector3 object.
     * It takes a scalar value as the first argument and a constant Vector3 object as the second argument.
     * It returns a new Vector3 object where each component of the original object is multiplied by the provided scalar value.
     *
     * This function follows the convention of placing the scalar value before the Vector3 object,
     * which aligns with common mathematical notation (scale * vec).
     *
     * @param scale The scalar value to multiply with.
     * @param vec The constant Vector3 object to be scaled.
     * @return A new Vector3 object with each component multiplied by the scalar.
     */
    friend Vector3 operator*(float scale, const Vector3 &vec)
    {
        return Vector3(scale * vec.x, scale * vec.y, scale * vec.z);
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};
