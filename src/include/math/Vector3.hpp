#pragma once

#include <ostream>
#include "Common.h"

namespace fgengine
{
	namespace math{
		struct Vector2;
		struct Vector4;
		struct Matrix4;

		struct FGE_API Vector3
		{
			float x, y, z;

			Vector3();
			~Vector3();
			Vector3(float scalar);
			Vector3(float x, float y, float z);
			Vector3(const Vector2& other);
			Vector3(float x, float y);
			Vector3(const Vector4& other);

			static Vector3 Up();
			static Vector3 Down();
			static Vector3 Left();
			static Vector3 Right();
			static Vector3 Zero();
			static Vector3 XAxis();
			static Vector3 YAxis();
			static Vector3 ZAxis();

			Vector3& Add(const Vector3& other);
			Vector3& Subtract(const Vector3& other);
			Vector3& Multiply(const Vector3& other);
			Vector3& Divide(const Vector3& other);
			Vector3& Add(float other);
			Vector3& Subtract(float other);
			Vector3& Multiply(float other);
			Vector3& Divide(float other);
			Vector3 Multiply(const Matrix4& transform) const;

			friend Vector3 operator+(Vector3 left, const Vector3& right);
			friend Vector3 operator-(Vector3 left, const Vector3& right);
			friend Vector3 operator*(Vector3 left, const Vector3& right);
			friend Vector3 operator/(Vector3 left, const Vector3& right);

			friend Vector3 operator+(Vector3 left, float right);
			friend Vector3 operator-(Vector3 left, float right);
			friend Vector3 operator*(Vector3 left, float right);
			friend Vector3 operator/(Vector3 left, float right);

			bool operator==(const Vector3& other) const;
			bool operator!=(const Vector3& other) const;

			Vector3& operator+=(const Vector3& other);
			Vector3& operator-=(const Vector3& other);
			Vector3& operator*=(const Vector3& other);
			Vector3& operator/=(const Vector3& other);

			Vector3& operator+=(float other);
			Vector3& operator-=(float other);
			Vector3& operator*=(float other);
			Vector3& operator/=(float other);

			bool operator<(const Vector3& other) const;
			bool operator<=(const Vector3& other) const;
			bool operator>(const Vector3& other) const;
			bool operator>=(const Vector3& other) const;

			friend Vector3 operator-(const Vector3& vector);

			Vector3 Cross(const Vector3& other) const;
			float Dot(const Vector3& other) const;

			float Magnitude() const;
			Vector3 Normalize() const;
			float Distance(const Vector3& other) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		};
	}
}
