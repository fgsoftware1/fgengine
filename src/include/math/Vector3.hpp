#pragma once
#ifndef Vector3_HPP
#define Vector3_HPP

namespace fgengine
{
	namespace math{
		class Vector3
		{
		private:
		public:
			float x;
			float y;
			float z;

			Vector3();

			Vector3(float uX, float uY, float uZ);

			~Vector3();

			Vector3(const Vector3 & v);

			void operator+=(const Vector3 & v);
			void operator-=(const Vector3 & v);
			void operator*=(float s);
			void operator/=(float s);
			void operator%=(const Vector3 & v);

			Vector3& operator=(const Vector3 & v);
			Vector3 operator+(const Vector3 & v) const;
			Vector3 operator-(const Vector3 & v) const;
			Vector3 operator*(float s) const;
			Vector3 operator/(float s) const;
			Vector3 operator%(Vector3 v) const;

			float operator*(const Vector3 & v) const;

			void conjugate();
			void normalize();
			void zero();
			void absolute();
			void show();
			void negate();

			Vector3 cross(Vector3 v) const;
			Vector3 rotateVectorAboutAngleAndAxis(float uAngle, Vector3 & uAxis);

			float dot(Vector3 v) const;
			float angle(Vector3 v);
			float magnitude();
			float magnitudeSquare();
		};
	}
}

#endif
