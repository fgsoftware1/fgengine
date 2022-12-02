#pragma once

#include "Common.h"
#include "utils/types.h"
#include "Matrix4.hpp"

namespace fgengine
{
	namespace math
	{
		struct FGE_API Quaternion
		{
			float x, y, z, w;

			Quaternion();
			Quaternion(const Quaternion &quaternion);
			Quaternion(float x, float y, float z, float w);
			Quaternion(const Vector3 &xyz, float w);
			Quaternion(const Vector4 &vec);
			Quaternion(float scalar);

			Quaternion &operator=(const Quaternion &quat);

			Quaternion &SetXYZ(const Vector3 &vec);
			const Vector3 GetXYZ() const;

			Quaternion &SetElem(i32 idx, float value);
			float GetElem(i32 idx) const;
			Vector3 GetAxis() const;
			Vector3 ToEulerAngles() const;

			const Quaternion operator+(const Quaternion &Quaternion) const;
			const Quaternion operator-(const Quaternion &Quaternion) const;
			const Quaternion operator*(const Quaternion &Quaternion) const;
			const Quaternion operator*(float scalar) const;
			const Quaternion operator/(float scalar) const;
			float operator[](i32 idx) const;

			Quaternion &operator+=(const Quaternion &Quaternion)
			{
				*this = *this + Quaternion;
				return *this;
			}

			Quaternion &operator-=(const Quaternion &Quaternion)
			{
				*this = *this - Quaternion;
				return *this;
			}

			Quaternion &operator*=(const Quaternion &Quaternion)
			{
				*this = *this * Quaternion;
				return *this;
			}

			Quaternion &operator*=(float scalar)
			{
				*this = *this * scalar;
				return *this;
			}

			Quaternion &operator/=(float scalar)
			{
				*this = *this / scalar;
				return *this;
			}

			const Quaternion operator-() const;
			bool operator==(const Quaternion &quaternion) const;
			bool operator!=(const Quaternion &quaternion) const;
			static Quaternion Identity();
			static Quaternion FromEulerAngles(const Vector3 &angles);

			static Vector3 Rotate(const Quaternion &quat, const Vector3 &vec);

			static const Quaternion Rotation(const Vector3 &unitVec0, const Vector3 &unitVec1);
			static const Quaternion Rotation(float radians, const Vector3 &unitVec);

			static const Quaternion RotationX(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
			}

			static const Quaternion RotationY(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(0.0f, sin(angle), 0.0f, cos(angle));
			}

			static const Quaternion RotationZ(float radians)
			{
				float angle = radians * 0.5f;
				return Quaternion(0.0f, 0.0f, sin(angle), cos(angle));
			}

			float Dot(const Quaternion &other) const;
			Quaternion Conjugate() const;
		};
	}
}
