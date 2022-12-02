#pragma once

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "utils/Types.h"
#include "utils/String.hpp"

namespace fgengine
{
	namespace math
	{
		struct Quaternion;

		struct FGE_API Matrix4
		{
			union
			{
				float elements[4 * 4];
				Vector4 rows[4];
			};

			Matrix4();
			Matrix4(float diagonal);
			Matrix4(float *elements);
			Matrix4(const Vector4 &row0, const Vector4 &row1, const Vector4 &row2, const Vector4 &row3);

			static Matrix4 Identity();

			Matrix4 &Multiply(const Matrix4 &other);
			friend FGE_API Matrix4 operator*(Matrix4 left, const Matrix4 &right);
			Matrix4 &operator*=(const Matrix4 &other);

			Vector3 Multiply(const Vector3 &other) const;
			friend FGE_API Vector3 operator*(const Matrix4 &left, const Vector3 &right);

			Vector4 Multiply(const Vector4 &other) const;
			friend FGE_API Vector4 operator*(const Matrix4 &left, const Vector4 &right);

			Matrix4 &Invert();

			Vector4 GetColumn(int index) const;
			void SetColumn(uint index, const Vector4 &column);
			inline Vector3 GetPosition() const { return Vector3(GetColumn(3)); }
			inline void SetPosition(const Vector3 &position) { SetColumn(3, Vector4(position, 1.0f)); }

			static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);
			static Matrix4 LookAt(const Vector3 &camera, const Vector3 &object, const Vector3 &up);

			static Matrix4 Translate(const Vector3 &translation);
			static Matrix4 Rotate(float angle, const Vector3 &axis);
			static Matrix4 Rotate(const Quaternion &quat);
			static Matrix4 Scale(const Vector3 &scale);
			static Matrix4 Invert(const Matrix4 &matrix);

			static Matrix4 Transpose(const Matrix4 &matrix);

			String ToString() const;
		};
	}
}
